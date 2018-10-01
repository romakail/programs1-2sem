#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern "C" int _mystrcmp (const char*,const char*);

//extern "C" int _mystrcmp (char* arg1, char* arg2);

class hashTable;

struct list_elem_t
{
    char* data;
    list_elem_t* next;
    list_elem_t* prev;
};


class rList
{
    private:
        list_elem_t* head;
        list_elem_t* tail;
        int nElements;

    public:
        rList    ();

        int addElemAfter     (char* data, list_elem_t* prevElement);
        int addElemBefore    (char* data, list_elem_t* nextElement);
        int addToBeginning   (char* data);
        int addToEnd         (char* data);

        int changeElem       (char* data, list_elem_t* element);
        int deleteElem       (list_elem_t* deletedElement);

        int dumpList ();
        int dumpWithDot ();

        friend hashTable;
};

rList::rList ()
{
    head        = NULL;
    tail        = NULL;
    nElements   = 0;
}

//--------------------------------------------------------------------------------------------------------------------

class hashTable
{
    private:
        rList* hTable;
        unsigned int nElements;

    public:
        hashTable (unsigned int N);
        int addElement (unsigned int, char* word);
        int dumpListWithDot (int ListHash);
        int findSameObject (int Hash, char* word);
        int texDump ();
        int searchElement(unsigned int (*hashFunction)(const char*), const char* elemStr);
};

hashTable::hashTable(unsigned int N)
{
    assert (N >= 0);
    nElements = N;

    hTable = (rList*)  calloc (N, sizeof(rList));
    assert (hTable);
}

int hashTable::addElement (unsigned int Hash, char* word)
{
    hTable[Hash].addToEnd(word);

    return 0;
}

int hashTable::dumpListWithDot (int ListHash)
{
    hTable[ListHash].dumpWithDot();

    return 0;
}

int hashTable::findSameObject (int Hash, char* word)
{
    list_elem_t* elemptr = hTable[Hash].head;
    int flag = 0;

    //printf ("finding: %s\n", word);
    if (elemptr != NULL)
    {
        //printf ("hash is %d\n", Hash);
        //hTable[Hash].dumpWithDot();
        do
        {
            //printf ("first  word is '%s'\n", elemptr->data);
            //printf ("second word is '%s'\n", word);
            //printf ("my strcmp = %d\n", _mystrcmp (elemptr->data, word));
            //printf ("strcmp    = %d\n\n", strcmp (elemptr->data, word));
/*
            if (_mystrcmp (elemptr->data, word) == 0)
                flag = 1;
*/          int result = 0;
            //result = strcmp (elemptr->data, word);

        asm volatile
        (
            ".intel_syntax noprefix;"

            "xor rax, rax;"
            "cld;"
            "while:;"

            "mov ah , byte [rsi - 1];"
            "cmp ah , 0;"
            "je zeroFound;"

            "cmpsb;"
            "je notEqual;"

            "mov al, 1;"
            "jmp endOfWord;"
            "notEqual:;"

            "jmp while;"
            "zeroFound:;"
            "mov ah, byte [rdi - 1];"
            "cmp ah, 0;"
            "je endOfWord;"
            "mov al, 1;"

            "endOfWord:;"
            "xor ah, ah;"
            ".att_syntax noprefix;"

            : "=a"(result)
            : "S"(elemptr->data), "D"(word)
        );


/*
            asm volatile
            (
                ".intel_syntax noprefix;"

                "nop;"
                "nop;"
                "nop;"
                "nop;"
                "nop;"
                "nop;"
                "nop;"


                "xor rax, rax;"
                "xor r8, r8;"
                "xor r9, r9;"

                "while: ;"

                "xor rbx, rbx;"
                "mov bl, byte [rdi];"
                "mov r8, rbx;"

                "xor rbx, rbx;"
                "mov bl, byte [rsi];"
                "mov r9, rbx;"

                "cmp r8, 0;"
                "je zeroFound;"
                "cmp r9, 0;"
                "je zeroFound;"

                "cmp r8, r9;"
                "je notEqual;"

                "mov rax, 1;"
                "jmp endOfWord;"

                "notEqual: ;"

                "inc rdi;"
                "inc rsi;"
                "jmp while;"

                "zeroFound: ;"
                "cmp r8, r9;"
                "je endOfWord;"
                "mov rax, 1;"

                "endOfWord: ;"

                ".att_syntax noprefix;"
                :
                "=a"(result)
                :
                "S"(elemptr->data),
                "D"(word)
            );
*/
            //printf ("I have realised your function, result = %d\n", result);
            if (result == 0)
                flag = 1;
            //if (strcmp (elemptr->data, word) == 0)
            //   flag = 1;

            //printf("%p\n", elemptr);

            if (elemptr->next != NULL)
                elemptr = elemptr->next;
            //printf ("flag = %d\n\n", flag);
        } while (elemptr != hTable[Hash].tail);
    }


    return flag;
}

