#ifndef MATRIX_H
#define MATRIX_H

#include "common.h"

typedef struct {
    size_t rows;
    size_t cols;
    double *data;
} Matrix;

Matrix matrix_create(size_t rows, size_t cols);
void matrix_destroy(Matrix *matrix);

double matrix_get(const Matrix *matrix, size_t row, size_t col);
void matrix_set(Matrix *matrix, size_t row, size_t col, double value);

void matrix_fill_zero(Matrix *matrix);
void matrix_print(const Matrix *matrix);

Status matrix_copy(const Matrix *src, Matrix *dst);

Status gauss_solve(const Matrix *A, const double *b, double *x);
Status gauss_jordan_solve(const Matrix *A, const double *b, double *x);
Status crout_solve(const Matrix *A, const double *b, double *x);
Status doolittle_solve(const Matrix *A, const double *b, double *x);
Status cholesky_solve(const Matrix *A, const double *b, double *x);
Status jacobi_solve(const Matrix *A, const double *b, double *x,
                    size_t max_iterations, double tolerance);
Status gauss_seidel_solve(const Matrix *A, const double *b, double *x,
                          size_t max_iterations, double tolerance);

#endif
