#include "primaryestimator.h"

PrimaryEstimator::PrimaryEstimator() : Estimator() {
    // does nothing
}

void PrimaryEstimator::preProcess(Extinction* extFunc, Float a, Float b) {
    // does nothing for now
}

void PrimaryEstimator::updateAxisValue(AxisVar var, Float value) {
    // does nothing, is optionally extended
}

vector<AxisVar> PrimaryEstimator::getValidAxis() const {
    vector<AxisVar> vars = vector<AxisVar>();
    return vars;
}

void PrimaryEstimator::updateEstVar(EstimatorVarFloat var, Float value) {
    // does nothing, is optionally extended
}

void PrimaryEstimator::updateEstVar(EstimatorVarInt var, int value) {
    // does nothing, is optionally extended
}

void PrimaryEstimator::getEstVar(EstimatorVarFloat var, Float& data) const {
    data = 0.0;
}

void PrimaryEstimator::getEstVar(EstimatorVarInt var, int& data) const {
    data = 0;
}

vector<EstimatorVarFloat> PrimaryEstimator::getValidEstFloatVars() const {
    vector<EstimatorVarFloat> vars = vector<EstimatorVarFloat>();
    return vars;
}

vector<EstimatorVarInt> PrimaryEstimator::getValidEstIntVars() const {
    vector<EstimatorVarInt> vars = vector<EstimatorVarInt>();
    return vars;
}
