#ifndef CSV_EDIT_H
#define CSV_EDIT_H

#include "csv_base.h"

// Adds a new row to the database.
// 'data' is a comma-separated string (e.g. "Jan,Novak,20")
void addRow(CSV *db, const char *data);

#endif