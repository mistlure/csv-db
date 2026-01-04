#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "csv_help.h"

char **splitLine(const char *line, const char *delimiters, size_t *count)
{
    // Default delimiter value
    if (!delimiters) delimiters = ",";

    char **parts = NULL;
    size_t used = 0;
    const char *p = line;

    int loop = 1; 

    while (*p || loop)
    {
        if (!*p)
        {
            loop = 0;
        }

        const char *startToken = p;

        while (*p && !strchr(delimiters, *p)) 
        {
            p++;
        }

        size_t lenToken = p - startToken;
        
        char *token = malloc(lenToken + 1);
        if (!token)
        {
            for (size_t i = 0; i < used; i++) free(parts[i]);
            free(parts);
            return NULL;
        }

        memcpy(token, startToken, lenToken);
        token[lenToken] = '\0';

        for (size_t k = 0; k < lenToken; k++)
        {
            if (token[k] == '\r' || token[k] == '\n')
            {
                token[k] = '\0';
                break;
            }
        }

        char **tmp = realloc(parts, (used + 1) * sizeof(char *));
        if (!tmp)
        {
            for (size_t i = 0; i < used; i++)
            {
                free(parts[i]);
            }

            free(parts);
            free(token);
            return NULL;
        }

        parts = tmp;
        parts[used++] = token;

        if (*p) 
        {
            p++; 
        }
        else 
        {
            loop = 0; 
        }
    }

    *count = used;

    return parts;
}

int getColumnIndex(const CSV *db, const char *columnName)
{
    if (!db || !db->headers || !columnName)
    {
        return -1;
    }

    for (size_t i = 0; i < db->column_count; i++)
    {
        if (strcmp(db->headers[i], columnName) == 0)
        {
            return (int)i;
        }
    }
    return -1;
}

double stringToDouble(const char *string)
{
    if (!string)
    {
        return 0.0;
    }
    
    char *endptr;
    
    // strtod parses a double from a string
    double value = strtod(string, &endptr);
    
    // "text" return 0.0
    if (string == endptr) 
    {
        return 0.0;
    }
    
    return value;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(const char *in, const char *out) {
    printf(COLOR_CYAN "============================================================\n" COLOR_RESET);
    printf(STYLE_BOLD "                         CSV DATABASE                       \n" COLOR_RESET);
    printf(COLOR_CYAN "============================================================\n" COLOR_RESET);
    printf(" " STYLE_BOLD "INPUT FILE :" COLOR_RESET " %s\n", in);
    printf(" " STYLE_BOLD "OUTPUT FILE:" COLOR_RESET " %s\n", out);
    printf(COLOR_CYAN "============================================================\n" COLOR_RESET);
}

void printHelp() {
    printf("\n" COLOR_MAGENTA "--- AVAILABLE COMMANDS ---" COLOR_RESET "\n");
    printf(COLOR_YELLOW "  average <col>" COLOR_RESET "             : Calculate average of a column\n");
    printf(COLOR_YELLOW "  sum <col>" COLOR_RESET "                 : Calculate sum of a column\n");
    printf(COLOR_YELLOW "  min <col>" COLOR_RESET "                 : Find min value in a column\n");
    printf(COLOR_YELLOW "  max <col>" COLOR_RESET "                 : Find max value in a column\n");
    printf(COLOR_YELLOW "  addrow <vals>" COLOR_RESET "             : Add a row (" STYLE_BOLD "val1,val2,..." COLOR_RESET ")\n");
    printf(COLOR_YELLOW "  addcol <name> <vals>" COLOR_RESET "      : Add a column\n");
    printf(COLOR_YELLOW "  delrow <index>" COLOR_RESET "            : Delete a row by index (0-based)\n");
    printf(COLOR_YELLOW "  !help" COLOR_RESET "                     : Show this list\n");
    printf(COLOR_YELLOW "  rewrite" COLOR_RESET "                   : Save changes to file without exiting\n");
    printf(COLOR_YELLOW "  exit" COLOR_RESET "                      : Save and quit\n");
    printf(COLOR_MAGENTA "--------------------------" COLOR_RESET "\n");
}

void printMenu() {
    printf("\n" STYLE_BOLD "Select Operation:" COLOR_RESET "\n");
    printf(COLOR_YELLOW "[1]" COLOR_RESET " Add Row\n");
    printf(COLOR_YELLOW "[2]" COLOR_RESET " Add Column\n");
    printf(COLOR_YELLOW "[3]" COLOR_RESET " Delete Row\n");
    printf(COLOR_YELLOW "[4]" COLOR_RESET " Average\n");
    printf(COLOR_YELLOW "[5]" COLOR_RESET " Sum\n");
    printf(COLOR_YELLOW "[6]" COLOR_RESET " Min\n");
    printf(COLOR_YELLOW "[7]" COLOR_RESET " Max\n");
    printf(COLOR_YELLOW "[8]" COLOR_RESET " Help\n");
    printf(COLOR_GREEN  "[9] Save (Rewrite)" COLOR_RESET "\n");
    printf(COLOR_RED    "[0] Exit & Save" COLOR_RESET "\n");
    printf(STYLE_BOLD "\nYour Choice > " COLOR_RESET);
}

void printSuccess(const char *msg) {
    printf(COLOR_GREEN "[SUCCESS] %s" COLOR_RESET "\n", msg);
}

void printError(const char *msg) {
    printf(COLOR_RED "[ERROR] %s" COLOR_RESET "\n", msg);
}