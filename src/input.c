#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static bool read_line(char *buffer, int size)
{
    if (!fgets(buffer, size, stdin))
        return false;

    return true;
}

bool input_int(const char *prompt, int *value)
{
    char buffer[128];
    char *end;
    long result;

    if (!value) return false;

    printf("%s", prompt);

    if (!read_line(buffer, sizeof(buffer)))
        return false;

    errno = 0;
    result = strtol(buffer, &end, 10);

    if (errno != 0 || end == buffer)
        return false;

    *value = (int)result;
    return true;
}

bool input_size(const char *prompt, size_t *value)
{
    int temp;

    if (!input_int(prompt, &temp) || temp <= 0)
        return false;

    *value = (size_t)temp;
    return true;
}

bool input_double(const char *prompt, double *value)
{
    char buffer[128];
    char *end;

    if (!value) return false;

    printf("%s", prompt);

    if (!read_line(buffer, sizeof(buffer)))
        return false;

    errno = 0;
    double result = strtod(buffer, &end);

    if (errno != 0 || end == buffer)
        return false;

    *value = result;
    return true;
}

bool input_choice(const char *prompt, int min, int max, int *value)
{
    while (true) {
        if (input_int(prompt, value) && *value >= min && *value <= max)
            return true;

        printf("Invalid choice. Please try again.\n");
    }
}
