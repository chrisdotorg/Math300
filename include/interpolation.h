#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stddef.h>
#include "common.h"

Status lagrange_evaluate(
    const double *x, const double *y, size_t n,
    double point, double *value);

Status newton_interpolation_evaluate(
    const double *x, const double *y, size_t n,
    double point, double *value);

Status polynomial_least_squares(
    const double *x, const double *y, size_t n,
    size_t degree, double *coefficients);

#endif
