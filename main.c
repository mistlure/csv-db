#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "csv_base.h"
#include "csv_io.h"
#include "csv_math.h"
#include "csv_edit.h"
#include "csv_help.h"

int main(int argc, char **argv)
{
    ProgramArgs args;
    if (workArgs(argc, argv, &args) != 0) {
        return 1;
    }

    CSV db;
    if (loadCSVFile(args.input_file, &db) != 0) {
        return 1;
    }

    // Initial setup
    clearScreen();
    printHeader(args.input_file, args.output_file);
    printStats(args.input_file, &db);

    int mode = 0;
    printf("\n" STYLE_BOLD "Select Mode:" COLOR_RESET "\n");
    printf(COLOR_YELLOW "[1]" COLOR_RESET " Console Mode (Type commands manually)\n");
    printf(COLOR_YELLOW "[2]" COLOR_RESET " Interactive Menu (UI Mode)\n");
    printf("Mode > ");
    
    if (scanf("%d", &mode) != 1) mode = 1; 
    while (getchar() != '\n'); // Clear buffer

    char buffer[1024];
    char argBuf[512];
    char valBuf[512];

    if (mode == 1) 
    {
        printf("\n" COLOR_GREEN "[Console Mode Started]" COLOR_RESET ". Type " STYLE_BOLD "'!help'" COLOR_RESET " for commands.\n");
        while (1)
        {
            printf("\n" COLOR_CYAN "Console > " COLOR_RESET);

            if (!fgets(buffer, sizeof(buffer), stdin)) break;
            buffer[strcspn(buffer, "\n")] = 0;

            if (strlen(buffer) == 0) continue;

            char *cmd = strtok(buffer, " ");
            if (!cmd) continue;
            char *arg = strtok(NULL, " ");
            char *val = strtok(NULL, ""); 
            if (val && *val == ' ') val++;

            if (strcmp(cmd, "exit") == 0)
            {
                break;
            }
            else if (strcmp(cmd, "!help") == 0) 
            {
                printHelp();
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
            else if (strcmp(cmd, "delrow") == 0)
            {
                if (arg)
                {
                    delRow(&db, atoi(arg));
                }
                else printf(COLOR_RED "Error: Usage: delrow <index>\n" COLOR_RESET);
            }
            else 
            {
                printf(COLOR_RED "Unknown command '%s'. Try '!help'." COLOR_RESET "\n", cmd);
            }
        }
    }
    else 
    {
        int running = 1;
        while (running) 
        {
            clearScreen();
            printHeader(args.input_file, args.output_file);
            
            printMenu();
            
            int choice = -1;
            char choiceBuf[10];
            if (fgets(choiceBuf, sizeof(choiceBuf), stdin)) {
                choice = atoi(choiceBuf);
            }

            printf("\n"); 

            switch (choice) 
            {
                case 0: // Exit
                    running = 0;
                    break;

                case 1: // Add Row
                    printf("Enter row data (" STYLE_BOLD "comma separated" COLOR_RESET "): ");
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        addRow(&db, argBuf);
                        printSuccess("Operation attempted."); 
                    }
                    break;

                case 2: // Add Col
                    printf("Enter column name: ");
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        
                        printf("Enter column data (" STYLE_BOLD "comma separated" COLOR_RESET "): ");
                        if (fgets(valBuf, sizeof(valBuf), stdin))
                        {
                            valBuf[strcspn(valBuf, "\n")] = 0;
                            addCol(&db, argBuf, valBuf);
                            printSuccess("Operation attempted.");
                        }
                    }
                    break;
                
                case 3: // Delete Row
                    printf("Enter row index (0 to %zu): ", db.row_count > 0 ? db.row_count - 1 : 0);
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        delRow(&db, atoi(argBuf));
                    }
                    break;

                case 4: // Average
                    printf("Enter column name: ");
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        avgF(&db, argBuf);
                    }
                    break;
                
                case 5: // Sum
                    printf("Enter column name: ");
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        sumF(&db, argBuf);
                    }
                    break;

                case 6: // Min
                    printf("Enter column name: ");
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        minF(&db, argBuf);
                    }
                    break;

                case 7: // Max
                    printf("Enter column name: ");
                    if (fgets(argBuf, sizeof(argBuf), stdin))
                    {
                        argBuf[strcspn(argBuf, "\n")] = 0;
                        maxF(&db, argBuf);
                    }
                    break;

                case 8: // Help
                    printHelp();
                    break;

                default:
                    printError("Invalid option. Please try again.");
            }

            if(running)
            {
                printf("\n" STYLE_BOLD "Press [Enter] to continue..." COLOR_RESET);
                getchar(); 
            }
        }
    }

    printf("\n" COLOR_CYAN "Saving database to '%s'..." COLOR_RESET "\n", args.output_file);
    
    if (saveCSVFile(args.output_file, &db) != 0)
    {
        printError("Failed to save file!");
    } 
    else
    {
        printSuccess("Saved successfully. Goodbye!");
    }

    freeCSV(&db);
    return 0;
}