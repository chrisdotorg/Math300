#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define AT(m,r,c) ((m)->data[(r) * (m)->cols + (c)])

Matrix matrix_create(size_t rows, size_t cols)
{
    Matrix m = { rows, cols, NULL };
    if (rows != 0 && cols != 0)
        m.data = calloc(rows * cols, sizeof(*m.data));
    return m;
}

void matrix_destroy(Matrix *matrix)
{
    if (matrix == NULL) return;
    free(matrix->data);
    matrix->data = NULL;
    matrix->rows = 0;
    matrix->cols = 0;
}

double matrix_get(const Matrix *matrix, size_t row, size_t col)
{
    return AT(matrix, row, col);
}

void matrix_set(Matrix *matrix, size_t row, size_t col, double value)
{
    AT(matrix, row, col) = value;
}

void matrix_fill_zero(Matrix *matrix)
{
    if (matrix && matrix->data)
        for (size_t i = 0; i < matrix->rows * matrix->cols; ++i)
            matrix->data[i] = 0.0;
}

void matrix_print(const Matrix *matrix)
{
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j)
            printf("%12.6f ", AT(matrix, i, j));
        putchar('\n');
    }
}

Status matrix_copy(const Matrix *src, Matrix *dst)
{
    if (!src || !dst || src->rows != dst->rows || src->cols != dst->cols)
        return STATUS_INVALID_INPUT;

    for (size_t i = 0; i < src->rows * src->cols; ++i)
        dst->data[i] = src->data[i];

    return STATUS_OK;
}

static Status validate_system(const Matrix *A, const double *b, double *x)
{
    if (!A || !A->data || !b || !x ||
        A->rows == 0 || A->rows != A->cols)
        return STATUS_INVALID_INPUT;
    return STATUS_OK;
}

static void swap_rows(Matrix *A, size_t r1, size_t r2)
{
    if (r1 == r2) return;
    for (size_t j = 0; j < A->cols; ++j) {
        double tmp = AT(A, r1, j);
        AT(A, r1, j) = AT(A, r2, j);
        AT(A, r2, j) = tmp;
    }
}

static void swap_values(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

Status gauss_solve(const Matrix *A, const double *b, double *x)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;
    Matrix M = matrix_create(n, n);
    double *rhs = malloc(n * sizeof(*rhs));

    if (!M.data || !rhs) {
        matrix_destroy(&M);
        free(rhs);
        return STATUS_MEMORY_ERROR;
    }

    matrix_copy(A, &M);
    for (size_t i = 0; i < n; ++i) rhs[i] = b[i];

    for (size_t k = 0; k < n; ++k) {
        size_t pivot = k;
        double largest = fabs(AT(&M, k, k));

        for (size_t i = k + 1; i < n; ++i) {
            double candidate = fabs(AT(&M, i, k));
            if (candidate > largest) {
                largest = candidate;
                pivot = i;
            }
        }

        if (largest <= EPSILON) {
            matrix_destroy(&M);
            free(rhs);
            return STATUS_SINGULAR_MATRIX;
        }

        swap_rows(&M, k, pivot);
        swap_values(&rhs[k], &rhs[pivot]);

        for (size_t i = k + 1; i < n; ++i) {
            double factor = AT(&M, i, k) / AT(&M, k, k);
            AT(&M, i, k) = 0.0;

            for (size_t j = k + 1; j < n; ++j)
                AT(&M, i, j) -= factor * AT(&M, k, j);

            rhs[i] -= factor * rhs[k];
        }
    }

    for (size_t i = n; i-- > 0;) {
        double sum = rhs[i];

        for (size_t j = i + 1; j < n; ++j)
            sum -= AT(&M, i, j) * x[j];

        if (fabs(AT(&M, i, i)) <= EPSILON) {
            matrix_destroy(&M);
            free(rhs);
            return STATUS_SINGULAR_MATRIX;
        }

        x[i] = sum / AT(&M, i, i);
    }

    matrix_destroy(&M);
    free(rhs);
    return STATUS_OK;
}

