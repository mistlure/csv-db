#ifndef CSV_MATH_H
#define CSV_MATH_H

#include "csv_base.h"

// Calculate average value of a column
void avgF(const CSV *db, const char *colName);

// Calculate sum of a column
void sumF(const CSV *db, const char *colName);

// Find minimum value in a column
void minF(const CSV *db, const char *colName);

// Find maximum value in a column
void maxF(const CSV *db, const char *colName);

#endif