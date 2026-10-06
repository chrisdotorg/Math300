#ifndef ROOT_FINDING_H
#define ROOT_FINDING_H

#include "common.h"

typedef double (*ScalarFunction)(double);

typedef struct {
    double root;
    double function_value;
    size_t iterations;
    Status status;
} RootResult;

RootResult bisection_method(
    ScalarFunction f, double a, double b, SolverConfig config);

RootResult regula_falsi_method(
    ScalarFunction f, double a, double b, SolverConfig config);

RootResult secant_method(
    ScalarFunction f, double x0, double x1, SolverConfig config);

RootResult newton_method(
    ScalarFunction f, ScalarFunction df,
    double initial_guess, SolverConfig config);

RootResult fixed_point_method(
    ScalarFunction g, double initial_guess, SolverConfig config);

#endif
