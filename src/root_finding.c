#include "root_finding.h"

#include <math.h>

static RootResult make_result(double x, double fx, size_t iterations, Status status)
{
    RootResult result = { x, fx, iterations, status };
    return result;
}

RootResult bisection_method(ScalarFunction f, double a, double b,
                            SolverConfig config)
{
    double fa = f(a);
    double fb = f(b);

    if (fa == 0.0) return make_result(a, fa, 0, STATUS_OK);
    if (fb == 0.0) return make_result(b, fb, 0, STATUS_OK);
    if (fa * fb > 0.0)
        return make_result(a, fa, 0, STATUS_INVALID_INTERVAL);

    for (size_t i = 1; i <= config.max_iterations; ++i) {
        double c = a + (b - a) / 2.0;
        double fc = f(c);

        if (fabs(fc) <= config.tolerance ||
            fabs(b - a) <= config.tolerance)
            return make_result(c, fc, i, STATUS_OK);

        if (fa * fc < 0.0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    double c = a + (b - a) / 2.0;
    return make_result(c, f(c), config.max_iterations,
                       STATUS_MAX_ITERATIONS);
}

RootResult regula_falsi_method(ScalarFunction f, double a, double b,
                               SolverConfig config)
{
    double fa = f(a);
    double fb = f(b);

    if (fa == 0.0) return make_result(a, fa, 0, STATUS_OK);
    if (fb == 0.0) return make_result(b, fb, 0, STATUS_OK);
    if (fa * fb > 0.0)
        return make_result(a, fa, 0, STATUS_INVALID_INTERVAL);

    double c = a;

    for (size_t i = 1; i <= config.max_iterations; ++i) {
        double denominator = fb - fa;
        if (fabs(denominator) <= config.tolerance)
            return make_result(c, f(c), i, STATUS_DIVISION_BY_ZERO);

        c = a - fa * (b - a) / denominator;
        double fc = f(c);

        if (fabs(fc) <= config.tolerance ||
            fabs(b - a) <= config.tolerance)
            return make_result(c, fc, i, STATUS_OK);

        if (fa * fc < 0.0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return make_result(c, f(c), config.max_iterations,
                       STATUS_MAX_ITERATIONS);
}

RootResult secant_method(ScalarFunction f, double x0, double x1,
                         SolverConfig config)
{
    double f0 = f(x0);
    double f1 = f(x1);

    for (size_t i = 1; i <= config.max_iterations; ++i) {
        double denominator = f1 - f0;
        if (fabs(denominator) <= config.tolerance)
            return make_result(x1, f1, i, STATUS_DIVISION_BY_ZERO);

        double x2 = x1 - f1 * (x1 - x0) / denominator;
        double f2 = f(x2);

        if (fabs(x2 - x1) <= config.tolerance ||
            fabs(f2) <= config.tolerance)
            return make_result(x2, f2, i, STATUS_OK);

        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;
    }

    return make_result(x1, f1, config.max_iterations,
                       STATUS_MAX_ITERATIONS);
}

RootResult newton_method(ScalarFunction f, ScalarFunction df,
                         double initial_guess, SolverConfig config)
{
    double x = initial_guess;

    for (size_t i = 1; i <= config.max_iterations; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (fabs(dfx) <= config.tolerance)
            return make_result(x, fx, i, STATUS_DIVISION_BY_ZERO);

        double next_x = x - fx / dfx;
        double next_fx = f(next_x);

        if (fabs(next_x - x) <= config.tolerance ||
            fabs(next_fx) <= config.tolerance)
            return make_result(next_x, next_fx, i, STATUS_OK);

        x = next_x;
    }

    return make_result(x, f(x), config.max_iterations,
                       STATUS_MAX_ITERATIONS);
}

RootResult fixed_point_method(ScalarFunction g, double initial_guess,
                              SolverConfig config)
{
    double x = initial_guess;

    for (size_t i = 1; i <= config.max_iterations; ++i) {
        double next_x = g(x);

        if (fabs(next_x - x) <= config.tolerance)
            return make_result(next_x, 0.0, i, STATUS_OK);

        x = next_x;
    }

    return make_result(x, 0.0, config.max_iterations,
                       STATUS_MAX_ITERATIONS);
}
