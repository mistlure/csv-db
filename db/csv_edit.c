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