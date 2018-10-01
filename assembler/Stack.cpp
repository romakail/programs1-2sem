#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>
#include <math.h>
#include <ctime>

#include "Stack.h"
#include "printfscanf.h"


int  constructStack (Stack_t* rStack,int sizeOfStack)
{
    //_txlib_precondition (rStack, return );
    assert (sizeOfStack > 0);
    rStack->data        = (Elem_t*) calloc (sizeOfStack, sizeof (Elem_t));
    assert (rStack->data); // must be if
    if (rStack->data == 0)
    {
        printf ("I can`t construct stack\nProblems with calloc\n");
        printf ("Calloc returned : %d", rStack->data);
    }

    rStack->counter     = 0;
    rStack->sizeOfStack = sizeOfStack;

    rStack->canary1 = canary (1);
    rStack->canary2 = canary (2);
    rStack->canary3 = canary (3);
    rStack->canary4 = canary (4);

    calculateHash (rStack);

    CARSKYASSERT_OK
    return 0;
}

//----------------------------------------------------------------------

int destructStack (Stack_t* rStack)
{
    CARSKYASSERT_OK

    free (rStack);
    return 0;
}

//----------------------------------------------------------------------

int stackPush (Stack_t* rStack, Elem_t value)
{
    CARSKYASSERT_OK

    rStack->data [rStack->counter++] = value;

    calculateHash (rStack);

    CARSKYASSERT_OK
    return 0;
}

//----------------------------------------------------------------------

Elem_t stackPop (Stack_t* rStack)
{
    CARSKYASSERT_OK

    Elem_t temp = rStack->data [--rStack->counter];
    rStack->data [rStack->counter] = 0;

    calculateHash(rStack);

    CARSKYASSERT_OK

    return temp;

}

//----------------------------------------------------------------------

int stackOK (Stack_t* rStack)
{
    if      (rStack          == NULL)
        return POINTERNULL  ;

    else if (rStack->counter <  0   )
        return COUNTERLESS0 ;

    else if (rStack->data   == NULL)
        return DATAPOINTER0 ;

    else if (rStack->counter >  rStack->sizeOfStack)
        return TOOBIGCOUNTER;

    else if (isNull (rStack->hesh - mathHash (rStack)) == 1)
        return HASHPROBLEM  ;

    else if ((rStack->canary1 != canary (1)) ||
             (rStack->canary2 != canary (2)) ||
             (rStack->canary3 != canary (3)) ||
             (rStack->canary4 != canary (4)) )
        return CANARYPROBLEM;

    else
        return 0;
}

//----------------------------------------------------------------------

double canary (int number)
{
    static double canary1 = rand ();
    static double canary2 = rand ();
    static double canary3 = rand ();
    static double canary4 = rand ();

    switch ( number )
    {
        case 1 : return canary1;
                 break;
        case 2 : return canary2;
                 break;
        case 3 : return canary3;
                 break;
        case 4 : return canary4;
                 break;
    }
}


//----------------------------------------------------------------------
int dumpStack (Stack_t* rStack)
{
    printf ("\n\nsize of stack is : %d\n", rStack->sizeOfStack);
    printf ("counter is : %d\n", rStack->counter);
    for (int i = 0; i < rStack->sizeOfStack; i++)
    {
        printf ("[%d]  ", i);
        printfElem_t (rStack->data[i]);
    }
    printf ("\ncanary 1 is %s"  , (rStack->canary1 == canary (1)) ? "OK" : "NOT OK");
    printf ("\ncanary 2 is %s"  , (rStack->canary2 == canary (2)) ? "OK" : "NOT OK");
    printf ("\ncanary 3 is %s"  , (rStack->canary3 == canary (3)) ? "OK" : "NOT OK");
    printf ("\ncanary 4 is %s\n", (rStack->canary4 == canary (4)) ? "OK" : "NOT OK");

    return 0;
}

//------------------------------------------------------------------------

int   calculateHash    (Stack_t* rStack)
{
    rStack->hesh = mathHash ( rStack );
    return 0;
}

//------------------------------------------------------------------------

int  mathHash   (Stack_t* rStack)
{
    int hashValue = 0;
    for (int i = 0; i < (sizeof (Stack_t)) / (sizeof(int)); i++)
    {
        hashValue += *((int*)rStack + i);
    }
    for (int i = 0; i < (rStack->sizeOfStack)*(sizeof(Elem_t))/(sizeof(int)) ; i++)
    {
        hashValue += *((int*)rStack->data + i);
    }
    return hashValue;

}

//---------------------------------------------------------------------------

bool isNull (double number)
{
    if ( fabs (number) > EPSILON)
        return 0;
    else
        return 1;
}

//------------------------------------------------------------------------------