//------------------------------------------------------------------------------------------------------------------
// there is such element
// there is no such element

int hashTable::searchElement(unsigned int (*hashFunction)(const char*), const char* elemStr)
{
    int flag = 0;
    int compareResult = 0;
    int Hash = hashFunction (elemStr);
    //printf ("Hash = %d\n", Hash);

    list_elem_t* elemptr = hTable [Hash].head;

    if (elemptr != NULL)
    {
        do
        {
            //printf ("%s\n", elemptr->data);
            //printf ("%s\n", elemStr);

            compareResult = strcmp(elemptr->data, elemStr);
/*
            asm volatile
            (
                ".intel_syntax noprefix;"

                "xor rax, rax;"
                "cld;"
                "while1:;"

                "mov ah , byte [rsi - 1];"
                "cmp ah , 0;"
                "je zeroFound1;"

                "cmpsb;"
                "je notEqual1;"

                "mov al, 1;"
                "jmp endOfWord1;"
                "notEqual1:;"

                "jmp while1;"
                "zeroFound1:;"
                "mov ah, byte [rdi - 1];"
                "cmp ah, 0;"
                "je endOfWord1;"
                "mov al, 1;"

                "endOfWord1:;"
                "xor ah, ah;"
                ".att_syntax noprefix;"

                : "=a"(compareResult)
                : "S"(elemptr->data), "D"(elemStr)
            );
*/
            if ( compareResult == 0)
            {
                flag = 1;
                break;
            }
            if (elemptr->next != NULL)
                elemptr = elemptr->next;
        }while (elemptr->next != NULL);
    }
    return flag;
}

//------------------------------------------------------------------------------------------------------------------

