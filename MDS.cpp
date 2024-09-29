#include "MDS.h"

MDS::MDS(distanceF &distanceFunction, stressF &stressFunction, OptimizationMethod *minimalizationMethod) :
    distance(&distanceFunction), stress(&stressFunction), optimizer(minimalizationMethod) {
}

Solution *MDS::InitPos() {
    return optimizer->InitPos();
}

Solution *MDS::NextIteration() {
    iteration++;
    return optimizer->NextPos();
}
