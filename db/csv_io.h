#ifndef CSV_IO_H
#define CSV_IO_H

#include "csv_base.h"

// Load CSV file from disk into memory.
// Returns 0 on success, non-zero on error.
int loadCSVFile(const char *filename, CSV *db);

// Save CSV structure back to a file.
// Returns 0 on success, non-zero on error.
int saveCSVFile(const char *filename, const CSV *db);

#endif