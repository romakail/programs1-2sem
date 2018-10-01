#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>

#include "akinator.h"


int akinator ()
{
    tree_t rTree = {};
    constructTree (&rTree, "He is a person");

    constructBase (&rTree, "savedBase.txt");
    akinatorRun (&rTree);
    saveBase (&rTree);
    dumpWithDot(&rTree);
    system ("nano savedBase.txt");
    return 0;
}

//-----------------------------------------------------------------------------------------------

int akinatorRun (tree_t*  rTree)
{
    //printf ("Do you want to chose anybody ? (yes/no)\n ");
    char answer [MAX_CHARS] = {};
    //scanf ("%s", answer);

    bool out1 = 0;
    while (out1 != 1)
    {
        printf ("Do you want to choose or search anybody ? (yes/no/search)\n");
        scanf ("%s", answer);
        if      (strcmp (answer, "yes") == 0)
        {
            chooseCharacter (rTree);
        }
        else if (strcmp (answer, "no") == 0)
        {
            out1 = 1;
        }
        else if (strcmp (answer, "search") == 0)
        {
            searchingForCharactert (rTree);
        }
        else
        {
            printf ("I can`t understand you.\n");
            printf ("Try again.\n");
        }
    }
    printf ("this is the end.\n");
    return 0;
}

//----------------------------------------------------------------------------------------

int chooseCharacter (tree_t* rTree)
{
    char answer [MAX_CHARS];
    tree_elem_t* branch = rTree->root;
    bool out1 = 0;
    bool out2 = 0;
    while (out1 == 0)
    {
        if (branch->left == NULL)
        {
            out2 = 0;
            while (out2 == 0)
            {
                printf ("Is he/she/it %s ?  (Yes/No)\n", branch->data);
                scanf ("%s", answer);

                if      (strcmp (answer, "yes") == 0)
                {
                    printf ("Yeah, I am molodec!!!\n");
                    out2 = 1;
                }
                else if (strcmp (answer, "no") == 0)
                {
                    addingNewCharacter (rTree, branch);
                    out2 = 1;
                }
                else
                {
                    printf ("I`ve misunderstood you.\n");
                }
            }
            out1 = 1;
        }
        else
        {
            out2 = 0;
            while (out2 == 0)
            {
                printf ("Is he/she/it %s ? (Yes/No)\n", branch->data);
                scanf ("%s", answer);
                if      (strcmp (answer, "yes") == 0)
                {
                    branch = branch->right;
                    out2 = 1;
                }
                else if (strcmp (answer, "no") == 0)
                {
                    branch = branch->left;
                    out2 = 1;
                }
                else
                {
                    printf ("I`ve misunderstood you.\n");
                }
            }
        }
    }
    return 0;
}


//{

//}

//-------------------------------------------------------------------------------------------------

int addingNewCharacter (tree_t* rTree,tree_elem_t* branch)  //S2 2:27
{
    char answer [MAX_CHARS] = {};

    addElemLeft    (rTree, branch, branch->data);

    printf ("who is this character ?\n");

    getchar();
    scanf ("%[^\n]", answer);
    addElemRight   (rTree, branch, answer);

    printf ("what differents %s from %s\n", branch->right->data, branch->left->data);
    printf ("%s is ", branch->right->data);

    getchar();
    scanf ("%[^\n]", answer);
    changeElemData (rTree, branch, answer);

    return 0;
}

//-------------------------------------------------------------------------------------------------
/*
int scanfWithSpace (char buffer [MAX_CHARS])
{
    assert (buffer);
    int i = 0;
    scanf ("%c", buffer [i] );
    while (buffer[i] != '\n')
    {
        i++;
        scanf ("%c", buffer [i]);
    }
    buffer [i+1] = '\0';
    return 0;
}
*/
//-------------------------------------------------------------------------------------------------

int saveBase (tree_t* rTree)
{
    FILE* ptrFile = fopen ("savedBase.txt", "w");
    assert (ptrFile);
    rewind (ptrFile);

    fprintf(ptrFile, "(");
    printfElem (rTree->root, ptrFile);
    fprintf(ptrFile, ")");

    fclose(ptrFile);
    return 0;
}

