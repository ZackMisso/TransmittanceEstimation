#include "hist.h"
#include "util.h"

////
// HIST INTERFACE
////

Hist::Hist() { }

Hist::~Hist() { }

HistType Hist::getType() {
	return type;
}

////
// REGULAR HIST CLASS
////

RegHist::RegHist() : Hist() {
	hist = HistData();
	needsSort = false;
	type = HIST_REG;
}

size_t RegHist::size(int flags) {
	return hist.size();
}

void RegHist::push_back(Pdd param, int flags) {
	hist.push_back(param);
}

void RegHist::push_back(Hist* param, int flags) {
	// not supported
}

void RegHist::postProcess(Float a, Float b, int samples, int flags) {
	if (needsSort) Util::sort(hist);
	if (flags & HRF_CLEAR) clear(HRF_NONE);
	// debug logic
	for (int i = 0; i < hist.size(); i++)
	{
		if (hist[i].first < a || hist[i].first > b)
		{
			cout << "x is out of bounds" << endl;
			printDebug();
			i = hist.size();
		}
		if (hist[i].second < 0.0 || hist[i].second > 1.0)
		{
			cout << "y is out of bounds" << endl;
			printDebug();
			i = hist.size();
		}
	}
}

void RegHist::printDebug() {
	for (int i = 0; i < hist.size(); i++)
		cout << i << ": (" << hist[i].first << ", " << hist[i].second << ")" << endl;
}

void RegHist::clear(int flags) {
	hist.clear();
}

void RegHist::setNeedsSort(bool param) {
	needsSort = param;
}

HistData& RegHist::getData(int flags, int iter) {
	return hist;
}

////
// ERROR HIST CLASS
////

ErrHist::ErrHist() : Hist() {
	t = HistData();
	mean = 0.0;
	absRelError = 0.0;
	absError = 0.0;
	variance = 0.0;
	sampVariance = 0.0;
	cost = 0.0;
	expected = 0.0;
	bias = 0.0;
	type = HIST_ERR;
}

size_t ErrHist::size(int flags) {
	return t.size();
}

void ErrHist::push_back(Pdd param, int flags) {
	if (flags & HRF_HIST) t.push_back(param);
}

void ErrHist::push_back(Hist* param, int flags) {
	// not supported
}

void ErrHist::postProcess(Float a, Float b, int samples, int flags) {
	if (flags & HRF_CLEAR) clear(HRF_MEANS | HRF_ABSERR | HRF_RELERR | HRF_VAR);

	int bb = (int)b;
	Float expected = a;

	// calculates the means for every index
	if (flags & HRF_MEANS) {
		Float sum = 0.0;

		for (int i = 0; i < bb; i++) {
			sum += t[i].second;
		}

		mean = sum / (Float)bb;
	}

	// for each sample point calculate the absolute error
	if (flags & HRF_ABSERR) {
		Float sum = 0.0;

		for (int j = 0; j < bb; j++) {
			sum += Util::abs(t[j].second - expected);
		}

		absError = sum / ((Float)bb);
	}

	// for each sample point calculate the absolute relative error
	if (flags & HRF_RELERR) {
		Float sum = 0.0;

		for (int j = 0; j < bb; j++) {
			sum += Util::abs(t[j].second - expected);
		}

		absRelError = sum / ((Float)bb * expected);
	}

	// for each sample point calculate the variance (mean squared error)
	if (flags & HRF_VAR) {
		Float sum = 0.0;

		for (int j = 0; j < bb; j++) {
			sum += (t[j].second - expected) * (t[j].second - expected);
		}

		variance = sum / ((Float)bb);

        // Float sum = 0.0;
        //
		// for (int i = 0; i < bb; i++) {
		// 	sum += t[i].second;
		// }
        //
		// mean = sum / (Float)bb;
        //
		// sum = 0.0;
        //
		// for (int j = 0; j < bb; j++) {
		// 	sum += (t[j].second - mean) * (t[j].second - mean);
		// }
        //
		// variance = sum / ((Float)bb);
	}

	// for each sample point calculate the sample variance
	if (flags & HRF_SAMPVAR && flags & HRF_MEANS) {
		Float sum = 0.0;

		for (int j = 0; j < bb; j++) {
			sum += (t[j].second - mean) * (t[j].second - mean);
		}

		sampVariance = sum / ((Float)bb - 1.0);
	}
}