int hashTable::texDump ()
{
    //assert (fileName);
    //assert (Table);

    FILE* ptrFile = fopen ("texDump" , "w");
    assert (ptrFile);
    rewind (ptrFile);

    fprintf (ptrFile, "\\documentclass{article}\n");
    fprintf (ptrFile, "\\usepackage{pgfplots}\n");
    fprintf (ptrFile, "\\pgfplotsset{compat=1.9}\n");

    fprintf (ptrFile, "\\begin{document}\n");
    fprintf (ptrFile, "\\begin{tikzpicture}\n");
    fprintf (ptrFile, "\\begin{axis}\n");

    //fprintf (ptrFile, "\\addplot3 table [x = b, y = a] {\n");
    //fprintf (ptrFile, "   a   b\n");

    fprintf (ptrFile, "\\addplot coordinates {\n");

    for (unsigned int i = 0; i < nElements; i++)
    {
        fprintf (ptrFile, "   (%d, %d)\n", i, hTable [i].nElements);
    }

    fprintf (ptrFile, "};\n");

    fprintf (ptrFile, "\\end{axis}\n");
    fprintf (ptrFile, "\\end{tikzpicture}\n");
    fprintf (ptrFile, "\\end{document}\n");
    //fprintf (ptrFile, "");

    fclose (ptrFile);

    system ("pdflatex texDump");
    system ("evince texDump.pdf");

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------

int rList::addElemAfter (char* data, list_elem_t* prevElement)
{
    assert (data);
    assert (prevElement);

    list_elem_t* addedElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
    assert (addedElement);

    addedElement->data = data;

    if      (prevElement->next == NULL)
    {
        prevElement ->next = addedElement;            //connection with previous element
        addedElement->prev = prevElement;
        addedElement->next = NULL;

        tail = addedElement;
    }

    else if (prevElement->next != NULL)
    {
        addedElement->next      = prevElement->next;  //connection with next element
        prevElement->next->prev = addedElement;

        addedElement->prev      = prevElement;        //connection with previous element
        prevElement ->next      = addedElement;
    }
    else assert (0);

    nElements++;
    return 0;
}

//------------------------------------------------------------------------------

int rList::addElemBefore (char* data, list_elem_t* nextElement)
{
    assert (data);
    assert (nextElement);

    list_elem_t* addedElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
    assert (addedElement);
    addedElement->data = data;

    if      (nextElement->prev == NULL)
    {
        nextElement ->prev = addedElement;            //connection with next element
        addedElement->next = nextElement;
        addedElement->prev = NULL;

        head = addedElement;
    }

    else if (nextElement->prev != NULL)
    {
        addedElement->prev      = nextElement->prev;  // connection with previous element
        nextElement->prev->next = addedElement;

        addedElement->next      = nextElement;        // connection with next element
        nextElement ->prev      = addedElement;
    }
    else assert (0);


    nElements++;
    return 0;
}

//------------------------------------------------------------------------------------

int rList::addToBeginning (char* data)
{
    if ((head == NULL) && (tail == NULL))
    {
        list_elem_t* addedElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
        assert (addedElement);
        addedElement->data = data;
        addedElement->next = NULL;
        addedElement->prev = NULL;

        head = addedElement;
        tail = addedElement;
        nElements++;
    }
    else if ((head != NULL) && (tail != NULL))
    {
        if (addElemBefore(data, head) == 0)
            return 0;
        else
            return 1;
    }
    else { return 2; }

    return 0;
}

//-------------------------------------------------------------------------------------

int rList::addToEnd (char* data)
{
    if ((head == NULL) && (tail == NULL))
    {
        list_elem_t* addedElement = (list_elem_t*) calloc (1, sizeof (list_elem_t));
        assert (addedElement);
        addedElement->data = data;
        addedElement->next = NULL;
        addedElement->prev = NULL;

        head = addedElement;
        tail = addedElement;
        nElements++;
    }
    else if ((head != NULL) && (tail != NULL))
    {
        if (addElemAfter(data, tail) == 0)
            return 0;
        else
            return 1;
    }
    else { return 2; }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------

int rList::changeElem (char* data, list_elem_t* element)
{
    assert (element);

    element->data = data;
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------

int rList::deleteElem (list_elem_t* deletedElement)
{
    assert (deletedElement);

    if     ((deletedElement->next == NULL) && (deletedElement->prev == NULL))
        return 1;
    else if (deletedElement->next == NULL)
    {
        deletedElement->prev->next = NULL;
        tail = deletedElement->prev;
    }
    else if (deletedElement->prev == NULL)
    {
        deletedElement->next->prev = NULL;
        head = deletedElement->next;
    }
    else
    {
        deletedElement->prev->next = deletedElement->next;
        deletedElement->next->prev = deletedElement->prev;
    }
    free (deletedElement);
    nElements--;

    // S1 2:54
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------

int rList::dumpList ()
{
    printf ("\nNumber of elements in list is : %d\n", nElements);
    list_elem_t* ptrElem = head;
    printf ("head pointer is %p\n", head);
    for (int counter = 0; counter < nElements; counter++)
    {
        printf ("element [%d] is \" %s \"\n"  , counter + 1, ptrElem->data);
        printf ("prev pointer is %p\n"   , ptrElem->prev);
        printf ("elem pointer is %p\n"   , ptrElem);
        printf ("next pointer is %p\n\n" , ptrElem->next);

        ptrElem = ptrElem->next;
    }
    printf ("tail pointer is %p\n", tail);

    return 0;
}

//------------------------------------------------------------------------------------

int rList::dumpWithDot ()
{
    list_elem_t* ptr = head;
    FILE* ptrFile = fopen ("Dump.txt", "w");
    assert (ptrFile);
    rewind (ptrFile);

    fprintf (ptrFile, "digraph Elements{\n");
    fprintf (ptrFile, "rankdir=HR;\n");

    //fprintf (ptrFile, "error [shape=record,label=\"error detector returned : %d\"];\n ", listOK (rList));
    fprintf (ptrFile, "head [shape=record,label=\"head\\n%p | tail\\n%p | nElement\\n%d\"];\n", head, tail, nElements);

    for (int i = 0; i < nElements; i++)
    {
        fprintf (ptrFile, "elem%d [shape=record,label=\"<pt> ptr\\n %p | data\\n %s |<n> next\\n %p |<p> prev\\n%p\" ];\n", i, ptr, ptr->data, ptr->next, ptr->prev);
        if (ptr->next != NULL)
            ptr = ptr->next;
    }
    for (int i = 0; i < nElements-1; i++)
    {
        fprintf (ptrFile, "elem%d:<n>->elem%d:<pt>;\n", i, i+1);
        if (ptr->next != NULL)
            ptr = ptr->next;
    }
    for (int i = 0; i < nElements-1; i++)
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

