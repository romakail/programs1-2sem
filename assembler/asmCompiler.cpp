
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>

#include "asmCompiler.h"

#include "compilercommands.h"

int Compile ()
{
    printf ("lalala");
    FILE * ptrSource       = fopen ("asmCode.txt",   "rb");
    assert (ptrSource);
    rewind (ptrSource);

    FILE * ptrProcCommands = fopen ("ProcCommands.txt", "wb");
    assert (ptrProcCommands);
    rewind (ptrProcCommands);

    char labelName [MAXCHARS] = {};
    int counter1 = 0;
    int counter2 = 0;
    labelNames_t names [MAXLABELS] = {};
    while (strcmp ( labelName, "End") != 0)
    {
        fscanf (ptrSource, "%s", labelName);
        if ( strcmp (labelName, "label") == 0)
        {
            fscanf (ptrSource, "%s", names[counter2].labelName);
            names[counter2].commandNumber = ++counter1;
            counter2++;
        }
        counter1 ++;
    }

    for (int i = 0; i < MAXLABELS; i++)
    {
        printf ("\n[%d] %s  %lg\n", i, names[i].labelName, names[i].commandNumber );
    }

    rewind (ptrSource);


    bool endOfProg = 0;
    int nCommands = 0;
    double temp = 0;
    int temp2 = 0;
    while (endOfProg == 0)
    {
        fscanf (ptrSource, "%s", labelName);
        nCommands++;

        if (0);

        #define DEF_CMD(number, type)                       \
            else if (strcmp (labelName, #type) == 0)       \
            {                                               \
                fprintf (ptrProcCommands, "%d  ", number);  \
                                                            \
                DEF_##type                                  \
            }

        #include "assemblerСommands.h"

        #undef DEF_CMD

        else
        {
            printf ("\n\nCOMPILATION ERROR\ni can`t understand what is '%s'\n\n", labelName);
            assert (0);
        }


        fprintf (ptrProcCommands, "\r\n");


    }
    fclose (ptrSource);
    fclose (ptrProcCommands);
    printf ("\n--compiled--\n");
    return nCommands;
}

//---------------------------------------------------------------------------------------

double nameInNumber (char* name, labelNames_t* names)
{
    int counter = 0;
    while (strcmp(names[counter].labelName, name) != 0)
        counter++;
    printf ("\n--%s  %lg", names[counter].labelName, names[counter].commandNumber);
    return names[counter].commandNumber;
}








