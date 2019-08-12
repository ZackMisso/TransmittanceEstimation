#pragma once

// this file contains a few data structures to keep track of various things.
// Hist used to be used to track the history of values in a very early implementation
// of this project, and I never got around to changing the names. These are not
// histograms.

#include "common.h"

enum HistFlags {
	HRF_SAMPLES = 0x1,
	HRF_AVERAGE = 0x2,
	HRF_HIST = 0x4,
	HRF_R = 0x8,
	HRF_C = 0x10,
	HRF_ABSERR = 0x20,
	HRF_RELERR = 0x40,
	HRF_VAR = 0x80,
	HRF_MEANS = 0x100,
	HRF_CLEAR = 0x200,
	HRF_SAMPVAR = 0x400,
	HRF_NONE = 0x0
};

enum HistType {
	HIST_REG,
	HIST_REG_RC,
	HIST_ERR,
	HIST_MULT,
	HIST_MULT_RC,
	HIST_MC,
	HIST_VAR_MAP
};

class Hist {
public:
	Hist();
	virtual ~Hist();

	virtual size_t size(int flags) = 0;
	virtual void push_back(Pdd param, int flags) = 0;
	virtual void push_back(Hist* param, int flags) = 0;
	virtual void postProcess(Float a, Float b, int samples, int flags) = 0;
	virtual void clear(int flags) = 0;
	virtual HistData& getData(int flags, int iter) = 0;

	// static Hist* initializeHist(HistType returnType);

	// void average(HistData& hist, HistData& average, int flags);

	HistType getType();
protected:
	HistType type;
};

class RegHist : public Hist {
public:
	RegHist();

	virtual size_t size(int flags);
	virtual void push_back(Pdd param, int flags);
	virtual void push_back(Hist* param, int flags);
	virtual void postProcess(Float a, Float b, int samples, int flags);
	virtual void clear(int flags);
	virtual HistData& getData(int flags, int iter);

	void printDebug();

	void setNeedsSort(bool param);
private:
	HistData hist;
	bool needsSort;
};

class ErrHist : public Hist {
public:
	ErrHist();

	virtual size_t size(int flags);
	virtual void push_back(Pdd param, int flags);
	virtual void push_back(Hist* param, int flags);
	virtual void postProcess(Float a, Float b, int samples, int flags);
	virtual void clear(int flags);
	virtual HistData& getData(int flags, int iter);

	void addCost(int value);

	Float getMean();
	Float getAbsRelError();
	Float getAbsError();
	Float getVariance();
	Float getSampleVariance();
	Float getEfficiency();
	Float getSampleEfficiency();
	Float getCost();
	Float getExpected();
	Float getBias();

	void setExpected(Float param);
	void setBias(Float value);

	// This is only used for testing
	void setVariance(Float value);
private:
	HistData t;
	Float mean;
	Float absRelError;
	Float absError;
	Float variance;
	Float sampVariance;
	Float cost;
	Float expected;
	Float bias;
};

// this hist is used for the var heat screen only
class VarHistMap : public Hist {
public:
	VarHistMap();
	~VarHistMap();

	virtual size_t size(int flags);
	virtual void push_back(Pdd param, int flags);
	virtual void push_back(Hist* param, int flags);
	virtual void postProcess(Float a, Float b, int samples, int flags);
	virtual void clear(int flags);
	virtual HistData& getData(int flags, int iter);

	// void push_back(Pdd sample);

	Float getMax(int flags);
	Float getMin(int flags);
	ErrHist* getHist(int iteration);
private:
	vector<ErrHist*> sampleHists;
	HistData samples;
};
