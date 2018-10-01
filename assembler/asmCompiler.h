//#include <windows.h>
#ifndef asmCompiler_H_INCLUDED
#define asmCompiler_H_INCLUDED

const int MAXLABELS = 20;
const int AMINUS1   = 96;
const int MAXCHARS  = 10;

struct labelNames_t
{
    char      labelName [10];
    double    commandNumber;
};

enum Commands
{
    PUSH = 1,
    POP,
    OUTT,
    SCAN,
    ADD,
    DIFF,
    MULT,
    DIV,
    SQRT,
    PUSHREG,
    POPREG,
    PUSHOP,
    POPOP,
    JUMP,
    JUMPE,
    JUMPNE,
    JUMPM,
    JUMPME,
    JUMPL,
    JUMPLE,
    LABEL,
    END,
    MEOW,
    CALL,
    RET,
    E,
    NE,
    M,
    ME,
    L,
    LE,
};


int Compile ();
void fillLabelNames (labelNames_t* names);
double nameInNumber (char* name, labelNames_t* names);

#endif
