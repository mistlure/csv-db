#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "csv_math.h"
#include "csv_help.h"

void avgF(const CSV *db, const char *colName)
{
    int colIdx = getColumnIndex(db, colName);

    if (colIdx < 0)
    {
        fprintf(stderr, "Column '%s' not found.\n", colName);
        return;
    }

    if (db->row_count == 0)
    {
        printf("Average of column %s: 0.0\n", colName);
        return;
    }

    double sum = 0.0;
    for (size_t i = 0; i < db->row_count; i++)
    {
        sum += stringToDouble(db->rows[i][colIdx]);
    }

    printf("Average of column %s: %.1f\n", colName, sum / db->row_count);
}

void sumF(const CSV *db, const char *colName)
{
    int colIdx = getColumnIndex(db, colName);
    if (colIdx < 0)
    {
        fprintf(stderr, "Column '%s' not found.\n", colName);
        return;
    }

    double sum = 0.0;
    for (size_t i = 0; i < db->row_count; i++)
    {
        sum += stringToDouble(db->rows[i][colIdx]);
    }

    printf("Sum of column %s: %g\n", colName, sum);
}

void minF(const CSV *db, const char *colName)
{
    int colIdx = getColumnIndex(db, colName);

    if (colIdx < 0)
    {
        fprintf(stderr, "Column '%s' not found.\n", colName);
        return;
    }

    if (db->row_count == 0)
    {
        printf("Min of column %s: 0\n", colName);
        return;
    }

    double minVal = stringToDouble(db->rows[0][colIdx]);

    // Loop starting from the second row (index 1)
    for (size_t i = 1; i < db->row_count; i++)
    {
        double val = stringToDouble(db->rows[i][colIdx]);
        if (val < minVal)
        {
            minVal = val;
        }
    }

    printf("Min of column %s: %g\n", colName, minVal);
}

void maxF(const CSV *db, const char *colName)
{
    int colIdx = getColumnIndex(db, colName);

    if (colIdx < 0)
    {
        fprintf(stderr, "Column '%s' not found.\n", colName);
        return;
    }

    if (db->row_count == 0)
    {
        printf("Max of column %s: 0\n", colName);
        return;
    }

    double maxVal = stringToDouble(db->rows[0][colIdx]);

    for (size_t i = 1; i < db->row_count; i++)
    {
        double val = stringToDouble(db->rows[i][colIdx]);
        if (val > maxVal)
        {
            maxVal = val;
        }
    }

    printf("Max of column %s: %g\n", colName, maxVal);
}