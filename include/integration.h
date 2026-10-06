#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "root_finding.h"

double left_rectangle_rule(ScalarFunction f, double a, double b, size_t n);
double right_rectangle_rule(ScalarFunction f, double a, double b, size_t n);
double midpoint_rule(ScalarFunction f, double a, double b, size_t n);
double trapezoidal_rule(ScalarFunction f, double a, double b, size_t n);

#endif
