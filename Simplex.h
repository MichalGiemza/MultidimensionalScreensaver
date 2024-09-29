#pragma once
#include <limits>
#include "Shape.h"
#include "Tools.h"

class Simplex : public Shape {

public:
    virtual int GetVerticesCount(int dimension) override;
    virtual int GetEdgesCount(int dimension) override;
    virtual double **GenerateDistanceMatrix(int dimension) override;
};

