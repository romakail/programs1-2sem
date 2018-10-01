#include "List.h"
#include "math.h"
//#include "stdio.h"

#define FILENAME texGraph

struct textData_T
{
    int nChars;
    int nWords;
    char*  bufferPtr;
    char** wordsBufferPtr;
};




unsigned int calcHash1 (const char* buffer);
unsigned int calcHash2 (const char* buffer);
unsigned int calcHash3 (const char* buffer);
unsigned int calcHash4 (const char* buffer);
unsigned int calcHash5 (const char* buffer);
struct textData_T makeBuffer (FILE* ptrFile);
struct textData_T numberOfChars ();
int texDump (hashTable* Table);
int speedTest (hashTable* Table, unsigned int (*hashFunction)(const char*));


unsigned int calcHash1 (const char* buffer) // first letter
{
    assert (buffer);
    //printf ("%s  ", buffer);
    //printf ("%d\n", (int) *buffer);
    return (int) *buffer;
}

unsigned int calcHash2 (const char* buffer) // number of letters
{
    assert (buffer);
    unsigned int Hash = 0;
    while (*buffer != '\0')
    {
        //printf ("%c", *buffer);
        //printf ("\n");
        buffer++;
        Hash++;
    }
    return Hash;
}

unsigned int calcHash3 (const char* buffer) // letters sum 2000
{
    assert (buffer);
    unsigned int Hash = 0;
    while (*buffer != '\0')
    {
        Hash += *buffer;
        buffer++;
    }
    //printf ("%d\n", Hash);
    return Hash;
}

unsigned int calcHash4 (const char* buffer)       // GNU Hash
{
    assert (buffer);
    int Hash = 1234;
    while (*buffer != '\0')
    {
        Hash = Hash*33 + *buffer;
        //Hash = ((Hash << 5) + Hash) + *buffer;
        buffer++;
    }
    if (Hash < 0)
        Hash = 0 - Hash;
    Hash = Hash%10000;
    //printf ("%d\n", Hash);
    return Hash;
}

unsigned int calcHash5 (const char* buffer)       // roll & +
{
    assert (buffer);

    int Hash = 0;
    while (*buffer != '\0')
    {
        Hash = Hash + *buffer;
        Hash = Hash<<1;
        buffer++;
    }
    if (Hash < 0)
        Hash = 0 - Hash;
    Hash = Hash%10000;
    //printf ("%d\n", Hash);
    return Hash;
}

//-------------------------------------------------------------------------------------

struct textData_T creatingComfortableBuffer ()
{
    printf ("started making a buffer\n");

    FILE* ptrFile = fopen ("newveldt.txt", "r");
    assert (ptrFile);
    rewind (ptrFile);

    textData_T textData;
    textData.nChars = 0;
    textData.nWords = 0;
    textData.bufferPtr = 0;
    textData.wordsBufferPtr = 0;

    fseek (ptrFile, 0, SEEK_END);
    textData.nChars = ftell(ptrFile);
    rewind (ptrFile);

    textData.bufferPtr = (char*) calloc (textData.nChars, sizeof(char));
    assert (textData.bufferPtr);

    int nReadChars = fread  (textData.bufferPtr, sizeof(char), textData.nChars, ptrFile);
    assert (textData.nChars == nReadChars);

    for (int counter = 0; counter < textData.nChars; counter++)
    {
        if (textData.bufferPtr [counter] == ' ')
        {
            textData.bufferPtr [counter] = '\0';
            textData.nWords ++;
        }
    }

    textData.wordsBufferPtr = (char**) calloc (textData.nWords, sizeof(char*));
    assert (textData.wordsBufferPtr);

    int wordsCounter = 0;
    for (int counter = 0; counter < textData.nChars; counter++)
    {
        if (textData.bufferPtr [counter] == '\0')
        {
            textData.wordsBufferPtr [wordsCounter] = &(textData.bufferPtr [counter]) + 1;
            wordsCounter++;
        }
    }
    printf ("wordsCounter = %d, tData.nWords = %d\n", wordsCounter, textData.nWords);

    fclose (ptrFile);

    printf ("finished making a buffer\n");
    return textData;
}


