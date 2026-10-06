#include "output.h"

#include <stdio.h>

void print_status(Status status)
{
    printf("Status: %s\n", status_message(status));
}

void print_root_result(const RootResult *result)
{
    if (!result) return;

    printf("\nRoot          : %.12f\n", result->root);
    printf("f(root)       : %.12e\n", result->function_value);
    printf("Iterations    : %zu\n", result->iterations);
    print_status(result->status);
}

void print_vector(const double *x, size_t n)
{
    if (!x) return;

    for (size_t i = 0; i < n; ++i)
        printf("x[%zu] = %.10f\n", i, x[i]);
}
