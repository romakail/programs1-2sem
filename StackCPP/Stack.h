#include <stdio.h>
#include <assert.h>
#include <iostream>



enum errorTypes
{
    POINTERNULL   = 1,
    COUNTERLESS0  = 2,
    DATAPOINTER0  = 3,
    TOOBIGCOUNTER = 4,
    HASHPROBLEM   = 5,
    CANARYPROBLEM = 6
};

//------------------------------------------------------------------------------------------------------------
/*
int printfElem_t (int element);
int printfElem_t (double element);
int printfElem_t (char element);
int printfElem_t (char* element);
*/


//------------------------------------------------------------------------------------------------------------

 template < class Elem_t, unsigned int sizeOfStack >

 class Stack
{

private:

    Elem_t* data = nullptr;
    unsigned int counter = 0;

    double canary1 = 0;
    double canary2 = 0;
    double canary3 = 0;
    double canary4 = 0;

    double canary (int number);
    int stackOK ();

public:

    Stack  ();
    ~Stack ();

    int dumpStack();

    int push (const Elem_t value);
    Elem_t pop ();
};



//-------------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
Stack < Elem_t, sizeOfStack >:: Stack ()
{
    data = (Elem_t*) calloc (sizeOfStack, sizeof (Elem_t));
    assert (data);

    counter = 0;

    canary1 = canary (1);
    canary2 = canary (2);
    canary3 = canary (3);
    canary4 = canary (4);


}

//-------------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
Stack < Elem_t, sizeOfStack >:: ~Stack ()
{
    free (data);
}

//-------------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
int Stack < Elem_t, sizeOfStack >:: push (const Elem_t value)
{
    data [counter ++] = value;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
Elem_t Stack < Elem_t, sizeOfStack >:: pop ()
{
    Elem_t temp = data [--counter];
    data [counter] = 0;

    //printfElem_t (temp);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
int Stack < Elem_t, sizeOfStack >:: stackOK ()
{
    if (counter <  0   )
        return COUNTERLESS0 ;

    else if (data   == NULL)
        return DATAPOINTER0 ;

    else if (counter > sizeOfStack)
        return TOOBIGCOUNTER;

    //else if (isNull (rStack->hesh - mathHash (rStack)) == 1)
    //    return HASHPROBLEM  ;

    else if ((canary1 != canary (1)) ||
             (canary2 != canary (2)) ||
             (canary3 != canary (3)) ||
             (canary4 != canary (4)) )
        return CANARYPROBLEM;

    else
        return 0;
}

//-------------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
double Stack < Elem_t, sizeOfStack >:: canary (int number)
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

    return 0;
}

//----------------------------------------------------------------------------------------------------------------

template < typename Elem_t, unsigned int sizeOfStack >
int Stack < Elem_t, sizeOfStack >:: dumpStack ()
{
    printf ("\n\nsize of stack is : %d\n", sizeOfStack);
    printf ("counter is : %d\n", counter);
    for (int i = 0; i < sizeOfStack; i++)
    {
        printf ("[%d]  ", i);
        printfElem_t (data[i]);
    }
    printf ("\ncanary 1 is %s"  , (canary1 == canary (1)) ? "OK" : "NOT OK");
    printf ("\ncanary 2 is %s"  , (canary2 == canary (2)) ? "OK" : "NOT OK");
    printf ("\ncanary 3 is %s"  , (canary3 == canary (3)) ? "OK" : "NOT OK");
    printf ("\ncanary 4 is %s\n", (canary4 == canary (4)) ? "OK" : "NOT OK");

    return 0;
}

//------------------------------------------------------------------------------------------------------------------

template < typename Elem_t = int, unsigned int sizeOfStack >
void printfElem_t (Elem_t element)
{
    printf ("%d", element);
}
/*
void printfElem_t (double element)
{
    printf ("%lg", element);
}

void printfElem_t (char element)
{
    printf ("%c", element);
}

void printfElem_t (char* element)
{
    printf ("%s", element);
}
*/












