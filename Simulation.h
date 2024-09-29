#pragma once
#include "MDS.h"
#include "OptimizationMethod.h"
#include "GradientDescent.h"
#include "Solution.h"
#include "Tools.h"
#include "Simplex.h"
#include "Hypercube.h"


class Simulation {
    
    OptimizationMethod *om = nullptr;
    MDS *mds = nullptr;
    Solution *s = nullptr;
    bool simulationInProgress = false;

    char *polytope = nullptr;
    double alpha = 0.2f;
    int interval = 16;
    double **d0 = nullptr;
    int dimIn = NULL;
    int dimOut = 2;
    double epsilon = 0.00001;
    int iteration = 0;
    double oldStress = 0;

public:
    int getDimIn() { return dimIn; }
    char *getPolytope() { return polytope; }
    Solution *getSolution() { return s; }

    Simulation(int dim, char *shape, double step, double eps = 0.00001);
    bool isRunning();
    void update();
};

