#ifndef OUTPUT_H
#define OUTPUT_H

#include "common.h"
#include "root_finding.h"

void print_root_result(const RootResult *result);
void print_status(Status status);
void print_vector(const double *x, size_t n);

#endif
