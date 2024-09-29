#pragma once
#include <limits>
#include <math.h>
#include "Shape.h"
#include "Tools.h"

class Hypercube : public Shape {

public:
    static int HammingDistance(int n1, int n2);
    virtual int GetVerticesCount(int dimension) override;
    virtual int GetEdgesCount(int dimension) override;
    virtual double **GenerateDistanceMatrix(int dimension) override;
};

