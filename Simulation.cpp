#include "Simulation.h"

Simulation::Simulation(int dim, char *shape, double step, double eps) :
    dimIn(dim), polytope(shape), d0(Tools::malloc2D(dimIn)), alpha(step), epsilon(eps) {

    if (shape == simplexType) {
        auto sh = Simplex();
        d0 = sh.GenerateDistanceMatrix(dim);
        om = new GradientDescent(d0, alpha, sh.GetVerticesCount(dimIn));
    }
    if (shape == hypercubeType) {
        auto sh = Hypercube();
        d0 = sh.GenerateDistanceMatrix(dim);
        om = new GradientDescent(d0, alpha, sh.GetVerticesCount(dimIn));
    }

    mds = new MDS(Tools::EuclideanDistance, Tools::KruskalStress, om);
    s = mds->InitPos();
    oldStress = s->GetValue();
    simulationInProgress = true;
}

bool Simulation::isRunning() {
    return abs(oldStress - s->GetValue()) < epsilon;
}

void Simulation::update() {
    s = mds->NextIteration();

    if (abs(oldStress - s->GetValue()) < epsilon)
        simulationInProgress = false;

    oldStress = s->GetValue();
}

