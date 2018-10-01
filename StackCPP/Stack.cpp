#include "Stack.h"

#ifdef ROMANEZNAETCPP

template < typename Elem_t, unsigned int lenght >
int Stack < Elem_t, lenght >:: push (const Elem_t value)
{
    data [counter ++] = value;
    return 0;
}

//-------------------------------------------------------------------------------

template < typename Elem_t, unsigned int lenght >
Elem_t Stack < Elem_t, lenght >:: pop ()
{
    Elem_t temp = data [--counter];
    data [counter] = 0;
    return temp;
}

#endif