Status gauss_jordan_solve(const Matrix *A, const double *b, double *x)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;
    Matrix M = matrix_create(n, n + 1);

    if (!M.data) return STATUS_MEMORY_ERROR;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            AT(&M, i, j) = AT(A, i, j);
        AT(&M, i, n) = b[i];
    }

    for (size_t k = 0; k < n; ++k) {
        size_t pivot = k;
        double largest = fabs(AT(&M, k, k));

        for (size_t i = k + 1; i < n; ++i) {
            double candidate = fabs(AT(&M, i, k));
            if (candidate > largest) {
                largest = candidate;
                pivot = i;
            }
        }

        if (largest <= EPSILON) {
            matrix_destroy(&M);
            return STATUS_SINGULAR_MATRIX;
        }

        swap_rows(&M, k, pivot);

        double pivot_value = AT(&M, k, k);
        for (size_t j = 0; j <= n; ++j)
            AT(&M, k, j) /= pivot_value;

        for (size_t i = 0; i < n; ++i) {
            if (i == k) continue;

            double factor = AT(&M, i, k);
            for (size_t j = 0; j <= n; ++j)
                AT(&M, i, j) -= factor * AT(&M, k, j);
        }
    }

    for (size_t i = 0; i < n; ++i)
        x[i] = AT(&M, i, n);

    matrix_destroy(&M);
    return STATUS_OK;
}

Status crout_solve(const Matrix *A, const double *b, double *x)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;
    Matrix L = matrix_create(n, n);
    Matrix U = matrix_create(n, n);
    double *y = calloc(n, sizeof(*y));

    if (!L.data || !U.data || !y) {
        matrix_destroy(&L); matrix_destroy(&U); free(y);
        return STATUS_MEMORY_ERROR;
    }

    for (size_t i = 0; i < n; ++i)
        AT(&U, i, i) = 1.0;

    for (size_t j = 0; j < n; ++j) {
        for (size_t i = j; i < n; ++i) {
            double sum = 0.0;
            for (size_t k = 0; k < j; ++k)
                sum += AT(&L, i, k) * AT(&U, k, j);
            AT(&L, i, j) = AT(A, i, j) - sum;
        }

        if (fabs(AT(&L, j, j)) <= EPSILON) {
            matrix_destroy(&L); matrix_destroy(&U); free(y);
            return STATUS_SINGULAR_MATRIX;
        }

        for (size_t k = j + 1; k < n; ++k) {
            double sum = 0.0;
            for (size_t i = 0; i < j; ++i)
                sum += AT(&L, j, i) * AT(&U, i, k);
            AT(&U, j, k) =
                (AT(A, j, k) - sum) / AT(&L, j, j);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < i; ++j)
            sum += AT(&L, i, j) * y[j];
        y[i] = (b[i] - sum) / AT(&L, i, i);
    }

    for (size_t i = n; i-- > 0;) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j)
            sum += AT(&U, i, j) * x[j];
        x[i] = (y[i] - sum) / AT(&U, i, i);
    }

    matrix_destroy(&L); matrix_destroy(&U); free(y);
    return STATUS_OK;
}

Status doolittle_solve(const Matrix *A, const double *b, double *x)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;
    Matrix L = matrix_create(n, n);
    Matrix U = matrix_create(n, n);
    double *y = calloc(n, sizeof(*y));

    if (!L.data || !U.data || !y) {
        matrix_destroy(&L); matrix_destroy(&U); free(y);
        return STATUS_MEMORY_ERROR;
    }

    for (size_t i = 0; i < n; ++i)
        AT(&L, i, i) = 1.0;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < i; ++k)
                sum += AT(&L, i, k) * AT(&U, k, j);
            AT(&U, i, j) = AT(A, i, j) - sum;
        }

        if (fabs(AT(&U, i, i)) <= EPSILON) {
            matrix_destroy(&L); matrix_destroy(&U); free(y);
            return STATUS_SINGULAR_MATRIX;
        }

        for (size_t j = i + 1; j < n; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < i; ++k)
                sum += AT(&L, j, k) * AT(&U, k, i);
            AT(&L, j, i) =
                (AT(A, j, i) - sum) / AT(&U, i, i);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < i; ++j)
            sum += AT(&L, i, j) * y[j];
        y[i] = b[i] - sum;
    }

    for (size_t i = n; i-- > 0;) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j)
            sum += AT(&U, i, j) * x[j];
        x[i] = (y[i] - sum) / AT(&U, i, i);
    }

    matrix_destroy(&L); matrix_destroy(&U); free(y);
    return STATUS_OK;
}

