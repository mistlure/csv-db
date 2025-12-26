#ifndef CSV_EDIT_H
#define CSV_EDIT_H

#include "csv_base.h"

// Adds a new row to the database.
// 'data' is a comma-separated string (e.g. "Jan,Novak,20")
void addRow(CSV *db, const char *data);

// Adds a new column.
// 'colName' is the new header name.
// 'data' is comma-separated values for each row (e.g. "10,20,30").
void addCol(CSV *db, const char *colName, const char *data);

#endif