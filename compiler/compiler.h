#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#include "tree.h"

const int MAX_LEXEMS = 500;
const int MAX_VARS   = 15;
const int MAX_FUNCS  = 15;
const int MAX_CHARS_IN_FUNC_NAME = 15;
const int MAX_CHARS_IN_VAR_NAME  = 20;
const int FUNC_ARGS_POSITION = 100;
const int ARGS_BLOC = 5;

//[MAX_CHARS_IN_VAR_NAME]
struct varName_t
{
    char name [MAX_CHARS_IN_VAR_NAME];
    double number;
};

struct funcName_t
{
    char name [MAX_CHARS_IN_VAR_NAME];
    double number;
};

struct argName_t
{
    char name [MAX_CHARS_IN_VAR_NAME];
    double number;
};

struct lexem_t
{
    int    type;
    double data;
};

enum types
{
    NOTH = 0,
    CONST,
    VAR,
    OPBEG,

        #define DEF_OPER(name, text, command)                \
        name,
        #include "operations.h"
        #undef DEF_OPER

    OPEND,
    FUNCBEG,

        #define DEF_FUNC(name, text, command)                \
        name,
        #include "functions.h"
        #undef DEF_FUNC

    FUNCEND,
    END,
};

int      compiler ();

int constructNamesMassive    (varName_t*  varNames);
int constructFuncsMassive    (funcName_t* funcNames);
int constructArgsMassive     (argName_t*  argNames);
double nameInNumber          (char* name, varName_t* names);
double funcNameInNumber      (char* name, funcName_t* functions);
double argNameInNumber       (char* name, argName_t* names, int reset);
int dumpLexemMassive         (lexem_t* lexems);
lexem_t* createLexemMassive  (const char* fileName/*, varName_t* varNames*/);
lexem_t createLexem          (FILE* ptrFile, varName_t* varNames, funcName_t* funcNames, argName_t* argNames);

int buildingTree             (lexem_t* lexemMassive, tree_t* rTree);
tree_elem_t* growNodeFUNC    (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeMEOW    (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeIF      (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeASSIGN  (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeEML     (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeE       (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeT       (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeP       (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeSQRT    (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeCALL    (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeCONST   (tree_t* rTree, lexem_t* lexemMassive, int* position);
tree_elem_t* growNodeVAR     (tree_t* rTree, lexem_t* lexemMassive, int* position);

int asmCodeFromTree          (tree_t* rTree);
int printElementCode         (FILE* ptrFile, tree_elem_t* element);
char labelName ();

#endif
