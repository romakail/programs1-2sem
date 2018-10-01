#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>
#include <cmath>

#include "compiler.h"
#include "tree.h"

int compiler()
{

    lexem_t* lexemMassive = createLexemMassive("code.txt");
    printf ("\nreturned%p\n", lexemMassive);

    dumpLexemMassive(lexemMassive);

    tree_t rTree = {};
    constructTree (&rTree);


    buildingTree(lexemMassive, &rTree);
    dumpWithDot(&rTree);

    asmCodeFromTree(&rTree);


    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------

int dumpLexemElement (lexem_t* lexems, int number)
{
    switch (lexems[number].type)
        {
            case CONST : printf ("[%d] type CONST data %lg\n", number, lexems[number].data);
            break;
            case VAR : printf ("[%d] type VAR data %lg\n", number, lexems[number].data);
            break;
            #define DEF_OPER(name, text, command)                           \
            case name : printf ("[%d] type "#name" data %lg\n", number, lexems[number].data); \
            break;

            #include "operations.h"
            #undef  DEF_OPER

            #define DEF_FUNC(name, text, command)                                    \
            case name : printf ("[%d] type "#name" data %lg\n", number, lexems[number].data); \
            break;

            #include "functions.h"
            #undef  DEF_FUNC
            case END : printf ("[%d] type END  data %lg\n", number, lexems[number].data);
            break;
            default : assert (0);
        }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------

int dumpLexemMassive (lexem_t* lexems)
{
    int i = 0;
    do
    {
        dumpLexemElement ( lexems, i);

        //printf ("type %d  data %lg\n", lexems[i].type, lexems[i].data);
        i++;
    }while (lexems[i-1].type != END);
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------

lexem_t* createLexemMassive (const char* fileName)
{
    FILE* ptrFile = fopen (fileName, "r");
    assert (ptrFile);
    rewind (ptrFile);

    lexem_t* lexemMassive = (lexem_t*) calloc (MAX_LEXEMS, sizeof (lexem_t));
    assert (lexemMassive);
    printf ("pointer is %p\n", lexemMassive);


    varName_t varNames [MAX_VARS] = {};
    constructNamesMassive (varNames);

    funcName_t funcNames [MAX_FUNCS] = {};
    constructFuncsMassive (funcNames);

    argName_t argNames [ARGS_BLOC] = {};
    constructArgsMassive  (argNames);

    int counter = 0;
    do
    {
        lexemMassive [counter] = createLexem (ptrFile, varNames, funcNames, argNames);
        printf ("\nlexem[%d] type %d data %lg \n", counter, lexemMassive [counter].type, lexemMassive [counter].data);
        counter++;
    } while (lexemMassive[counter-1].type != END);


    fclose (ptrFile);
    return lexemMassive;
}

//------------------------------------------------------------------------------------------------------------------------

lexem_t createLexem (FILE* ptrFile, varName_t* varNames, funcName_t* funcNames, argName_t* argNames)
{
    lexem_t lexem = {};
    char lexemName [MAX_CHARS_IN_FUNC_NAME] = {};
    char temp = '\0';
    static int actualFuncNumber = 0;

    fscanf (ptrFile, " %c", &temp);
    if ((temp >= '0') && (temp <= '9'))
    {
        fseek (ptrFile, -1, SEEK_CUR);
        fscanf (ptrFile, "%lg", &lexem.data);
        printf ("--%lg--", lexem.data);
        lexem.type = CONST;
    }
    else if (temp == 'x')
    {
        fscanf (ptrFile, "%s", lexemName);
        lexem.type = VAR;
        lexem.data = nameInNumber(lexemName, varNames);
    }
    else if (temp == 'f')
    {
        fscanf (ptrFile, "%s", lexemName);
        lexem.type = FUNCTION;
        actualFuncNumber = funcNameInNumber(lexemName, funcNames);
        lexem.data = actualFuncNumber;
        assert ( argNameInNumber(lexemName, argNames , 1) == -1 );
        //lexem.data = funcNameInNumber(lexemName, funcNames);
    }
    else if (temp == 'c')
    {
        fscanf (ptrFile, "%s", lexemName);
        lexem.type = CALL;
        lexem.data = funcNameInNumber(lexemName, funcNames);
    }
    else if (temp == 'a')
    {
        fscanf (ptrFile, "%s", lexemName);
        lexem.type = VAR;
        lexem.data = FUNC_ARGS_POSITION + ARGS_BLOC * actualFuncNumber + argNameInNumber(lexemName, argNames , 0);

        //lexem.data = funcNameInNumber(lexemName, funcNames);
    }
    else //if (((temp >= 'a') && (temp <= 'z')) || ((temp >= 'A') && (temp <= 'Z')))
    {
        fseek (ptrFile, -1, SEEK_CUR);
        fscanf (ptrFile, "%s", lexemName);
        if (0);
        #define DEF_OPER(name, text, command)       \
        else if (strcmp (text, lexemName) == 0)     \
        {                                           \
            lexem.type = name;                      \
            lexem.data = POISON;                    \
        }
        #include "operations.h"
        #undef DEF_OPER

        #define DEF_FUNC(name, text, command)       \
        else if (strcmp (text, lexemName) == 0)     \
        {                                           \
            lexem.type = name;                      \
            lexem.data = POISON;                    \
        }
        #include "functions.h"
        #undef DEF_FUNC
        else if (strcmp ("end", lexemName) == 0)
        {
            lexem.type = END;
            lexem.data = POISON;
            printf ("\n I have found end\n");
        }

        else
        {
            printf ("---ERROR---\n");
            printf ("%s\n", lexemName);
            assert (0);
        }
    }
    return lexem;
}

//------------------------------------------------------------------------------------------------------------------

double argNameInNumber (char* name, argName_t* names, int reset)
{
    if      (reset == 1)
    {
        constructArgsMassive (names);
        return -1;
    }
    else if (reset == 0)
    {
        int counter = 0;
        while ((strcmp(names[counter].name, name) != 0) && (names[counter].number != -1))
            counter++;
        assert (counter < ARGS_BLOC);
        strcpy (names[counter].name, name);
        names[counter].number = counter;
        printf ("\n--%s  %lg", names[counter].name, names[counter].number);
        return names[counter].number;
    }
    else assert (0);
}

//------------------------------------------------------------------------------------------------------------------

double nameInNumber (char* name, varName_t* names)
{
    int counter = 0;
    while ((strcmp(names[counter].name, name) != 0) && (names[counter].number != -1))
        counter++;
    strcpy (names[counter].name, name);
    names[counter].number = counter;
    printf ("\n--%s  %lg", names[counter].name, names[counter].number);
    return names[counter].number;
}

//-------------------------------------------------------------------------------------------------------------------

double funcNameInNumber (char* name, funcName_t* functions)
{
    int counter = 0;
    while ((strcmp(functions[counter].name, name) != 0) && (functions[counter].number != -1))
        counter++;
    strcpy (functions[counter].name, name);
    functions[counter].number = counter;
    printf ("\n--%s  %lg", functions[counter].name, functions[counter].number);
    return functions[counter].number;
}



//-----------------------------------------------------------------------------------------------------------------------

int buildingTree (lexem_t* lexemMassive, tree_t* rTree)
{
    int position = 0;

    //tree_elem_t* firstElement = createNode(rTree);
    rTree->root = growNodeFUNC (rTree, lexemMassive, &position);

    if (lexemMassive[position].type != END)
    {
        printf ("\n returned a mistake\n");
        printf ("position is %d\n", position);
        dumpLexemElement(lexemMassive, position);
        /*switch (lexemMassive[position].type)
        {
            case CONST : printf ("type CONST data %lg\n", lexemMassive[position].data);
            break;
            #define DEF_OPER(name, text, command)                                    \
            case name : printf ("type "#name" data %lg\n", lexemMassive[position].data); \
            break;

            #include "operations.h"
            #undef  DEF_OPER

            #define DEF_FUNC(name, text)                                    \
            case name : printf ("type "#name" data %lg\n", lexemMassive[position].data); \
            break;

            #include "functions.h"
            #undef  DEF_FUNC
            case END : printf ("type END  data %lg\n", lexemMassive[position].data);
            break;
            default : assert (0);
        }*/
        assert (0);
    }
    else
        printf ("\nI have reached end");
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeFUNC (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    assert (lexemMassive[*position].type == FUNCTION);
    tree_elem_t* topElement = createNode(rTree);
    topElement->type = lexemMassive[*position].type;
    topElement->data = lexemMassive[*position].data;

    *position = *position + 1;

    topElement->right = growNodeMEOW (rTree, lexemMassive, position);

    while ((lexemMassive[*position].type == FUNCTION) && (lexemMassive[*position].type != END))
    {

        tree_elem_t* element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;

        /*tree_elem_t* meowNode = createNode(rTree);
        meowNode->type = MEOW;
        element->right = meowNode;
        meowNode->parent = element;*/

        assert ( lexemMassive[*position].type == LQUOT );
        *position = *position + 1;

        while (( lexemMassive[*position].type == VAR ) && (lexemMassive[*position].type != RQUOT))
        {
            assert ( lexemMassive[*position].type == VAR );
            *position = *position + 1;

            if (lexemMassive[*position].type == COMMA)
            *position = *position + 1;
        }

        assert ( lexemMassive[*position].type == RQUOT );
        *position = *position + 1;

        element->left = topElement;
        topElement->parent = element;

        tree_elem_t* rightElement = growNodeMEOW (rTree, lexemMassive, position);

        element->right = rightElement;
        rightElement->parent = element;

        topElement = element;
    }

    return topElement;
}

//----------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeMEOW (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    assert (lexemMassive[*position].type == LFIGURE);
    *position = *position + 1;

    tree_elem_t* topElement = growNodeIF (rTree, lexemMassive, position);

    while ((lexemMassive[*position].type == MEOW) && (lexemMassive [*position + 1].type != RFIGURE))
    {
        tree_elem_t* element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;
        tree_elem_t* rightElement = NULL;
        rightElement = growNodeIF (rTree, lexemMassive, position);

        element->left = topElement;
        topElement->parent = element;

        element->right = rightElement;
        rightElement->parent = element;

        topElement = element;
    }
    assert (lexemMassive[*position].type == MEOW);
    *position = *position + 1;
    assert (lexemMassive[*position].type == RFIGURE);
    *position = *position + 1;

    return topElement;
}

//----------------------------------------------------------------------------------------------------------------------
// between MEOW and ASSIGN

tree_elem_t* growNodeIF (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* element = NULL;
    if (lexemMassive[*position].type == IF)
    {
        element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = POISON;

        *position = *position + 1;

        element->left = growNodeEML(rTree, lexemMassive, position);
        element->left->parent = element;

        element->right = growNodeMEOW (rTree, lexemMassive, position);
        element->right->parent = element;
    }
    else if (lexemMassive[*position].type == WHILE)
    {
        element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = POISON;

        *position = *position + 1;

        element->left = growNodeEML(rTree, lexemMassive, position);
        element->left->parent = element;

        element->right = growNodeMEOW (rTree, lexemMassive, position);
        element->right->parent = element;
    }
    else if (lexemMassive[*position].type == PRINTF)
    {
        element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = POISON;

        *position = *position + 1;

        element->left = growNodeEML(rTree, lexemMassive, position);
        element->left->parent = element;
    }
    else
    {
        element = growNodeASSIGN (rTree, lexemMassive, position);
    }
    return element;
}

//----------------------------------------------------------------------------------------------------------------------
//instead of growNodeE

tree_elem_t* growNodeASSIGN (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    if (lexemMassive[*position + 1].type == ASSIGN)
    {
        tree_elem_t* topElement = createNode(rTree);
        topElement->type = ASSIGN;

        assert (lexemMassive[*position].type == VAR);
        topElement->data = lexemMassive[*position].data;
        *position = *position + 1;
        //topElement->left = growNodeVAR(rTree, lexemMassive, position);
        //topElement->left->parent = topElement;

        assert ( lexemMassive[*position].type == ASSIGN);
        *position = *position + 1;

        topElement->right = growNodeEML(rTree, lexemMassive, position);
        topElement->right->parent = topElement;
        return topElement;
    }
    else
    {
        return growNodeEML(rTree, lexemMassive, position);
    }
}

//----------------------------------------------------------------------------------------------------------------------
//between assign and E
tree_elem_t* growNodeEML (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* topElement = growNodeE (rTree, lexemMassive, position);

    if (
            (lexemMassive[*position].type == EQUAL)  ||
            (lexemMassive[*position].type == NEQUAL) ||
            (lexemMassive[*position].type == MORE)   ||
            (lexemMassive[*position].type == MOREE)  ||
            (lexemMassive[*position].type == LESS)   ||
            (lexemMassive[*position].type == LESSE)
       )
    {
        tree_elem_t* element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;
        tree_elem_t* rightElement = growNodeE (rTree, lexemMassive, position);

        element->left  = topElement;
        topElement->parent = element;

        element->right = rightElement;
        rightElement->parent = element;

        topElement = element;
    }
    return topElement;
}

//-----------------------------------------------------------------------------------------------------------------------
tree_elem_t* growNodeE (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* topElement = NULL;// = createNode(rTree);
    topElement = growNodeT (rTree, lexemMassive, position);


    while ((lexemMassive[*position].type == ADD) || (lexemMassive[*position].type == SUB))
    {
        tree_elem_t* element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;
        tree_elem_t* rightElement = NULL;// = createNode(rTree);
        rightElement = growNodeT (rTree, lexemMassive, position);

        element->left  = topElement;
        topElement->parent = element;

        element->right = rightElement;
        rightElement->parent = element;

        topElement = element;
    }
    return topElement;
}

//----------------------------------------------------------------------------------------------------

tree_elem_t* growNodeT (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* topElement = NULL;// = createNode(rTree);
    topElement = growNodeP (rTree, lexemMassive, position);


    while ((lexemMassive[*position].type == MULT) || (lexemMassive[*position].type == DIV))
    {
        tree_elem_t* element = createNode(rTree);
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;
        tree_elem_t* rightElement = NULL;// = createNode(rTree);
        rightElement = growNodeP (rTree, lexemMassive, position);

        element->left  = topElement;
        topElement->parent = element;

        element->right = rightElement;
        rightElement->parent = element;

        topElement = element;
    }
    return topElement;
}

//------------------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeP (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    switch (lexemMassive[*position].type)
    {
        case LQUOT :{printf ("I opened left quot");
                    *position = *position + 1;
                    tree_elem_t* element = NULL;// = createNode(rTree);
                    element = growNodeEML (rTree, lexemMassive, position);
                    assert (lexemMassive[*position].type == RQUOT);
                    *position = *position + 1;
                    return element;}
            break;
        case SQRT  : {return growNodeSQRT  (rTree, lexemMassive, position);}
            break;
        case CONST : {return growNodeCONST (rTree, lexemMassive, position);}
            break;
        case VAR   : {return growNodeVAR   (rTree, lexemMassive, position);}
            break;
        case CALL  : {return growNodeCALL  (rTree, lexemMassive, position);}
            break;
        default :
            printf ("\nERROR\n");
            dumpLexemElement(lexemMassive, *position);
            //printf ("type is %d", lexemMassive[*position].type);
            assert (0);
                    //return growNodeN (rTree, lexemMassive, position);
    }
}

//------------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeSQRT (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* element = createNode (rTree);
    if (lexemMassive[*position].type == SQRT)
    {
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;
    }
    else assert (0);

    assert (lexemMassive[*position].type == LQUOT);
    printf ("I opened left quot");
    *position = *position + 1;
    element->left = growNodeEML (rTree, lexemMassive, position);
    element->left->parent = element;
    assert (lexemMassive[*position].type == RQUOT);
    *position = *position + 1;

    return element;
}

//--------------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeCALL (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* element = createNode(rTree);
    printf ("\nI`m in getCALL\n");
    int blocPosition = 0;
    if (lexemMassive[*position].type == CALL)
    {
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        blocPosition = FUNC_ARGS_POSITION + (int)lexemMassive[*position].data * ARGS_BLOC;
        *position = *position + 1;
    }
    else assert (0);

    assert ( lexemMassive[*position].type == LQUOT );
    *position = *position + 1;

    tree_elem_t* topElement = element;
    int argCounter = 0;
    while ( lexemMassive[*position].type != RQUOT)
    {
        tree_elem_t* commaElement = createNode (rTree);
        topElement  ->right = commaElement;
        commaElement->parent= topElement;
        commaElement->type  = COMMA;
        commaElement->data  = POISON;

        tree_elem_t* assElement   = createNode (rTree);
        commaElement->left  = assElement;
        assElement ->parent = commaElement;
        assElement   ->type = ASSIGN;
        assElement   ->data = blocPosition + argCounter;

        assElement->right = growNodeEML (rTree, lexemMassive, position);

        topElement = commaElement;
        argCounter++;

        if      ( lexemMassive[*position].type == COMMA )
        {
            *position = *position + 1;
        }
        else if ( lexemMassive[*position].type == RQUOT );
        else assert (0);
    }

    assert ( lexemMassive[*position].type == RQUOT );
    *position = *position + 1;

    return element;
}

//--------------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeVAR (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* element = createNode(rTree);
    printf ("\nI`m in getVAR\n");
    if (lexemMassive[*position].type == VAR)
    {
        element->type = lexemMassive[*position].type;
        element->data = lexemMassive[*position].data;
        *position = *position + 1;
    }
    else assert (0);
    return element;
}

//--------------------------------------------------------------------------------------------------------------------------

tree_elem_t* growNodeCONST (tree_t* rTree, lexem_t* lexemMassive, int* position)
{
    tree_elem_t* element = createNode(rTree);
    printf ("\nI`m in getN\n");
    if (lexemMassive[*position].type == CONST)
    {
        element->type = lexemMassive[*position].type;
        //printf ("\nI`m returning type %d", lexemMassive[*position].type);
        element->data = lexemMassive[*position].data;
        //printf ("\nI`m returning data %lg\n", lexemMassive[*position].data);
        *position = *position + 1;
        //printf ("\nIn getN *position is %d", *position);
    }
    else assert (0);
    return element;
}

//------------------------------------------------------------------------------------------------------------------

int asmCodeFromTree (tree_t* rTree)
{
    FILE* ptrFile = fopen ("./../assembler/asmCode.txt", "w");
    assert (ptrFile);
    rewind (ptrFile);

    printElementCode (ptrFile, rTree->root);


    fprintf (ptrFile, "\nlabel finish");
    //fprintf (ptrFile, "\nout");
    fprintf (ptrFile, "\nEnd");
    fclose (ptrFile);
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------

int printElementCode (FILE* ptrFile, tree_elem_t* element)
{
    if (((element->type >= OPBEG) && (element->type <= OPEND)) || (element->type == CONST) || (element->type == VAR))
    {
        if (element->left != NULL)
        {
            printElementCode (ptrFile, element->left);
        }

        if (element->right != NULL)
        {
            printElementCode (ptrFile, element->right);
        }

        if (element->type == CONST)
        {
            if (element->data != POISON)
            {
                fprintf (ptrFile, "push %lg\n", element->data);
            }
            else assert (0);
        }
        else if (element->type == VAR)
        {
            if (element->data != POISON)
            {
                fprintf (ptrFile, "pushop %lg\n", element->data);
            }
            else assert (0);
        }
        else if (element->type == ASSIGN)
        {
            if (element->data != POISON)
            {
                fprintf (ptrFile, "popop %lg\n", element->data);
            }
            else assert (0);
        }
        #define DEF_OPER(name, text, command)   \
        else if (element->type == name)         \
        {                                       \
            fprintf (ptrFile, command);         \
            fprintf (ptrFile, "\n");            \
        }

        #include "operations.h"
        #undef DEF_OPER
        else
        {
            printf ("\nelement type is %d\n", element->type);
            printf ("element type is %lg\n", element->data);
            assert (0);
        }
    }
    else if ((element->type >= FUNCBEG) && (element->type <= FUNCEND))
    {
        if (element->type == IF)
        {
            char label = labelName();

            fprintf (ptrFile, "push 0\n");

            if (element->left != NULL)
            {
                printElementCode (ptrFile, element->left);
            }
            else
            {
                printf ("\n--ERROR--");
                printf ("\nIf has no condition\n");
                assert (0);
            }

            fprintf (ptrFile, "jumpe %c\n", label);

            if (element->right != NULL)
            {
                printElementCode (ptrFile, element->right);
            }
            else
            {
                printf ("\n--ERROR--");
                printf ("\nIf has no operation\n");
                assert (0);
            }

            fprintf (ptrFile, "label %c\n", label);
        }
        else if (element->type == WHILE)
        {
            char label1 = labelName();
            char label2 = labelName();

            fprintf (ptrFile, "label %c\n", label1);
            fprintf (ptrFile, "push 0\n");

            if (element->left != NULL)
            {
                printElementCode (ptrFile, element->left);
            }
            else
            {
                printf ("\n--ERROR--");
                printf ("\nWHILE has no condition\n");
                assert (0);
            }

            fprintf (ptrFile, "jumpe %c\n", label2);

            if (element->right != NULL)
            {
                printElementCode (ptrFile, element->right);
            }
            else
            {
                printf ("\n--ERROR--");
                printf ("\nWHILE has no operation\n");
                assert (0);
            }

            fprintf (ptrFile, "jump %c\n", label1);
            fprintf (ptrFile, "label %c\n", label2);
        }
        else if (element->type == FUNCTION)
        {
            if (element->left != NULL)
            {
                printElementCode (ptrFile, element->left);
            }
            fprintf (ptrFile, "label %c\n", (char)element->data + 'q');

            if (element->right != NULL)
            {
                printElementCode (ptrFile, element->right);
            }
            else
            {
                printf ("\n--ERROR--");
                printf ("\nFunction has not got a body\n");
                assert (0);
            }
            if (element->left != NULL)
            {
                fprintf (ptrFile, "ret\n\n");
            }
            else
            {
                fprintf (ptrFile, "jump finish\n\n");
            }
        }
        else if (element->type == CALL)
        {
            assert (element->left == NULL);

            if (element->right != NULL)
            {
                printElementCode (ptrFile, element->right);
            }

            fprintf (ptrFile, "call %c\n", (char)element->data + 'q');
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------

int constructNamesMassive (varName_t* varNames)
{
    for (int i = 0; i < MAX_VARS; i++)
    {
        strcpy (varNames[i].name, "\0");
        varNames[i].number = -1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------

int constructFuncsMassive (funcName_t* funcNames)
{
    for (int i = 0; i < MAX_FUNCS; i++)
    {
        strcpy (funcNames[i].name, "\0");
        funcNames[i].number = -1;
    }
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------


int constructArgsMassive (argName_t* argNames)
{
    for (int i = 0; i < ARGS_BLOC; i++)
    {
        strcpy (argNames[i].name, "\0");
        argNames[i].number = -1;
    }
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------

char labelName ()
{
    static char name = 'a' - 1;
    name++;
    return name;
}
















