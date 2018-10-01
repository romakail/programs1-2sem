#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int main()
{
    FILE* ptrFile1 = fopen ("veldt.txt", "r");
    assert (ptrFile1);
    rewind (ptrFile1);

    FILE* ptrFile2 = fopen ("newveldt.txt", "w");
    assert (ptrFile2);
    rewind (ptrFile2);

    char symbol = 0;


//    fprintf (ptrFile2, "    ");
    while (symbol != '$')
    {
        fscanf (ptrFile1, "%c", &symbol);
        if ((ispunct(symbol) != 0) || (symbol == '\n') || (symbol == ' ') || (symbol == '—'))
        {
            fprintf(ptrFile2, "%c", ' ');
            fscanf (ptrFile1, "%c", &symbol);
            while ((ispunct(symbol) != 0) || (symbol == '\n') || (symbol == ' ')  || (symbol == '—'))
            {
                fscanf (ptrFile1, "%c", &symbol);
            }
            fseek (ptrFile1, -1, SEEK_CUR);

        }
        else
        {
            fprintf(ptrFile2, "%c", symbol);
        }

        //fseek (ptrFile1, 1, SEEK_CUR);

    }

    fprintf(ptrFile2, "\0$\0");
    fclose (ptrFile1);
    fclose (ptrFile2);
    return 0;
}
