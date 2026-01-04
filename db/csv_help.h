#ifndef CSV_HELP_H
#define CSV_HELP_H

#include <stddef.h>
#include "csv_base.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"

#define COLOR_RESET   "\x1b[0m"
#define STYLE_BOLD    "\x1b[1m"

// Splits a line into tokens
char **splitLine(const char *line, const char *delimiters, size_t *count);

// Finds the index of a column by its name. Returns -1 if not found.
int getColumnIndex(const CSV *db, const char *columnName);

// Converts a string to a double number. Returns 0.0 if conversion fails.
double stringToDouble(const char *string);

//

// Clears the terminal screen
void clearScreen();

// Prints the application header with file info
void printHeader(const char *in, const char *out);

// Prints the help list of commands
void printHelp();

// Prints the interactive menu options
void printMenu();

// Prints a success message in green
void printSuccess(const char *msg);

// Prints an error message in red
void printError(const char *msg);

#endif