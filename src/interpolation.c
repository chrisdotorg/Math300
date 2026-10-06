#include "interpolation.h"
#include "matrix.h"

#include <math.h>
#include <stdlib.h>

Status lagrange_evaluate(const double *x, const double *y, size_t n,
                         double point, double *value)
{
    if (!x || !y || !value || n == 0)
        return STATUS_INVALID_INPUT;

    *value = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double term = y[i];

        for (size_t j = 0; j < n; ++j) {
            if (i == j) continue;

            double denominator = x[i] - x[j];
            if (fabs(denominator) <= EPSILON)
                return STATUS_INVALID_INPUT;

            term *= (point - x[j]) / denominator;
        }

        *value += term;
    }

    return STATUS_OK;
}

Status newton_interpolation_evaluate(const double *x, const double *y,
                                     size_t n, double point, double *value)
{
    if (!x || !y || !value || n == 0)
        return STATUS_INVALID_INPUT;

    double *coeff = malloc(n * sizeof(*coeff));
    if (!coeff) return STATUS_MEMORY_ERROR;

    for (size_t i = 0; i < n; ++i)
        coeff[i] = y[i];

    for (size_t order = 1; order < n; ++order) {
        for (size_t i = n; i-- > order;) {
            double denominator = x[i] - x[i - order];
            if (fabs(denominator) <= EPSILON) {
                free(coeff);
                return STATUS_INVALID_INPUT;
            }
            coeff[i] =
                (coeff[i] - coeff[i - 1]) / denominator;
        }
    }

    double result = coeff[n - 1];

    for (size_t i = n - 1; i-- > 0;)
        result = result * (point - x[i]) + coeff[i];

    *value = result;
    free(coeff);
    return STATUS_OK;
}

Status polynomial_least_squares(const double *x, const double *y,
                                size_t n, size_t degree,
                                double *coefficients)
{
    if (!x || !y || !coefficients || n == 0 || degree >= n)
        return STATUS_INVALID_INPUT;

    const size_t m = degree + 1;
    Matrix normal = matrix_create(m, m);
    double *rhs = calloc(m, sizeof(*rhs));

    if (!normal.data || !rhs) {
        matrix_destroy(&normal);
        free(rhs);
        return STATUS_MEMORY_ERROR;
    }

    for (size_t row = 0; row < m; ++row) {
        for (size_t col = 0; col < m; ++col) {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k)
                sum += pow(x[k], (double)(row + col));
            matrix_set(&normal, row, col, sum);
        }

        double sum = 0.0;
        for (size_t k = 0; k < n; ++k)
            sum += y[k] * pow(x[k], (double)row);
        rhs[row] = sum;
    }

    Status status = gauss_solve(&normal, rhs, coefficients);

    matrix_destroy(&normal);
    free(rhs);
    return status;
}
