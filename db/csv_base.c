#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_base.h"

void freeCSV(CSV *db)
{
    if (!db) return;

    if (db->headers)
    {
        for (size_t i = 0; i < db->column_count; i++)
        {
            free(db->headers[i]);
        }
        free(db->headers);
    }

    if (db->rows)
    {
        for (size_t i = 0; i < db->row_count; i++)
        {
            for (size_t j = 0; j < db->column_count; j++)
            {
                free(db->rows[i][j]);
            }
            free(db->rows[i]);
        }
        free(db->rows);
    }

    // Reset structure.
    db->column_count = 0;
    db->row_count = 0;
    db->headers = NULL;
    db->rows = NULL;
}

void printStats(const char *filename, const CSV *db)
{
    if (!db) return;

    printf("File: %s\n", filename);
    printf("Columns: %zu\n", db->column_count);
    printf("Rows: %zu\n", db->row_count);
}