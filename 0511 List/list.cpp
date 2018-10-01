#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>
#include <ctime>

#include "list.h"

//Address sanitizer
//Valgrind
//------------------------------------------------------------------------------

int constructList (list_t* rList, Elem_t data)
{
    assert (rList);
    list_elem_t* firstElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
    assert (firstElement);

    rList->head        = firstElement;
    rList->tail        = firstElement;
    rList->nElements   = 1;

    firstElement->data = data;
    firstElement->next = NULL;
    firstElement->prev = NULL;

    return 0;
}

//------------------------------------------------------------------------------

int addElemAfter (list_t* rList, Elem_t data, list_elem_t* prevElement)
{
    assert (rList);
    assert (prevElement);

    list_elem_t* addedElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
    assert (addedElement);
    addedElement->data = data;

    if      (prevElement->next == NULL)
    {
        prevElement ->next = addedElement;            //connection with previous element
        addedElement->prev = prevElement;
        addedElement->next = NULL;

        rList       ->tail = addedElement;
    }

    else if (prevElement->next != NULL)
    {
        addedElement->next      = prevElement->next;  //connection with next element
        prevElement->next->prev = addedElement;

        addedElement->prev      = prevElement;        //connection with previous element
        prevElement ->next      = addedElement;
    }

    rList->nElements++;
    return 0;
}

//------------------------------------------------------------------------------

int addElemBefore (list_t* rList, Elem_t data, list_elem_t* nextElement)
{
    assert (rList);
    assert (nextElement);

    list_elem_t* addedElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
    assert (addedElement);
    addedElement->data = data;

    if      (nextElement->prev == NULL)
    {
        nextElement ->prev = addedElement;            //connection with next element
        addedElement->next = nextElement;
        addedElement->prev = NULL;

        rList       ->head = addedElement;
    }

    else if (nextElement->prev != NULL)
    {
        addedElement->prev      = nextElement->prev;  // connection with previous element
        nextElement->prev->next = addedElement;

        addedElement->next      = nextElement;        // connection with next element
        nextElement ->prev      = addedElement;
    }

    rList->nElements++;
    return 0;
}

//----------------------------------------------------------------------------------

int changeElem (list_t* rList, Elem_t data, list_elem_t* element)
{
    assert (rList);
    assert (element);

    element->data = data;
    return 0;
}

//-----------------------------------------------------------------------------------

int deleteElem (list_t* rList, list_elem_t* deletedElement)
{
    assert (rList);
    assert (deletedElement);

    if     ((deletedElement->next == NULL) && (deletedElement->prev == NULL))
        return 1;
    else if (deletedElement->next == NULL)
    {
        deletedElement->prev->next = NULL;
        rList->tail = deletedElement->prev;
    }
    else if (deletedElement->prev == NULL)
    {
        deletedElement->next->prev = NULL;
        rList->head = deletedElement->next;
    }
    else
    {
        deletedElement->prev->next = deletedElement->next;
        deletedElement->next->prev = deletedElement->prev;
    }
    free (deletedElement);
    rList->nElements--;

    // S1 2:54
    return 0;
}

//--------------------------------------------------------------------------------------------------

int dumpList (list_t* rList)
{
    assert (rList);

    printf ("\nNumber of elements in list is : %d\n", rList->nElements);
    list_elem_t* ptrElem = rList->head;
    printf ("head pointer is %p\n", rList->head);
    for (int counter = 0; counter < rList->nElements; counter++)
    {
        printf ("element [%d] is %lg\n"  , counter + 1, ptrElem->data);
        printf ("prev pointer is %p\n"   , ptrElem->prev);
        printf ("elem pointer is %p\n"   , ptrElem);
        printf ("next pointer is %p\n\n" , ptrElem->next);

        ptrElem = ptrElem->next;
    }
    printf ("tail pointer is %p\n", rList->tail);

    return 0;
}

//------------------------------------------------------------------------------------

int dumpWithDot (list_t* rList)
{
    assert (rList);

    list_elem_t* ptr = rList->head;
    FILE* ptrFile = fopen ("Dump.txt", "w");
    assert (ptrFile);
    rewind (ptrFile);

    fprintf (ptrFile, "digraph Elements{\n");
    fprintf (ptrFile, "rankdir=HR;\n");

    fprintf (ptrFile, "error [shape=record,label=\"error detector returned : %d\"];\n ", listOK (rList));
    fprintf (ptrFile, "head [shape=record,label=\"head\\n%p | tail\\n%p | nElement\\n%d\"];\n", rList->head, rList->tail, rList->nElements);

    for (int i = 0; i < rList->nElements; i++)
    {
        fprintf (ptrFile, "elem%d [shape=record,label=\"<pt> ptr\\n %p | data\\n %lg |<n> next\\n %p |<p> prev\\n%p\" ];\n", i, ptr, ptr->data, ptr->next, ptr->prev);
        if (ptr->next != NULL)
            ptr = ptr->next;
    }
    for (int i = 0; i < rList->nElements-1; i++)
    {
        fprintf (ptrFile, "elem%d:<n>->elem%d:<pt>;\n", i, i+1);
        if (ptr->next != NULL)
            ptr = ptr->next;
    }
    for (int i = 0; i < rList->nElements-1; i++)
    {
        fprintf (ptrFile, "elem%d:<p>->elem%d:<pt>;\n", i+1, i);
        if (ptr->next != NULL)
            ptr = ptr->next;
    }

    fprintf (ptrFile, "}");

    fclose (ptrFile);

    system ("dot -Tpng Dump.txt -o Dump.png");
    system ("xdot Dump.txt");

    return 0;
}

//------------------------------------------------------------------------------------

int listOK (list_t * rList)
{
    assert (rList);

    if      (checkCycle (rList) == 1)
        return CYCLE;
    else if (rList->nElements != nElements (rList))
        return NELEMENTS;
    else if (checkConnections (rList) != 0)
        return CONNECTIONS;
    else
        return 0;
}

//------------------------------------------------------------------------------------

int checkCycle (list_t* rList)
{
    assert (rList);

    list_elem_t* ptr1 = rList->head;
    list_elem_t* ptr2 = rList->head;
    int out = 0;

    while (out == 0)
    {
        if (ptr2 == NULL)
            out = 1;
        else
            ptr2 = ptr2->next;

        if (ptr2 == NULL)
            out = 1;
        else
            ptr2 = ptr2->next;

        if (ptr1 != NULL)
            ptr1 = ptr1->next;

        if (ptr1 == ptr2)
            out = 2;
    }
    if      (out == 2)
        return 1;
    else if (out == 1)
        return 0;
}

//------------------------------------------------------------------------------------

int nElements (list_t* rList)
{
    assert (rList);

    int counter = 1;
    list_elem_t* ptr = rList->head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        counter++;
    }
    return counter;
}
//------------------------------------------------------------------------------------

int checkConnections (list_t* rList)
{
    assert (rList);
    list_elem_t* ptr = rList->head;

    while (ptr->next != NULL)
    {
        if (ptr->prev != NULL)
        {
            if (ptr != ptr->prev->next)
                return 1;
        }
        if (ptr->next != NULL)
        {
            if (ptr != ptr->next->prev)
                return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}



//------------------------------------------------------------------------------------

int addToBeginning (list_t* rList, Elem_t data)
{
    assert (rList);

    if (addElemBefore(rList, data, rList->head) == 0)
        return 0;
    else
        return 1;
}

//-------------------------------------------------------------------------------------

int addToEnd (list_t* rList, Elem_t data)
{
    assert (rList);

    if (addElemAfter(rList, data, rList->tail) == 0)
        return 0;
    else
        return 1;
}















