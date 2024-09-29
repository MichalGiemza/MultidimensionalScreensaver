#include "Visualization.h"


void Visualization::drawSimplexEdges() {
    int k = 0;
    for (int i = 0; i < pointsCount; i++)
        for (int j = i + 1; j < pointsCount; j++) {

            al_draw_line(
                sim->getSolution()->GetArgument()[i][0] * zoom + displayWidth / 2,
                sim->getSolution()->GetArgument()[i][1] * zoom + displayHeight / 2,
                sim->getSolution()->GetArgument()[j][0] * zoom + displayWidth / 2,
                sim->getSolution()->GetArgument()[j][1] * zoom + displayHeight / 2,
                color,
                2.0f
            );
            k++;
        }
}

void Visualization::drawHypercubeEdges() {
    int k = 0;
    for (int i = 0; i < pointsCount; i++)
        for (int j = i + 1; j < pointsCount; j++)
            if (Hypercube::HammingDistance(i, j) == 1) { 
                // Hamming distance == 1  =>  edge is present
                
                al_draw_line(
                    sim->getSolution()->GetArgument()[i][0] * zoom + displayWidth / 2,
                    sim->getSolution()->GetArgument()[i][1] * zoom + displayHeight / 2,
                    sim->getSolution()->GetArgument()[j][0] * zoom + displayWidth / 2,
                    sim->getSolution()->GetArgument()[j][1] * zoom + displayHeight / 2,
                    color,
                    2.0f
                );
                k++;
            }
}

Visualization::Visualization(Simulation *sim) : sim(sim) {
    
    if (sim->getPolytope() == simplexType) {
        auto sh = Simplex();
        pointsCount = sh.GetVerticesCount(sim->getDimIn());
        linesCount = sh.GetEdgesCount(sim->getDimIn());
    }
    if (sim->getPolytope() == hypercubeType) {
        auto sh = Hypercube();
        pointsCount = sh.GetVerticesCount(sim->getDimIn());
        linesCount = sh.GetEdgesCount(sim->getDimIn());
    }
}

void Visualization::draw() {
    // Edges
    if (sim->getPolytope() == simplexType) {
        drawSimplexEdges();
    }
    if (sim->getPolytope() == hypercubeType) {
        drawHypercubeEdges();
    }

    // Points
    if (drawPoints) {
        for (int i = 0; i < pointsCount; i++) {
            al_draw_filled_circle(
                sim->getSolution()->GetArgument()[i][0] * zoom + displayWidth / 2,
                sim->getSolution()->GetArgument()[i][1] * zoom + displayHeight / 2,
                4, color);
        }
    }
}

