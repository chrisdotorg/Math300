#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define EPSILON 1e-10
#define DEFAULT_MAX_ITERATIONS 15000

typedef enum {
    STATUS_OK = 0,
    STATUS_INVALID_INPUT,
    STATUS_MAX_ITERATIONS,
    STATUS_DIVISION_BY_ZERO,
    STATUS_INVALID_INTERVAL,
    STATUS_SINGULAR_MATRIX,
    STATUS_NOT_SPD,
    STATUS_NOT_SYMMETRIC,
    STATUS_MEMORY_ERROR
} Status;

typedef struct {
    size_t max_iterations;
    double tolerance;
} SolverConfig;

const char *status_message(Status status);

#endif
