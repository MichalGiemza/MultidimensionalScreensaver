#include "GradientDescent.h"

Solution *GradientDescent::InitPos() {
    // Prepare random solution for start
    pointVec pts = pointVec();
    d = Tools::malloc2D(n);

    for (int k = 0; k < n; k++) {
        auto pt = new double[2] { Tools::randDouble(min, max), Tools::randDouble(min, max) };
        pts.push_back(pt);
    }

    Tools::CalcDistances(d, pts, 2, Tools::EuclideanDistance);
    old = new Solution(fun, (double **)d0, d, n, pts);

    return old;
}

Solution *GradientDescent::NextPos() {
    // calculated using Euclidean Distance

    if (old == nullptr)
        InitPos();

    // Calc gradient
    pointVec grad = Grad((double **)d0, d, *old);

    // - grad * alpha
    for (auto &pt : grad) {
        pt[0] = -pt[0] * alpha; // X
        pt[1] = -pt[1] * alpha; // Y
    }
    // next_step = old - alpha * grad
    for (int k = 0; k < n; k++) {
        grad[k][0] += old->GetArgument()[k][0]; // X
        grad[k][1] += old->GetArgument()[k][1]; // Y
    }
    // save changes and return
    Tools::CalcDistances(d, grad, 2, Tools::EuclideanDistance); 
    
    delete old;
    old = new Solution(fun, (double **)d0, d, n, grad);

    return old;
}

pointVec GradientDescent::Grad(double **d0, double **d, Solution &s) {
    int n = s.GetArgument().size();

    double _B = B(d0, n);
    double _A = A(s);

    pointVec *grad = new pointVec();
    for (int k = 0; k < n; k++)
        grad->push_back(CalcGradPt(k, d0, d, s, _A, _B));

    return *grad;
}

double *GradientDescent::CalcGradPt(int k, double **d0, double **d, Solution s, double _A, double _B) {
    double *pt = new double[2] {0, 0};

    for (int i = 0; i < n; i++) {
        if (i != k) {
            pt[0] += C(i, k, 0, s, d0, _B); // X
            pt[1] += C(i, k, 1, s, d0, _B); // Y
        }
    }

    pt[0] *= _A; // X
    pt[1] *= _A; // Y

    return pt;
}

double GradientDescent::A(Solution s) {
    return 1 / (2 * s.GetValue());
}

double GradientDescent::B(double **d0, int n) {
    double sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            sum += pow(d0[i][j], 2);
        }
    }

    return sum;
}

double GradientDescent::C(int i, int j, int pt_i, Solution s, double **d0, double _B) {
    return 2.0 / _B * (-s.GetArgument()[i][pt_i] + s.GetArgument()[j][pt_i]) * (1 - d0[i][j] / d[i][j]);
}
