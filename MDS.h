#pragma once
#include "OptimizationMethod.h"
#include "Tools.h"


class MDS {
private:
    int iteration = 0;
public:
    distanceF *distance;
    stressF *stress;
    OptimizationMethod *optimizer;

public:
    int getIteration() { return iteration; }

    MDS(distanceF &distanceFunction, stressF &stressFunction, OptimizationMethod *minimalizationMethod);
    Solution *InitPos();
    Solution *NextIteration();
};

