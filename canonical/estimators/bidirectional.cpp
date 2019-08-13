#include "bidirectional.h"
#include <tgmath.h>

Bidirectional::Bidirectional() : Estimator() {
    type = EST_BIDIR;
}

Float Bidirectional::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float Tr = 0.0;

    Float yab = rec.a;
    Float yba = rec.b;

    vector<Float> a2b = vector<Float>();
    vector<Float> b2a = vector<Float>();

    do {
        Float maja2b = rec.extFunc->calculateMajorant(yab);
        Float majb2a = rec.extFunc->calculateMajorant(yba);

        if (yab >= rec.b && yba <= rec.a) {
            break;
        }

        if (yab < rec.b) {
            a2b.push_back(yab);
            yab += sampleExpFF(rec, sampler, maja2b);
        } else {
            // path from a to b must use odd samples only
            sampler->next1D();
        }

        if (yba > rec.a) {
            b2a.push_back(yba);
            yba -= sampleExpFF(rec, sampler, majb2a);
        } else {
            // path from b to a must use even samples only
            sampler->next1D();
        }
    } while (true);

    a2b.push_back(rec.b);
    b2a.push_back(rec.a);

    // a2b.push_back(rec.a);
    // do {
    //     Float maj = rec.extFunc->calculateMajorant(y);
    //     y += sampleExpFF(rec, sampler, maj);
    //
    //     if (y >= rec.b) break;
    //
    //     a2b.push_back(y);
    // } while(true);
    // a2b.push_back(rec.b);
    //
    // y = rec.b;
    // b2a.push_back(rec.b);
    // do {
    //     Float maj = rec.extFunc->calculateMajorant(y);
    //     y -= sampleExpFF(rec, sampler, maj);
    //
    //     if (y <= rec.a) break;
    //
    //     b2a.push_back(y);
    // } while(true);
    // b2a.push_back(rec.a);

    Float k = rec.extFunc->calculateMajorant((rec.b - rec.a) / 2.0);

    Float val = exp(-k * (rec.b - rec.a));

    vector<Float> extValsA2B = vector<Float>();
    vector<Float> extValsB2A = vector<Float>();

    vector<Float> expB2A = vector<Float>();
    vector<Float> expA2B = vector<Float>();

    extValsA2B.push_back(-1.0);
    for (int i = 1; i < a2b.size() - 1; ++i) {
        Float maj = rec.extFunc->calculateMajorant(a2b[i]);
        Float ex = (maj - rec.extFunc->calculateExtinction(a2b[i], rec.extCalls)) / maj;
        extValsA2B.push_back(ex);
        // expA2B.push_back(val / exp(-rec.extFunc->calculateMajorantIntegral(a2b[i - 1], a2b[i])));
        expA2B.push_back(val / exp(-k * (a2b[i] - a2b[i - 1])));
    }
    expA2B.push_back(val / exp(-k * (a2b[a2b.size() - 1] - a2b[a2b.size() - 2])));
    // expA2B.push_back(val / exp(-rec.extFunc->calculateMajorantIntegral(a2b[a2b.size() - 2], a2b[a2b.size() - 1])));
    extValsA2B.push_back(-1.0);

    extValsB2A.push_back(-1.0); // b
    for (int i = 1; i < b2a.size() - 1; ++i) {
        Float maj = rec.extFunc->calculateMajorant(b2a[i]);
        Float ex = (maj - rec.extFunc->calculateExtinction(b2a[i], rec.extCalls)) / maj;
        extValsB2A.push_back(ex);
        expB2A.push_back(val / exp(-k * (b2a[i - 1] - b2a[i])));
        // expB2A.push_back(val / exp(-rec.extFunc->calculateMajorantIntegral(b2a[i], b2a[i - 1])));
    }
    expB2A.push_back(val / exp(-k * (b2a[b2a.size() - 2] - b2a[b2a.size() - 1])));
    // expB2A.push_back(val / exp(-rec.extFunc->calculateMajorantIntegral(b2a[b2a.size() - 1], b2a[b2a.size() - 2])));
    extValsB2A.push_back(-1.0); // a

    // int n = max(a2b.size() - 2, b2a.size() - 2);
    int n = a2b.size() + b2a.size() - 4;

    for (int l = 0; l <= n; ++l) {
        for (int i = 0; i <= l; ++i) {
            int j = l - i;

            if (a2b.size() - 2 < i) {
                i = l+1;
                continue;
            }
            if (b2a.size() - 2 < j) continue;
            if (b2a[j] - a2b[i] < 0.0) continue;

            Float nee = exp(-k * (b2a[j] - a2b[i]));
            // Float nee = exp(-rec.extFunc->calculateMajorantIntegral(a2b[i], b2a[j]));
            Float pdf = val / nee;

            Float prod = 1.0;
            Float pdfPath = 0.0;
            Float pdfLight = 0.0;

            for (int q = 1; q <= i; ++q) {
                prod *= extValsA2B[q];
                pdfPath += expA2B[q - 1];
            }

            for (int q = 1; q <= j; ++q) {
                prod *= extValsB2A[q];
                pdfLight += expB2A[q - 1];
            }

            Float weight = pdf / (pdf + pdfLight + pdfPath + 2.0 * val);

            Float ist = prod * nee;

            Tr += ist * weight;
        }

        // can get rid of these if statements on every loop

    }

    Float pathProd = 1.0;
    for (int i = 0; i < extValsA2B.size(); ++i) {
        pathProd *= extValsA2B[i];
    }

    Float pdftotPath = 0.0;
    for (int i = 0; i < expA2B.size(); ++i) {
        pdftotPath += expA2B[i];
    }

    Tr += pathProd * val / (2.0 * val + pdftotPath);

    Float lightProd = 1.0;
    for (int i = 0; i < extValsB2A.size(); ++i) {
        lightProd *= extValsB2A[i];
    }

    Float pdftotLight = 0.0;
    for (int i = 0; i < expB2A.size(); ++i) {
        pdftotLight += expB2A[i];
    }

    Tr += lightProd * val / (2.0 * val + pdftotLight);

    rec.transmittance = Tr;

    return Tr;
}

string Bidirectional::getName() const {
    return "bidirectional";
}
