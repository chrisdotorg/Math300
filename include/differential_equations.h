#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H

#include "root_finding.h"

typedef double (*OdeFunction)(double x, double y);

typedef struct {
    double x;
    double y;
} OdePoint;

Status euler_step(
    OdeFunction f, OdePoint initial, double step,
    size_t steps, OdePoint *result);

Status runge_kutta_2_step(
    OdeFunction f, OdePoint initial, double step,
    size_t steps, OdePoint *result);

#endif
