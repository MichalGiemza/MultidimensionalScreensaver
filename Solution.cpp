#include "Solution.h"

Solution::Solution(valueFunction function, double **d0, double **d, int count, pointVec &arg) : argument(arg) {
    this->function = function;
    this->d0 = d0;
    this->d = d;
    this->count = count;
}

double Solution::GetValue() {
    if (isnan(value)) {
        value = function(d0, d, count);
    }
    return value;
}

pointVec Solution::GetArgument() {
    return argument;
}
