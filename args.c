#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "args.h"

int checkArgument(const char *argument, const char *expected_key)
{
    if (argument == NULL)
    {
        return 0;
    }

    if (strcmp(argument, expected_key) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int workArgs(int argc, char **argv, ProgramArgs *args)
{
    args->input_file = NULL;
    args->output_file = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (checkArgument(argv[i], "--input") || checkArgument(argv[i], "-i"))
        {
            if (args->input_file != NULL)
            {
                fprintf(stderr, "Error! --input.\n");
                return 1;
            }

            if (i + 1 >= argc)
            {
                fprintf(stderr, "Error! --input.\n");
                return 1;
            }

            args->input_file = argv[++i];
        }



        else if (checkArgument(argv[i], "--output") || checkArgument(argv[i], "-o"))
        {
            if (args->output_file != NULL)
            {
                fprintf(stderr, "Error! --output.\n");
                return 1;
            }

            if (i + 1 >= argc)
            {
                fprintf(stderr, "Error! --output.\n");
                return 1;
            }
            args->output_file = argv[++i];
        }



        else
        {
            fprintf(stderr, "Error! Unknown argument %s\n", argv[i]);
            return 1;
        }
    }

    if (args->input_file == NULL || args->output_file == NULL)
    {
        fprintf(stderr, "Error: please specify both --input and --output arguments.\n");
        return 1;
    }

    return 0;
}