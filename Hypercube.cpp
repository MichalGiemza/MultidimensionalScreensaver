#include "Hypercube.h"

int Hypercube::HammingDistance(int n1, int n2) {
    int x = n1 ^ n2;
    int h = 0;
    while (x != 0) {
        x = (x & (x - 1));
        h++;
    }
    return h;
}

int Hypercube::GetVerticesCount(int dimension) {
    return pow(2, dimension);
}

int Hypercube::GetEdgesCount(int dimension) {
    return dimension * pow(2, dimension - 1);
}

double **Hypercube::GenerateDistanceMatrix(int dimension) {
    int n = GetVerticesCount(dimension);
    double **m = Tools::malloc2D(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            // h=0 => same point, distance = 0
            // h=1 => edge, distance = 1
            // h>1 => diagonal, distance = 1 * sqrt(h)
            m[i][j] = 1.0 * sqrt(HammingDistance(i, j));
        }

    return m;
}
