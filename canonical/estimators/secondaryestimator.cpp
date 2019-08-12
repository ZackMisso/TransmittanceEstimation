#include "secondaryestimator.h"

SecondaryEstimator::SecondaryEstimator() : Estimator() {
    estimator = nullptr;
}

Float SecondaryEstimator::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    // sanity check
    if (rec.samples == -1) {
        cout << "ERROR: Number of Samples not set" << endl;
        return 0.0;
    }

    Float ret = 0.0;
    for (int i = 0; i < rec.samples * rec.samples; ++i) {
        // evaluate the primary estimator
        ret += estimator->T(rec, sampler);

        // increment sample
        sampler->nextSample();
    }

    rec.transmittance = ret / Float(rec.samples * rec.samples);

    return ret / Float(rec.samples * rec.samples);
}

Float SecondaryEstimator::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    // TODO
    return 0.0;
}

Float SecondaryEstimator::convergeT(TransmittanceQuaryRecord& rec, Sampler* sampler, vector<Float>& means, vector<Float>& costs) {
    // sanity check
    if (rec.samples == -1) {
        cout << "ERROR: Number of Samples not set" << endl;
        return 0.0;
    }

    Float ret = 0.0;
    // cout << "Rec Samples: " << rec.samples << endl;
    // cout << "Rec a: " << rec.a << endl;
    // cout << "Rec b: " << rec.b << endl;
    for (int i = 0; i < rec.samples; ++i) {
        // evaluate the primary estimator
        int prevCost = rec.extCalls;
        Float trans = estimator->T(rec, sampler);
        int cost = rec.extCalls - prevCost;
        costs.push_back(Float(cost));
        means.push_back(trans);

        ret += trans;

        // increment sample
        sampler->nextSample();
    }
    // cout << "Poest Converge T" << endl;

    return ret / Float(rec.samples);
}

Estimator* SecondaryEstimator::copy() const {
    SecondaryEstimator* newEst = new SecondaryEstimator();
    newEst->setPrimaryEstimator(estimator->copy());

    return newEst;
}

void SecondaryEstimator::updateAxisValue(AxisVar var, Float value) {
    estimator->updateAxisValue(var, value);
}

vector<AxisVar> SecondaryEstimator::getValidAxis() const {
    return estimator->getValidAxis();
}

void SecondaryEstimator::updateEstVar(EstimatorVarFloat var, Float value) {
    estimator->updateEstVar(var, value);
}

void SecondaryEstimator::updateEstVar(EstimatorVarInt var, int value) {
    estimator->updateEstVar(var, value);
}

void SecondaryEstimator::getEstVar(EstimatorVarFloat var, Float& data) const {
    estimator->getEstVar(var, data);
}

void SecondaryEstimator::getEstVar(EstimatorVarInt var, int& data) const {
    estimator->getEstVar(var, data);
}

vector<EstimatorVarFloat> SecondaryEstimator::getValidEstFloatVars() const {
    return estimator->getValidEstFloatVars();
}

vector<EstimatorVarInt> SecondaryEstimator::getValidEstIntVars() const {
    return estimator->getValidEstIntVars();
}

string SecondaryEstimator::getName() const {
    // cout << "Secondary Estimator NAME" << endl;
    return estimator->getName();
}

string SecondaryEstimator::getFullName() const {
    return estimator->getFullName();
}

void SecondaryEstimator::setPrimaryEstimator(Estimator* param) {
    estimator = param;
    if (!estimator) cout << "WHAT IN BLUE BLAZES?" << endl;
    type = estimator->getType();
}
