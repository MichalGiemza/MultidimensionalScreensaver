#include "Simplex.h"

int Simplex::GetVerticesCount(int dimension) {
    return dimension + 1;
}

int Simplex::GetEdgesCount(int dimension) {
    if (dimension < 1)
        return INT_MIN;
    if (dimension == 1)
        return 1;

    return GetEdgesCount(dimension - 1) + GetVerticesCount(dimension - 1);
}

double **Simplex::GenerateDistanceMatrix(int dimension) {
    int n = GetVerticesCount(dimension);
    double **m = Tools::malloc2D(n);

    // All vertices in same distance
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = i == j ? 0 : 1;

    return m;
}
