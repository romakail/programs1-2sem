const double EPSILON = 1e-6;

typedef double Elem_t;
struct Stack_t
{
    double canary1;
    Elem_t* data;
    double canary2;
    int counter;
    double canary3;
    int sizeOfStack;
    Elem_t hesh;
    double canary4;
};

enum errorTypes
{
    POINTERNULL   = 1,
    COUNTERLESS0  = 2,
    DATAPOINTER0  = 3,
    TOOBIGCOUNTER = 4,
    HASHPROBLEM   = 5,
    CANARYPROBLEM = 6
};

#define CARSKYASSERT_OK                                      \
if (stackOK (rStack) != 0)                                   \
{                                                            \
    printf ("\n------------ERROR-----------------\n\n");     \
    printf ("errorNumber : %d\n", stackOK (rStack));         \
    dumpStack (rStack);                                      \
    assert (!"CARSKYASSERT");                                \
};


int    constructStack   (Stack_t* rStack, int sizeOfStack);
int    stackPush        (Stack_t* rStack, Elem_t value);
Elem_t stackPop         (Stack_t* rStack);
int    stackOK          (Stack_t* rStack);
int    dumpStack        (Stack_t* rStack);
int    calculateHash    (Stack_t* rStack);
int    mathHash         (Stack_t* rStack);
bool   isNull           (double number);
double canary           (int number);
