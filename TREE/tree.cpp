#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>

#include "tree.h"

//-----------------------------------------------------------------------------------------

int constructTree (tree_t* rTree, char firstElemData [MAX_CHARS])
{
    tree_elem_t* firstElement = (tree_elem_t*) calloc (1, sizeof (tree_elem_t));
    assert (firstElement);

    rTree->root      = firstElement;
    rTree->nElements = 1;

    firstElement->parent = NULL;
    firstElement->left   = NULL;
    firstElement->right  = NULL;
    strcpy (firstElement->data, firstElemData);

    return 0;
}

//---------------------------------------------------------------------------------------

int addElemLeft (tree_t* rTree, tree_elem_t* parentElement, char addedElemData [MAX_CHARS])
{
    tree_elem_t* addedElement = (tree_elem_t*) calloc (1, sizeof (tree_elem_t));
    assert (addedElement);

    parentElement->left = addedElement;

    addedElement->parent = parentElement;
    addedElement->left   = NULL;
    addedElement->right  = NULL;
    strcpy (addedElement->data, addedElemData);

    rTree->nElements++;
    return 0;
}

//----------------------------------------------------------------------------------------

int addElemRight (tree_t* rTree, tree_elem_t* parentElement, char addedElemData [MAX_CHARS])
{
    tree_elem_t* addedElement = (tree_elem_t*) calloc (1, sizeof (tree_elem_t));
    assert (addedElement);

    parentElement->right = addedElement;

    addedElement->parent = parentElement;
    addedElement->left   = NULL;
    addedElement->right  = NULL;
    strcpy (addedElement->data, addedElemData);

    rTree->nElements++;
    return 0;
}

//-----------------------------------------------------------------------------------------

int changeElemData (tree_t* rTree, tree_elem_t* element, char data [MAX_CHARS])
{
    strcpy (element->data, data);
    return 0;
}

//-----------------------------------------------------------------------------------------

int dumpWithDot (tree_t* rTree)
{
    tree_elem_t* ptr = rTree->root;

    FILE* ptrFile = fopen ("Dump.txt", "w");
    assert (ptrFile);
    rewind (ptrFile);

    fprintf (ptrFile, "digraph tree{\n");
    fprintf (ptrFile, "rankdir=HR;\n");
    fprintf (ptrFile, "head [label=\"nElements : %d\"];\n", rTree->nElements);

    fPrintfElem  ( ptr, ptrFile);
    fPrintfArrow ( ptr, ptrFile);

    /*fprintf (ptrFile, "");
    fprintf (ptrFile, "");*/
    fprintf (ptrFile, "}");
    fclose (ptrFile);

    system ("dot -Tpng Dump.txt -o Dump.png");
    system ("xdot Dump.txt");

    return 0;
}

//------------------------------------------------------------------------------------------

int fPrintfElem (tree_elem_t* element, FILE* ptrFile)
{
    static int i = 0;

    if (element->left != NULL)
    {
        fPrintfElem (element->left, ptrFile);
        //printf ("I`m connecting %d\n", i);
        //fprintf (ptrFile, "elem%d:<l>->elem%d;\n", element->number, element->left->number);
    }

    i++;
    element->number = i;
    fprintf (ptrFile, "elem%d [shape=record,label=\"{ parent\\n%p | ptr %d\\n %p | data\\n %s | { <l>left\\n %p | <r> right\\n %p }}\"];\n", i, element->parent, i, element, element->data, element->left, element->right);

    if (element->right != NULL)
    {
        fPrintfElem (element->right, ptrFile);
        //printf ("I`m connecting %d\n", i);
        //fprintf (ptrFile, "elem%d:<r>->elem%d;\n", element->number, element->right->number);
    }

    return 0;
}

//--------------------------------------------------------------------------------

int fPrintfArrow (tree_elem_t* element, FILE* ptrFile)
{
    if (element->left != 0)
    {
        fprintf (ptrFile, "elem%d:<l>->elem%d[color=\"red\",label=\"NO\"];\n", element->number, element->left->number);
        fPrintfArrow (element->left, ptrFile);
    }

    if (element->right != 0)
    {
        fprintf (ptrFile, "elem%d:<r>->elem%d[color=\"green\",label=\"YES\"];\n", element->number, element->right->number);
        fPrintfArrow (element->right, ptrFile);
    }
}










