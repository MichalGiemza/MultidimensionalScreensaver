#pragma once
#include "OptimizationMethod.h"
#include "Tools.h"
#include "Solution.h"
#include <random>
#include <vector>


class GradientDescent : public OptimizationMethod {
    const double min = -0.5;
    const double max = 0.5;
    
    double **d0;
    const Solution::valueFunction fun;
    const int n;

    double **d = nullptr;
    Solution *old = nullptr;
    double alpha;
    pointVec tmp_pts;  // TODO

public:
    double getAlpha() { return alpha; }

    GradientDescent(double **d0, double alpha, int count) : 
        d0(d0), alpha(alpha), fun(Tools::KruskalStress), n(count) {}

    Solution *InitPos();
    Solution *NextPos();

    pointVec Grad(double **d0, double **d, Solution &s);
    double *CalcGradPt(int k, double **d0, double **d, Solution s, double _A, double _B);
    double A(Solution s);
    double B(double **d0, int n);
    double C(int i, int j, int pt_i, Solution s, double **d0, double B);
};

