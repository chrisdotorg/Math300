#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <stdbool.h>

bool input_int(const char *prompt, int *value);
bool input_size(const char *prompt, size_t *value);
bool input_double(const char *prompt, double *value);
bool input_choice(const char *prompt, int min, int max, int *value);

#endif
