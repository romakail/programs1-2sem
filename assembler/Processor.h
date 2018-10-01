
const int SIZEOFRSTACK  = 50;
const int MEMORY_LENGHT = 200;
const double POISON = 666.666;

int    assemble ();
int    constructCommandsMassive (int nCommands,   Elem_t** commandsMassive);
int    workWithStack            (Stack_t* rStack, Stack_t* label, Elem_t* commandsMassive);

const int MAX_FUNCTIONS = 10;

enum registers
{
    REGXA = 1,
    REGXB = 2,
    REGXC = 3,
    REGXD = 4
};

int   stackAddition    (Stack_t* rStack);
int   stackDifference  (Stack_t* rStack);
int   stackComposition (Stack_t* rStack);
int   stackDivision    (Stack_t* rStack);
int   stackSqrt        (Stack_t* rStack);

int stackEqual         (Stack_t* rStack);
int stackNotEqual      (Stack_t* rStack);
int stackMore          (Stack_t* rStack);
int stackMoreEqual     (Stack_t* rStack);
int stackLess          (Stack_t* rStack);
int stackLessEqual     (Stack_t* rStack);

