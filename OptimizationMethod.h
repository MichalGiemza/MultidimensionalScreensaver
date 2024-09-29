#pragma once
#include "Solution.h"

class OptimizationMethod {
public:
    virtual Solution *NextPos() = 0;
    virtual Solution *InitPos() = 0;
};

