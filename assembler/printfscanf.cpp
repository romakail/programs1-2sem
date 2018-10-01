#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>

#include "printfscanf.h"

void fscanfElem_t (float* data, FILE* ptrfile)
{
    fscanf (ptrfile, "%f", data);
}

void fscanfElem_t (int* data, FILE* ptrfile)
{
    fscanf (ptrfile, "%d", data);
}

void fscanfElem_t (double* data, FILE* ptrfile)
{
    fscanf (ptrfile, "%lg", data);
}

//----------------------------------------------------------------------

void printfElem_t (float data)
{
    printf ("%f\n", data);
}

void printfElem_t (int data)
{
    printf ("%d\n", data);
}

void printfElem_t (double data)
{
    printf ("%lg\n", data);
}

