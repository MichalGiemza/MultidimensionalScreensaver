#include "Tools.h"
#include <fstream>

const char *simplexType = "Simplex";
const char *hypercubeType = "Hypercube";
const char *cubeType = "Cube";

const int displayWidth = 1280;
const int displayHeight = 960;

const float PI = 3.14159;

const ALLEGRO_COLOR colorBg = al_map_rgb(211, 82, 0);
const ALLEGRO_COLOR color = al_map_rgb(255, 134, 4);
const ALLEGRO_COLOR color3 = al_map_rgb(17, 18, 12);


double **Tools::malloc2D(int n) {
    double **m = (double **)malloc(n * sizeof(double *));
    
    for (int i = 0; i < n; i++) {
        m[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            m[i][j] = 0;
        }
    }

    return m;
}

void Tools::CalcDistances(double **result, pointVec &x, int n, distanceF distance) {

    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x.size(); j++) {
            result[i][j] = distance(x[i], x[j], n);
        }
    }

    return;
}

double Tools::EuclideanDistance(double *x1, double *x2, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double val = pow(x1[i] - x2[i], 2);
        sum += val;
    }

    return sqrt(sum);
}

double Tools::KruskalStress(double **d0, double **d, int count) {
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < i; j++) {
            sum1 += pow(d0[i][j] - d[i][j], 2);
            sum2 += pow(d0[i][j], 2);
        }
    }

    return sqrt(sum1 / sum2);
}

double Tools::randDouble(double from, double to) {
    double val = (double)rand() / RAND_MAX * (to - from) + from;
    return val;
}

void Tools::freePoints(pointVec &pts) {
    for (auto &pt : pts) {
        delete pt;
    }
    pts.clear();
}

double Tools::distance(double *p1, double *p2) {
    return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
}

void Tools::printDistMatrix(double **d, int n) {
    printf("\n [ i ] Distance matrix printout\n");
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            printf(" %1.4f", d[i][j]);
        }
        printf("\n");
    }
    printf(" [ i ] end of printout\n");
}

void Tools::printPointVec(pointVec &x, int n) {
    printf("\n [ i ] Vector printout\n");
    for (double *pt : x) {
        for (size_t i = 0; i < n; i++) {
            printf(" %1.4f", pt[i]);
        }
        printf("\n");
    }
    printf(" [ i ] end of printout\n");
}