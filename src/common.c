#include "common.h"

const char *status_message(Status status)
{
    switch (status) {
        case STATUS_OK: return "converged";
        case STATUS_INVALID_INPUT: return "invalid input";
        case STATUS_MAX_ITERATIONS: return "maximum iterations reached";
        case STATUS_DIVISION_BY_ZERO: return "division by zero / zero pivot";
        case STATUS_INVALID_INTERVAL: return "invalid interval";
        case STATUS_SINGULAR_MATRIX: return "singular matrix";
        case STATUS_NOT_SPD: return "matrix is not positive definite";
        case STATUS_NOT_SYMMETRIC: return "matrix is not symmetric";
        case STATUS_MEMORY_ERROR: return "memory allocation failed";
        default: return "unknown status";
    }
}
