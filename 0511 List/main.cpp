#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>

#include "list.h"


int main()
{
    list_t rList;
    constructList (&rList, 0);
    addToBeginning(&rList, 10);
    addToBeginning(&rList, 11);
    addToBeginning(&rList, 12);
    addToBeginning(&rList, 13);
    addToEnd      (&rList, 80);
    addToEnd      (&rList, 80);
    addToEnd      (&rList, 80);
    addToEnd      (&rList, 90);
    deleteElem    (&rList, rList.tail);
    deleteElem    (&rList, rList.tail);
    deleteElem    (&rList, rList.tail);
    deleteElem    (&rList, rList.tail);
    changeElem    (&rList, 100, rList.tail);


    //int a = listOK (&rList);
    printf ("\n\n--ListOK returned : %d", listOK (&rList));

    //dumpList (&rList);
    dumpWithDot(&rList);
}


