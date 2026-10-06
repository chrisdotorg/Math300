#include "integration.h"

double left_rectangle_rule(ScalarFunction f, double a, double b, size_t n)
{
    if (!f || n == 0) return 0.0;
    double h = (b - a) / (double)n;
    double sum = 0.0;

    for (size_t i = 0; i < n; ++i)
        sum += f(a + (double)i * h);

    return h * sum;
}

double right_rectangle_rule(ScalarFunction f, double a, double b, size_t n)
{
    if (!f || n == 0) return 0.0;
    double h = (b - a) / (double)n;
    double sum = 0.0;

    for (size_t i = 1; i <= n; ++i)
        sum += f(a + (double)i * h);

    return h * sum;
}

double midpoint_rule(ScalarFunction f, double a, double b, size_t n)
{
    if (!f || n == 0) return 0.0;
    double h = (b - a) / (double)n;
    double sum = 0.0;

    for (size_t i = 0; i < n; ++i)
        sum += f(a + ((double)i + 0.5) * h);

    return h * sum;
}

double trapezoidal_rule(ScalarFunction f, double a, double b, size_t n)
{
    if (!f || n == 0) return 0.0;
    double h = (b - a) / (double)n;
    double sum = 0.5 * (f(a) + f(b));

    for (size_t i = 1; i < n; ++i)
        sum += f(a + (double)i * h);

    return h * sum;
}
