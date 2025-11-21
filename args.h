#ifndef ARGS_H
#define ARGS_H

// Structure to hold program arguments: input and output file paths.
// These are pointers to strings from argv (not owned, not freed).
typedef struct
{
    const char *input_file;
    const char *output_file;
} ProgramArgs;

// Checks if the given argument matches the expected key.
// Example: checkArgument("--input","--input") → returns 1, otherwise 0.
int checkArgument(const char *argument, const char *expected_key);

// Parses command-line arguments and stores input/output file paths in ProgramArgs.
// Supports both long (--input, --output) and short (-i, -o) options.
// Returns 0 on success, non-zero on error.
int workArgs(int argc, char **argv, ProgramArgs *args);

#endif