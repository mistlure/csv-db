#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "csv_base.h"
#include "csv_io.h"
#include "csv_math.h"
#include "csv_edit.h"

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


        char *arg = strtok(NULL, " ");
        char *val = strtok(NULL, "");
        if (val && *val == ' ') val++;

        if (strcmp(cmd, "exit") == 0)
        {
            printf("Saving... (%s)\n", args.output_file);
            if (saveCSVFile(args.output_file, &db) != 0)
            {
                fprintf(stderr, "Error saving file!\n");
            }
            break;
        }
        else if (strcmp(cmd, "average") == 0)
        {
            avgF(&db, arg);
        }
        else if (strcmp(cmd, "sum") == 0)
        {
            sumF(&db, arg);
        }
        else if (strcmp(cmd, "min") == 0)
        {
            minF(&db, arg);
        }
        else if (strcmp(cmd, "max") == 0)
        {
            maxF(&db, arg);
        }
        else if (strcmp(cmd, "addrow") == 0)
        {
            addRow(&db, arg);
        }
        else if (strcmp(cmd, "addcol") == 0)
        {
            addCol(&db, arg, val);
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