//--------------------------------------------------------------------------------------------------

int printfElem (tree_elem_t* element, FILE* ptrFile)
{
    static int nTabs = 0;

    fprintfNtabs (ptrFile, nTabs);
    fprintf (ptrFile, "\"%s\"\n", element->data);

    if (element->left  != NULL)
    {
        nTabs++;
        fprintfNtabs (ptrFile, nTabs);
        fprintf (ptrFile, "(\n");

        printfElem(element->left, ptrFile);

        fprintfNtabs (ptrFile, nTabs);
        fprintf (ptrFile, ")\n");
        nTabs--;
    }

    if (element->right != NULL)
    {
        nTabs++;
        fprintfNtabs (ptrFile, nTabs);
        fprintf (ptrFile, "(\n");

        printfElem(element->right, ptrFile);

        fprintfNtabs (ptrFile, nTabs);
        fprintf (ptrFile, ")\n");
        nTabs--;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------

int fprintfNtabs (FILE* ptrFile, int nTabs)
{
    for (int i = 0; i < nTabs; i++)
        fprintf (ptrFile, "\t");
    return 0;
}

//---------------------------------------------------------------------------------------------

int constructBase (tree_t* rTree, char* savedFile)
{
    FILE* ptrFile = fopen (savedFile, "r");
    assert (ptrFile);
    rewind (ptrFile);

    createTreeElement(rTree, rTree->root, ptrFile);

    fclose (ptrFile);
    return 0;
}

//-------------------------------------------------------------------------------------------------

int createTreeElement  (tree_t* rTree, tree_elem_t* element, FILE* ptrFile)   // S2 14.11.17 00:19
{
    char data [MAX_CHARS];
    char symbol;

    symbol = skipGetChar (ptrFile);

    if (symbol == '(')
    {
        readBetweenQuots(ptrFile, data);
        changeElemData(rTree, element, data);

        symbol = skipGetChar (ptrFile);
        fseek (ptrFile, -1, SEEK_CUR);
        if (symbol == '(')
        {
            addElemLeft   (rTree, element, "0");
            createTreeElement (rTree, element->left, ptrFile);

            addElemRight  (rTree, element, "0");
            createTreeElement(rTree, element->right, ptrFile);
        }
    }
    else
    {
        printf ("\nProblems with reading \"(\"\n");
        printf ("I`ve read \"%c\"", symbol);
        assert (0);
    }

    symbol = skipGetChar(ptrFile);
    //printf ("--%c\n", symbol);
    return 0;
}
/*
int createTreeElement (tree_t* rTree, tree_elem_t* element, FILE* ptrFile)
{
    char data [MAX_CHARS];
    char symbol;

    symbol = skipGetChar (ptrFile);

    if (symbol == '(')
    {
        readBetweenQuots (ptrFile, data);
        addElemLeft (rTree, element, data);
        printf ("I have added \"%s\"\n\n", data);
        createTreeElement(rTree, element->left, ptrFile);
        symbol = skipGetChar (ptrFile);
    }
    else if (symbol == ')')
    {
        printf ("I have scanfed first closing");
        symbol = skipGetChar (ptrFile);
        printf ("--symbol is %c\n", symbol);
    }
    else
    {
        printf ("ERROR\nI haven`t found \"(\" or \")\" where I was searching");
        assert (0);
    }


    if (symbol == '(')
    {
        readBetweenQuots (ptrFile, data);
        addElemRight (rTree, element, data);
        createTreeElement(rTree, element->right, ptrFile);
        symbol = skipGetChar (ptrFile);
    }
    else if (symbol == ')')
    {
        printf ("\nI am finishing a function\n");
        return 0;
    }
    else
    {
        printf ("ERROR\nI haven`t found \"(\" or \")\" where I was searching");
        printf ("\nsymbol is %c\n", symbol);
        assert (0);
    }
    return 1;
}
//[]
*/
//------------------------------------------------------------------------------------

char skipGetChar (FILE* ptrFile)
{
    char symbol = '\0';
    fscanf (ptrFile, "%c", &symbol);

    while ((symbol == '\n') || (symbol == '\t'))
    {
        fscanf (ptrFile, "%c", &symbol);
    }

    return symbol;
}

//---------------------------------------------------------------------------------------

int readBetweenQuots (FILE* ptrFile, char* phrase)
{
    char symbol = '\0';
    symbol = skipGetChar (ptrFile);

    if (symbol == '"')
    {
        int counter = 0;

        fscanf (ptrFile, "%c", &symbol);
        while (symbol != '"')
        {
            phrase [counter] = symbol;
            counter++;
            fscanf (ptrFile, "%c", &symbol);
        }
        phrase [counter] = '\0';
        return counter;
    }
    else
    {
        assert (0);
        return -1;
    }
}

//------------------------------------------------------------------------------------------------

int searchingForCharactert (tree_t* rTree)
{
    char characterName [MAX_CHARS] = {};
    printf ("who do you want to search ?\n");
    //scanf ("%[  ]", characterName);

    getchar();
    scanf ("%[^\n]", characterName);
    printf ("\n I am going to search %s \n", characterName);

    tree_elem_t* elemPtr = getElementPtr (rTree->root, characterName);

    if (elemPtr != NULL)
    printf ("\nI have found %s\n", elemPtr->data);
    //assert(!strcmp(elemPtr->data, characterName));

    if (elemPtr == NULL)
    {
        printf ("I haven`t found this character\n");
    }
    else
    {
        printCharacteristic (elemPtr, elemPtr->data);
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------

int printCharacteristic (tree_elem_t* element, char* name)
{
    char charactersName [MAX_CHARS] = {};
    printf ("\n %s is :\n", element->data);

    tree_elem_t* pathBack    [MAX_PATH] = {};
    //tree_elem_t* pathTowards [MAX_PATH] = {};

    int counter1 = 0;
    while (element->parent != NULL)
    {
        pathBack [counter1] = element;
        element = element->parent;
        counter1++;
    }
    pathBack [counter1] = element;
    //counter1--;

    for (int counter2 = 0; counter2 < counter1; counter2++)
    {
        //pathBack [counter1 - counter2 ];
        if      (pathBack [counter1 - counter2]->left == pathBack [counter1 - counter2 - 1])
        {
            printf ("%s is not %s\n", name, pathBack [counter1 - counter2]->data);
        }
        else if (pathBack [counter1 - counter2]->right == pathBack [counter1 - counter2 - 1])
        {
            printf ("%s is %s\n"    , name, pathBack [counter1 - counter2]->data);
        }
        else
        {
            assert (0);
        }
    }
    return 0;
}




//---------------------------------------------------------------------------------------------------
tree_elem_t* getElementPtr (tree_elem_t* element, char* lostElement)
{
    if      ((element->left == NULL) && (element->left == NULL))
    {
        if (strcmp (lostElement, element->data) == 0)
        {
            return element;
        }
        else
        {
            return NULL;
        }
    }
    else if ((element->left != NULL) && (element->left != NULL))
    {
        tree_elem_t* ptrElement = getElementPtr (element->left, lostElement);
        if (ptrElement != NULL)
        {
            return ptrElement;
        }

        ptrElement = getElementPtr (element->right, lostElement);
        if (ptrElement != NULL)
        {
            return ptrElement;
        }
        else
        {
            return NULL;
        }
    }
    else assert (0);
}
//--------------------------------------------------------------------------------------------------
/*
tree_elem_t* getElementPtr (tree_elem_t* element, char* lostElement)
{
    if ((element->left == NULL) || (element->right == NULL))
    {
        if (strcmp (lostElement, element->data) == 0)
        {
            return element;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        tree_elem_t* ptrElement = getElementPtr (element->left, lostElement);
        if (ptrElement != NULL)
        {
            return ptrElement;
        }

        ptrElement = getElementPtr (element->right, lostElement);
        if (ptrElement != NULL)
        {
            return ptrElement;
        }
        else
        {
            return NULL;
        }
    }
}
*/
//---------------------------------------------------------------------------------------------------





















