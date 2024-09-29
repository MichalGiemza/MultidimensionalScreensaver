#pragma once
#include <vector>
#include <limits>
#include "Tools.h"


class Solution {
public:
    typedef double (*valueFunction)(double **d0, double **d, int count);
private:
    double value = NAN;
    valueFunction function;
    double **d0;
    double **d;
    pointVec argument;
    int count;

public:
    Solution(valueFunction function, double **d0, double **d, int count, pointVec &arg);
    double GetValue();
    pointVec GetArgument();
};

