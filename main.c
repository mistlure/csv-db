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
    


    freeCSV(&db);
    return 0;
}
