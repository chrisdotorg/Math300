#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "root_finding.h"

static double f(double x)
{
    return x * x - 2.0;
}

static double df(double x)
{
    return 2.0 * x;
}

int main(void)
{
    SolverConfig config = { 1000, 1e-10 };

    RootResult bisection =
        bisection_method(f, 1.0, 2.0, config);
    assert(bisection.status == STATUS_OK);
    assert(fabs(bisection.root - sqrt(2.0)) < 1e-8);

    RootResult newton =
        newton_method(f, df, 1.5, config);
    assert(newton.status == STATUS_OK);
    assert(fabs(newton.root - sqrt(2.0)) < 1e-8);

    RootResult secant =
        secant_method(f, 1.0, 2.0, config);
    assert(secant.status == STATUS_OK);
    assert(fabs(secant.root - sqrt(2.0)) < 1e-8);

    puts("root_finding tests: OK");
    return 0;
}
