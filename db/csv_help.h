#ifndef CSV_HELP_H
#define CSV_HELP_H

#include <stddef.h>

char **splitLine(const char *line, const char *delimiters, size_t *count);

#endif