#ifndef CSV_BASE_H
#define CSV_BASE_H

#include <stddef.h>

// Core structure to represent a CSV table.
typedef struct
{
    size_t column_count;
    size_t row_count;
    char **headers;
    char ***rows;
} CSV;

// Free all memory used by the CSV structure.
// After this call, the structure is reset to safe empty values.
void freeCSV(CSV *db);

#endif