#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include "Stack.h"


int main()
{

    Stack<int, 10>  intStack;

    intStack.push(10);
    intStack.push(15);

    intStack.dumpStack();

    //printf ("%d \n%d", intStack.pop(), intStack.pop());

    //int smth = intStack.pop ();

    return 0;
}
