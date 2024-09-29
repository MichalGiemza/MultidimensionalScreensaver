#pragma once
#define ALLEGRO_UNSTABLE
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Tools.h"
#include "Simplex.h"
#include "Hypercube.h"
#include "Simulation.h"


class Visualization {
    
    Simulation *sim;
    int pointsCount = 0;
    int linesCount = 0;
    bool drawPoints = true; 
    double zoom = 250;

private:
    void drawSimplexEdges();
    void drawHypercubeEdges();
public:
    Visualization(Simulation *sim);
    void draw();
};

