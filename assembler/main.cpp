#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>

#include "Stack.h"
#include "printfscanf.h"
#include "Processor.h"
#include "asmCompiler.h"

#define writeline()                 \
do {                                \
    printf("LINE #%d\n", __LINE__); \
} while (0)



/*typedef double Elem_t;
struct Stack_t
{
    Elem_t* data;
    int counter;
    int sizeOfStack;
};*/

//void   workWithStack    (Stack_t* rStack);

//void    constructStack   (Stack_t* rStack, int* sizeOfStack);
//void   stackPush        (Stack_t* rStack, Elem_t value);
//Elem_t stackPop         (Stack_t* rStack);
//void   stackAddition    (Stack_t* rStack);
//void   stackDifference  (Stack_t* rStack);
//void   stackComposition (Stack_t* rStack);
//void   stackDivision    (Stack_t* rStack);

//bool   stackOK          (const Stack_t* rStack);

/*void   fscanfElem_t     (float* data, FILE* ptrfile);
void   fscanfElem_t     (int* data, FILE* ptrfile);
void   fscanfElem_t     (double* data, FILE* ptrfile);

void   printfElem_t     (float data);
void   printfElem_t     (int data);
void   printfElem_t     (double data);*/

//void dumpStack        (Stack_t* rStack);

int main ()
{

    assemble ();

    /*Stack_t rStack      = {};
    Stack_t label       = {};

    int nCommands = Compile ();

    constructStack(&rStack, SIZEOFRSTACK);
    constructStack(&label , MAXLABELS );
    Elem_t* commandsMassive = NULL;
    constructCommandsMassive (nCommands, &commandsMassive);
    workWithStack   (&rStack, &label, commandsMassive);
    return 0;*/
    return 0;
}

//----------------------------------------------------------------------
/*
void  constructStack (Stack_t* rStack,int* sizeOfStack)
{
    assert (stackOK (rStack));
    //Stack_t* rStack = calloc
    rStack->data        = (Elem_t*) calloc (*sizeOfStack, sizeof (Elem_t));
    assert (rStack->data);

    rStack->counter     = 0;
    rStack->sizeOfStack = *sizeOfStack;

    assert (stackOK (rStack));
}

//----------------------------------------------------------------------

void stackPush (Stack_t* rStack, Elem_t value)
{
    assert (stackOK (rStack));

    rStack->data [rStack->counter++] = value;

    assert (stackOK (rStack));
}

//----------------------------------------------------------------------

Elem_t stackPop (Stack_t* rStack)
{
    assert (stackOK (rStack));

    Elem_t temp = rStack->data [--rStack->counter];
    rStack->data [rStack->counter] = 0;

    assert (stackOK (rStack));

    return temp;

}
*/
//----------------------------------------------------------------------
/*
void stackAddition (Stack_t* rStack)
{
    assert (stackOK (rStack));

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term1+term2);

    assert (stackOK (rStack));
}

//----------------------------------------------------------------------

void stackDifference (Stack_t* rStack)
{
    assert (stackOK (rStack));

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2-term1);

    assert (stackOK (rStack));
}

//----------------------------------------------------------------------

void stackComposition (Stack_t* rStack)
{
    assert (stackOK (rStack));

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2*term1);

    assert (stackOK (rStack));
}

//----------------------------------------------------------------------

void stackDivision (Stack_t* rStack)
{
    assert (stackOK (rStack));

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2/term1);

    assert (stackOK (rStack));
}
*/
//----------------------------------------------------------------------
/*
bool stackOK(const Stack_t* rStack)
{
    return (rStack          != NULL) &&
           (rStack->counter >= 0   ) &&
           (&rStack->data   != NULL) &&
           (rStack->counter <= rStack->sizeOfStack);
}
*/
//----------------------------------------------------------------------
/*
void dumpStack (Stack_t* rStack)
{
    printf ("\n\nsize of stack is : %d\n", rStack->sizeOfStack);
    printf ("counter is : %d\n", rStack->counter);
    for (int i = 0; i < rStack->sizeOfStack; i++)
        printfElem_t (rStack->data[i]);
}
*/
//---------------------------------------------------------------------
/*
void workWithStack (Stack_t* rStack)
{
    FILE* ptrFile = NULL;
    ptrFile = fopen ( "StackCommands.txt", "rb");
    printf ("%d\n\n", ptrFile);
    assert (ptrFile);
    fseek (ptrFile, 0, SEEK_SET);

    bool out = 0;
    int command = 0;
    Elem_t temp = 0;
    while (out == 0)
    {
        fscanf (ptrFile, "%d", &command );
        //printf ("\ncommand number is %d\n", command);
        switch (command)
        {
            case 1 : fscanfElem_t (&temp, ptrFile);
                     stackPush (rStack, temp);
                     break;

            case 2 : printfElem_t (stackPop (rStack));
                     break;

            case 3 : stackAddition    (rStack);
                     break;

            case 4 : stackDifference  (rStack);
                     break;

            case 5 : stackComposition (rStack);
                     break;

            case 6 : stackDivision    (rStack);
                     break;

            case 7 : out = 1;
                     break;

            default: out = 1;
                     printf ("NO command found");
                     exit (1);
        }
    }
    dumpStack(rStack);


}
*/
//----------------------------------------------------------------------
/*
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


*/
