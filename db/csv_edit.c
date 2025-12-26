#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_edit.h"
#include "csv_help.h"

void addRow(CSV *db, const char *data)
{
    if (!data)
    {
        printf("Error: Missing row data. Usage: addrow val1,val2,...\n");
        return;
    }

    size_t count = 0;
    char **newRow = splitLine(data, ",", &count);

    if (!newRow)
    {
        fprintf(stderr, "Error: Failed to parse row data.\n");
        return;
    }

    if (count != db->column_count)
    {
        printf("Error: Row has %zu columns, expected %zu.\n", count, db->column_count);
        
        for (size_t i = 0; i < count; i++)
        {
            free(newRow[i]);
        }

        free(newRow);
        return;
    }

    char ***tmp = realloc(db->rows, (db->row_count + 1) * sizeof(char **));
    if (!tmp)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        for (size_t i = 0; i < count; i++) free(newRow[i]);
        free(newRow);
        return;
    }

    db->rows = tmp;

    db->rows[db->row_count] = newRow;
    db->row_count++;

    printf("Row added.\n");
}

void addCol(CSV *db, const char *colName, const char *data)
{
    if (!colName || !data)
    {
        printf("Error: Usage: addcol <name> <val1,val2...>\n");
        return;
    }

    size_t count = 0;
    char **newVals = splitLine(data, ",", &count);

    if (!newVals)
    {
        fprintf(stderr, "Error: Failed to parse column data.\n");
        return;
    }

    if (count != db->row_count)
    {
        printf("Error: Column has %zu values, expected %zu (rows).\n", count, db->row_count);
        for (size_t i = 0; i < count; i++) free(newVals[i]);
        free(newVals);
        return;
    }

    char **tmpHeaders = realloc(db->headers, (db->column_count + 1) * sizeof(char *));
    if (!tmpHeaders)
    {
        fprintf(stderr, "Error: Memory allocation failed (headers).\n");
        for (size_t i = 0; i < count; i++) free(newVals[i]);
        free(newVals);
        return;
    }
    db->headers = tmpHeaders;
    db->headers[db->column_count] = strdup(colName);

    for (size_t i = 0; i < db->row_count; i++)
    {
        char **tmpRow = realloc(db->rows[i], (db->column_count + 1) * sizeof(char *));
        if (!tmpRow)
        {
            fprintf(stderr, "Error: Memory allocation failed at row %zu.\n", i);
            return;
        }
        db->rows[i] = tmpRow;
        db->rows[i][db->column_count] = newVals[i];
    }

    free(newVals);
    db->column_count++;
    printf("Column '%s' added.\n", colName);
}