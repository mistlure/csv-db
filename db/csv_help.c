#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "csv_help.h"

char **splitLine(const char *line, const char *delimiters, size_t *count)
{
    // Default delimiter value.
    if (!delimiters) delimiters = ",";

    char **parts = NULL;
    size_t used = 0;
    const char *p = line;

    while (*p)
    {
        // Skip delimiter characters.
        while (*p && strchr(delimiters, *p))
        {
            p++;
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

        // Copy token characters into new string.
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



        // Expand array to hold one more token.
        char **tmp = realloc(parts, (used + 1) * sizeof(char *));
        if (!tmp)
        {
            for (size_t i = 0; i < used; i++) free(parts[i]);
            free(parts);
            free(token);
            return NULL;
        }
        parts = tmp;

        parts[used++] = token;
    }
    *count = used;
    return parts;
}