struct textData_T numberOfChars ()                                 //спросить textData норм ваще ?
{
    FILE* ptrFile = fopen ("newveldt.txt", "r");
    assert (ptrFile);
    rewind (ptrFile);

    textData_T textData;
    textData.nChars = 0;
    textData.nWords = 0;
    textData.bufferPtr = 0;
    textData.wordsBufferPtr = 0;

    char letter = '\0';

    while (letter != '$')
    {
        //letter = fgets (ptrFile);
        fscanf (ptrFile, "%c", &letter);
        textData.nChars++;
        if (letter == ' ')
        {
            textData.nWords++;
        }

    }

    fclose (ptrFile);
    return textData;
}

struct textData_T makeBuffer (FILE* ptrFile)
{
    printf ("start of make buffer\n");
    textData_T textData = numberOfChars();
    printf ("nChars = %d\nnWords = %d\n", textData.nChars, textData.nWords);

    char*  bufferptr   = (char*)  calloc (textData.nChars, sizeof (char ));
    assert (bufferptr);
    char** wordsBuffer = (char**) calloc (textData.nWords, sizeof (char*));
    assert (wordsBuffer);

    textData.bufferPtr = bufferptr;
    textData.wordsBufferPtr = wordsBuffer;

    int wordsCounter = 0;

    char letter = '\0';
    for (int counter = 0; counter < textData.nChars; counter++)
    {
        fscanf (ptrFile, "%c", &letter);
        if (letter != ' ')
        {
            *bufferptr = letter;
        }
        else
        {
            *bufferptr = '\0';
            wordsBuffer[wordsCounter] = bufferptr + 1;
            wordsCounter++;
        }

        bufferptr++;
    }


    printf ("end of make buffer\n");
    return textData;
}



int fillHashTable (hashTable* Table, unsigned int (*hashFunction)(const char*))
{


    printf ("start of fillHashTable\n");
    printf ("hashFunction pointer is : %p\n", hashFunction);
    unsigned int Hash = 0;

    FILE* ptrFile = fopen ("newveldt.txt", "r");
    assert (ptrFile);
    rewind (ptrFile);

    //textData_T textData = makeBuffer (ptrFile);

    textData_T textData = creatingComfortableBuffer();
    printf ("\nnChars = %d\nnWords = %d\nbufferPtr = %p\nwordsbufferptr = %p\n\n", textData.nChars, textData.nWords, textData.bufferPtr, textData.wordsBufferPtr);

    //char*  buffer = textData.bufferPtr;
    char** words  = textData.wordsBufferPtr;
    //printf ("pointer of word`s pointers massive is: %p\n", words);

    int wordsCounter = 0;


    //printf ("   WordPointer is: %p\n", words[wordsCounter]);
    while (*words[wordsCounter] != '$')
    {

        //printf ("   WordPointer is: %p\n", words[wordsCounter]);

        //printf ("   letter is: %c\n", *words[wordsCounter]);
        Hash = (*hashFunction)(words[wordsCounter]);
        //printf ("   Hash = %d\n", Hash);


        if (Table->findSameObject(Hash, words[wordsCounter]) == 0)
        {
            //printf ("aaaaaaaaaaaaaa\n");
            Table->addElement(Hash, words[wordsCounter]);

        }
        wordsCounter++;
    }

    fclose (ptrFile);
    printf ("End of making hash table\n");
    return 0;
}

//---------------------------------------------------------------------------------------------------------

int speedTest (hashTable* Table, unsigned int (*hashFunction)(const char*))
{
    char word [6] = "aaaaa";
    for (word [0] = 'a'; word [0] <= 'z'; word [0]++)
    {
        for (word [1] = 'a'; word [1] <= 'z'; word [1]++)
        {
            for (word [2] = 'a'; word [2] <= 'z'; word [2]++)
            {
                for (word [3] = 'a'; word [3] <= 'z'; word [3]++)
                {
                    for (word [4] = 'a'; word [4] <= 'z'; word [4]++)
                    {
                        if (Table->searchElement(hashFunction, word) == 1)
                        {
                            printf ("%s\n", word);
                        }
                    }
                }
            }
        }

    }

    return 0;
}















