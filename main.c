#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "csv_base.h"

int main(int argc, char **argv)
{
    ProgramArgs args;
    if (workArgs(argc, argv, &args) != 0)
    {
        return 1;
    }

    CSV db;
    
    if (loadCSVFile(args.input_file, &db) != 0)
    {
        return 1;
    }

    printStats(args.input_file, &db);

    char buffer[1024];

    ///

    while (1)
    {
        printf("Enter command: ");

        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            break;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        char *cmd = strtok(buffer, " ");
        if (!cmd) continue;



        if (strcmp(cmd, "exit") == 0)
        {
            printf("Saving... (%s)\n", args.output_file);
            if (saveCSVFile(args.output_file, &db) != 0)
            {
                fprintf(stderr, "Error saving file!\n");
            }
            break;
        }
        else
        {
            printf("Undefined '%s' command.\n", cmd);
        }

        

    }

    ///

    freeCSV(&db);
    return 0;
}