Status cholesky_solve(const Matrix *A, const double *b, double *x)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;
    Matrix L = matrix_create(n, n);
    double *y = calloc(n, sizeof(*y));

    if (!L.data || !y) {
        matrix_destroy(&L); free(y);
        return STATUS_MEMORY_ERROR;
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            double sum = 0.0;

            for (size_t k = 0; k < j; ++k)
                sum += AT(&L, i, k) * AT(&L, j, k);

            if (i == j) {
                double value = AT(A, i, i) - sum;
                if (value <= EPSILON) {
                    matrix_destroy(&L); free(y);
                    return STATUS_NOT_SPD;
                }
                AT(&L, i, j) = sqrt(value);
            } else {
                if (fabs(AT(&L, j, j)) <= EPSILON) {
                    matrix_destroy(&L); free(y);
                    return STATUS_SINGULAR_MATRIX;
                }
                AT(&L, i, j) =
                    (AT(A, i, j) - sum) / AT(&L, j, j);
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < i; ++j)
            sum += AT(&L, i, j) * y[j];
        y[i] = (b[i] - sum) / AT(&L, i, i);
    }

    for (size_t i = n; i-- > 0;) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j)
            sum += AT(&L, j, i) * x[j];
        x[i] = (y[i] - sum) / AT(&L, i, i);
    }

    matrix_destroy(&L);
    free(y);
    return STATUS_OK;
}

static double max_abs_difference(const double *a, const double *b, size_t n)
{
    double max = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double d = fabs(a[i] - b[i]);
        if (d > max) max = d;
    }
    return max;
}

Status jacobi_solve(const Matrix *A, const double *b, double *x,
                    size_t max_iterations, double tolerance)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;
    double *current = calloc(n, sizeof(*current));
    double *next = calloc(n, sizeof(*next));

    if (!current || !next) {
        free(current); free(next);
        return STATUS_MEMORY_ERROR;
    }

    for (size_t iter = 0; iter < max_iterations; ++iter) {
        for (size_t i = 0; i < n; ++i) {
            if (fabs(AT(A, i, i)) <= EPSILON) {
                free(current); free(next);
                return STATUS_SINGULAR_MATRIX;
            }

            double sum = b[i];
            for (size_t j = 0; j < n; ++j)
                if (i != j)
                    sum -= AT(A, i, j) * current[j];

            next[i] = sum / AT(A, i, i);
        }

        if (max_abs_difference(current, next, n) <= tolerance) {
            for (size_t i = 0; i < n; ++i) x[i] = next[i];
            free(current); free(next);
            return STATUS_OK;
        }

        for (size_t i = 0; i < n; ++i)
            current[i] = next[i];
    }

    for (size_t i = 0; i < n; ++i) x[i] = current[i];
    free(current); free(next);
    return STATUS_MAX_ITERATIONS;
}

Status gauss_seidel_solve(const Matrix *A, const double *b, double *x,
                          size_t max_iterations, double tolerance)
{
    Status status = validate_system(A, b, x);
    if (status != STATUS_OK) return status;

    const size_t n = A->rows;

    for (size_t i = 0; i < n; ++i)
        x[i] = 0.0;

    for (size_t iter = 0; iter < max_iterations; ++iter) {
        double max_change = 0.0;

        for (size_t i = 0; i < n; ++i) {
            if (fabs(AT(A, i, i)) <= EPSILON)
                return STATUS_SINGULAR_MATRIX;

            double sum = b[i];

            for (size_t j = 0; j < i; ++j)
                sum -= AT(A, i, j) * x[j];

            for (size_t j = i + 1; j < n; ++j)
                sum -= AT(A, i, j) * x[j];

            double next = sum / AT(A, i, i);
            double change = fabs(next - x[i]);

            if (change > max_change)
                max_change = change;

            x[i] = next;
        }

        if (max_change <= tolerance)
            return STATUS_OK;
    }

    return STATUS_MAX_ITERATIONS;
}
