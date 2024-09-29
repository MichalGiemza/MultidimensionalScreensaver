#pragma once
#include <xmemory>
#include <vector>
#include <random>
#include <numeric>
#include <allegro5/color.h>


extern const char *simplexType;
extern const char *hypercubeType;
extern const char *cubeType;

extern const int displayWidth;
extern const int displayHeight;

extern const float PI;

extern const ALLEGRO_COLOR colorBg;
extern const ALLEGRO_COLOR color;
extern const ALLEGRO_COLOR color3;

typedef double (distanceF)(double *x1, double *x2, int n);
typedef double (stressF)(double **d0, double **d, int dimX);
typedef std::vector<double *> pointVec;


class Tools {
public:
    static double **malloc2D(int n);

    static void CalcDistances(double **result, pointVec &x, int n, distanceF distance);

    static double EuclideanDistance(double *x1, double *x2, int n);

    static double KruskalStress(double **d0, double **d, int count);

    static double randDouble(double from, double to);

    static void freePoints(pointVec &p);

    static double distance(double *p1, double *p2);

    static void printDistMatrix(double **d, int n);

    static void printPointVec(pointVec &x, int n);
};

