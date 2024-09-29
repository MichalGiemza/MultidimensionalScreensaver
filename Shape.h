#pragma once


class Shape {
public:
    virtual int GetVerticesCount(int dimension) = 0;
    virtual int GetEdgesCount(int dimension) = 0;
    virtual double **GenerateDistanceMatrix(int dimension) = 0;
};

