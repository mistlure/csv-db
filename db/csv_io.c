#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_io.h"
#include "csv_help.h"

int loadCSVFile(const char *filename, CSV *db)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        return 1;
    }

    db->column_count = 0;
    db->row_count = 0;
    db->headers = NULL;
    db->rows = NULL;

    char buffer[1024];

    if (!fgets(buffer, sizeof(buffer), fp))
    {
        fclose(fp);
        fprintf(stderr, "Error: empty file %s\n", filename);
        return 1;
    }

    db->headers = splitLine(buffer, NULL, &db->column_count);
    if (!db->headers)
    {
        fclose(fp);
        fprintf(stderr, "Error: failed to parse headers\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        size_t col_count = 0;
        char **row = splitLine(buffer, NULL, &col_count);

        if (!row)
        {
            fclose(fp);
            fprintf(stderr, "Error: failed to parse row\n");
            return 1;
        }

        if (col_count == 0) 
        {
            free(row);
            continue;
        }

        if (col_count != db->column_count)
        {
            fprintf(stderr, "Warning: row has %zu columns, expected %zu\n",
                    col_count, db->column_count);
        }

        char ***tmp = realloc(db->rows, (db->row_count + 1) * sizeof(char **));
        if (!tmp)
        {
            fclose(fp);
            fprintf(stderr, "Error: memory allocation failed\n");
            return 1;
        }
        db->rows = tmp;

        db->rows[db->row_count++] = row;
    }

    fclose(fp);
    return 0;
}

int saveCSVFile(const char *filename, const CSV *db)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        fprintf(stderr, "Error: cannot open file %s for writing\n", filename);
        return 1;
    }

    // Headers.
    for (size_t i = 0; i < db->column_count; i++)
    {
        if (i > 0) fprintf(fp, ",");
        fprintf(fp, "%s", db->headers[i]);
    }
    fprintf(fp, "\n");

    // Rows.
    for (size_t r = 0; r < db->row_count; r++)
    {
        for (size_t c = 0; c < db->column_count; c++)
        {
            if (c > 0) fprintf(fp, ",");
            fprintf(fp, "%s", db->rows[r][c]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}