void ErrHist::clear(int flags) {
	if (flags & HRF_HIST) t.clear();
}

HistData& ErrHist::getData(int flags, int iter) {
	if (flags & HRF_HIST) return t;
	return t;
}

void ErrHist::addCost(int value) {
	cost += (Float)value;
}

Float ErrHist::getMean() { return mean; }
Float ErrHist::getAbsRelError() { return absRelError; }
Float ErrHist::getAbsError() { return absError; }
Float ErrHist::getVariance() { return variance; }
Float ErrHist::getSampleVariance() { return sampVariance; }
Float ErrHist::getEfficiency() { return variance * (cost / (Float)t.size()); }
Float ErrHist::getSampleEfficiency() { return sampVariance * ((cost) / (Float)t.size()); }
Float ErrHist::getCost() { return (cost) / (Float)t.size(); }
Float ErrHist::getExpected() { return expected; }
Float ErrHist::getBias() { return bias; }

void ErrHist::setExpected(Float param) { expected = param; }
void ErrHist::setBias(Float param) { bias = param; }
void ErrHist::setVariance(Float param) { variance = param; }

////
// VARIANCE HIST MAP CLASS
////

VarHistMap::VarHistMap() : Hist() {
	samples = HistData();
	sampleHists = vector<ErrHist*>();
}

VarHistMap::~VarHistMap() {
	for (int i = 0; i < sampleHists.size(); i++)
		delete sampleHists[i];

	sampleHists.clear();
}

size_t VarHistMap::size(int flags) { // maybe pass in flags as well
	return samples.size();
}

void VarHistMap::push_back(Pdd param, int flags) {
	samples.push_back(param);
}

void VarHistMap::push_back(Hist* param, int flags) {
	if (param->getType() == HIST_ERR) {
		sampleHists.push_back((ErrHist*)param);
	}
}

void VarHistMap::postProcess(Float a, Float b, int samples, int flags) {
	// not supported
}

void VarHistMap::clear(int flags) {
	if (flags & HRF_HIST) sampleHists.clear();
	if (flags & HRF_SAMPLES) samples.clear();
}

HistData& VarHistMap::getData(int flags, int iter) {
	if (flags & HRF_HIST) return sampleHists[iter]->getData(HRF_HIST, HRF_NONE);
	else return samples;
}

Float VarHistMap::getMax(int flags) {
	if (flags & HRF_VAR) {
		Float max = sampleHists[0]->getVariance();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getVariance() > max)
				max = sampleHists[i]->getVariance();
		return max;
	} else if (flags & HRF_MEANS) {
		Float max = sampleHists[0]->getMean();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getMean() > max)
				max = sampleHists[i]->getMean();
		return max;
	} else if (flags & HRF_RELERR) {
		Float max = sampleHists[0]->getAbsRelError();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getAbsRelError() > max)
				max = sampleHists[i]->getAbsRelError();
		return max;
	} else if (flags & HRF_ABSERR) {
		Float max = sampleHists[0]->getAbsError();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getAbsError() > max)
				max = sampleHists[i]->getAbsError();
		return max;
	}
	return 0.0;
}

Float VarHistMap::getMin(int flags) {
	if (flags & HRF_VAR) {
		Float min = sampleHists[0]->getVariance();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getVariance() < min)
				min = sampleHists[i]->getVariance();
		return min;
	} else if (flags & HRF_MEANS) {
		Float min = sampleHists[0]->getMean();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getMean() < min)
				min = sampleHists[i]->getMean();
		return min;
	} else if (flags & HRF_RELERR) {
		Float min = sampleHists[0]->getAbsRelError();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getAbsRelError() < min)
				min = sampleHists[i]->getAbsRelError();
		return min;
	} else if (flags & HRF_ABSERR) {
		Float min = sampleHists[0]->getAbsError();
		for (int i = 1; i < sampleHists.size(); i++)
			if (sampleHists[i]->getAbsError() < min)
				min = sampleHists[i]->getAbsError();
		return min;
	}
	return 0.0;
}

ErrHist* VarHistMap::getHist(int iteration) {
	return sampleHists[iteration];
}
