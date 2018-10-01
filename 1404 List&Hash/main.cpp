#include <stdio.h>
#include "Hash.h"

int main ()
{

    hashTable Table (30);
    fillHashTable(&Table, calcHash2);


    //Table.dumpListWithDot(12);

    int a = Table.searchElement(calcHash2, "it");
    printf ("result is %d\n", a);

    //Table.texDump();
    speedTest (&Table, calcHash2);

    printf ("C`est finit\n");
    return 0;
}
