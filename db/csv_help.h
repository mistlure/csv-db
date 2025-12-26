#ifndef CSV_HELP_H
#define CSV_HELP_H

#include <stddef.h>
#include "csv_base.h"

// Splits a line into tokens
char **splitLine(const char *line, const char *delimiters, size_t *count);

// Finds the index of a column by its name. Returns -1 if not found.
int getColumnIndex(const CSV *db, const char *columnName);

// Converts a string to a double number. Returns 0.0 if conversion fails.
double stringToDouble(const char *string);

#endif