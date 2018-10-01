#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


class boolMassive
{
public:
    char* massive;
    int nElements;

    boolMassive (int N);
    bool operator[] (int i);
};

class proxy
{
public:
    bool value;
    proxy (bool i)
    {
        value = i;
    }

    proxy operator= (bool value);
};

bool operator= (proxy value)
{
    return value;
}

/*
proxy proxy::operator= (bool value);
{
    return value;
};
*/
boolMassive::boolMassive (int N)
{
    assert (N > 0);
    nElements = N;
    int nChars = (N - 1) / 8 + 1;
    massive = (char*) calloc (nChars ,sizeof(char));
}


proxy boolMassive::operator[] (int i)
{
    assert (i >= 0);
    assert (i < nElements);

    //int elementNumber = i / 8;
    //int position      = i % 8;

    char a = 1;
    for (int counter = 0; counter < i % 8; counter++)
    {
        a = a*2;
    }

    proxy x (1)
    if ((a & massive [i / 8]) == 0)
        x.value = 0;

    return x;
}



int main()
{
    boolMassive m1 (16);
    m1.massive [0] = 'a';
    m1.massive [1] = 'b';

    for (int i = 0; i < 16; i++)
    {
        printf ("i = %d, x = %d\n", i, m1[i]);
    }

    /*
    int a;
    for (int i = 0; i < 20; i++)
    {
        a = 1;
        for (int counter = 0; counter < i % 8; counter++)
        {
            a = a*2;
        }
        printf ("i = %d, a = %d\n", i, a);
    }
    */
    return 0;
}
