#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>
#include <math.h>
//#include <txlib>

#include "Stack.h"
#include "printfscanf.h"
#include "Processor.h"
#include "asmCompiler.h"


int assemble ()
{
    Stack_t rStack      = {};
    Stack_t label       = {};

    int nCommands = Compile ();

    constructStack(&rStack, SIZEOFRSTACK);
    constructStack(&label , MAXLABELS );
    Elem_t* commandsMassive = NULL;
    constructCommandsMassive (nCommands, &commandsMassive);
    workWithStack   (&rStack, &label, commandsMassive);
    return 0;
}
/*#define CARSKYASSERT_OK                                      \
if (stackOK (rStack) != 0)                                   \
{                                                            \
    printf ("\n------------ERROR-----------------\n\n");     \
    printf ("errorNumber : %d\n", stackOK (rStack));         \
    dumpStack(rStack);                                       \
    assert (0);                                              \
};*/

#include "processorCommands.h"

int   constructCommandsMassive (int nCommands, Elem_t** commandsMassive)
{
    *commandsMassive = (Elem_t*) calloc (nCommands, sizeof (Elem_t));
    assert (commandsMassive);
    //printf ("\n commandsMassive : %d\n", commandsMassive);

    FILE* ptrFile = fopen ( "ProcCommands.txt", "r");
    assert (ptrFile);
    rewind (ptrFile);

    Elem_t temp = 0;
    for (int i = 0; i < nCommands; i++)
    {
        fscanfElem_t (&temp, ptrFile);
        (*commandsMassive) [i] = temp;
        printf ("\n%lg", (*commandsMassive) [i]);
    }
    fclose (ptrFile);

    return 0;
}

//---------------------------------------------------------------------------------------

int workWithStack (Stack_t* rStack, Stack_t* label, Elem_t* commandsMassive)
{
    Elem_t a = 0;  //registers
    Elem_t b = 0;
    Elem_t c = 0;
    Elem_t d = 0;

    Elem_t operMemory [MEMORY_LENGHT] = {POISON};

    Stack_t funcStack = {};      //for functions
    constructStack(&funcStack, MAX_FUNCTIONS);

    bool   out     = 0;
    int    i       = 0;
    Elem_t temp    = 0;

    printf ("\n\n---RESULT IS---\n");
    while (out == 0)
    {
        switch ( (int)commandsMassive [i])
        {

        #define DEF_CMD(number, type)   \
            case number : DEF_##type    \
                        break;

        #include "assemblerСommands.h"


        #undef DEF_CMD

        }
        i++;
    }

    //dumpStack(rStack);
    return 0;
}

//----------------------------------------------------------------------

int stackAddition (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term1+term2);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//----------------------------------------------------------------------

int stackDifference (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2-term1);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//----------------------------------------------------------------------

int stackComposition (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2*term1);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//----------------------------------------------------------------------

int stackDivision (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    assert (1 - isNull (term1));
    stackPush (rStack, term2/term1);

    calculateHash (rStack);

    CARSKYASSERT_OK
    return 0;
}

//-----------------------------------------------------------------------------

int   stackSqrt        (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t temp = stackPop (rStack);
    stackPush (rStack, sqrt (temp));

    calculateHash (rStack);

    CARSKYASSERT_OK
    return 0;
}

//---------------------------------------------------------------------------------

int stackEqual (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, isNull(term2 - term1));

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//---------------------------------------------------------------------------------

int stackNotEqual (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, fabs (1 - isNull(term2 - term1)));

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//---------------------------------------------------------------------------------

int stackMore (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2 > term1);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//---------------------------------------------------------------------------------

int stackMoreEqual (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2 >= term1);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//---------------------------------------------------------------------------------

int stackLess (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2 < term1);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

//---------------------------------------------------------------------------------

int stackLessEqual (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t term1 = stackPop (rStack);
    Elem_t term2 = stackPop (rStack);

    stackPush (rStack, term2 <= term1);

    calculateHash(rStack);

    CARSKYASSERT_OK
    return 0;
}

