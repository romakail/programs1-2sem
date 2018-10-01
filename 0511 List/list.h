#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef double Elem_t;
struct list_elem_t
{
    Elem_t data;
    list_elem_t* next;
    list_elem_t* prev;
};

struct list_t
{
    list_elem_t* head;
    list_elem_t* tail;
    int nElements;
};


int constructList    (list_t* rList, Elem_t data);
int addElemAfter     (list_t* rList, Elem_t data, list_elem_t* prevElement);
int addElemBefore    (list_t* rList, Elem_t data, list_elem_t* nextElement);
int addToBeginning   (list_t* rList, Elem_t data);
int addToEnd         (list_t* rList, Elem_t data);
int changeElem       (list_t* rList, Elem_t data, list_elem_t* element);
int deleteElem       (list_t* rList, list_elem_t* deletedElement);
int dumpList         (list_t* rList);
int dumpWithDot      (list_t* rList);

int listOK           (list_t* rList);  //functions for verification
int checkCycle       (list_t* rList);
int nElements        (list_t* rList);
int checkConnections (list_t* rList);

enum errors
{
    CYCLE       = 1,
    NELEMENTS   = 2,
    CONNECTIONS = 3
};

#endif // LIST_H_INCLUDED

