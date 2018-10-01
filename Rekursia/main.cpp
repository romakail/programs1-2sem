#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <assert.h>
#include <cmath>


int p = 0;
const char* s = 0;

int getG0 (const char* what);
int getN ();
int getE ();
int getT ();
int getP ();


int main ()
{
    int a = getG0 ("(50+50)/(5*(5+5))");
    printf ("%d", a);
    return 0;
}

//---------------------------------------------------------------------------------------------------------

int getG0 (const char* what)
{
    s = what;
    int val = getE();
    printf ("%d\n\n", p);
    assert (s[p] == '\0');
    return val;
}
/*
int getN ()
{
    if ((s[p] >= '0') && (s[p] <= '9'))
    {
        int val = s[p] - '0';
        p++;
        return val;
    }
    else
        return 0;
}
*/
//------------------------------------------------------------------------------------------------------------

int getN ()
{
    int val = 0;

    while ((s[p] >= '0') && (s[p] <= '9'))
    {
        val = val * 10 + s[p] - '0';
        p++;
    }
    return val;
}

//--------------------------------------------------------------------------------------------------------------

int getE ()
{
    int val = getT ();

    while ((s[p] == '+') || (s[p] == '-'))
    {
        int op = s[p];
        p++;
        int val2 = getT();
        if      (op == '+') val +=val2;
        else if (op == '-') val -=val2;
        else    assert (0);
    }
    return val;
}

//--------------------------------------------------------------------------------------------------------------

int getT ()
{
    int val = getP ();

    while ((s[p] == '*') || (s[p] == '/'))
    {
        int op = s[p];
        p++;
        int val2 = getP();
        if      (op == '*') val *=val2;
        else if (op == '/') val /=val2;
        else    assert (0);
    }
    return val;
}

//---------------------------------------------------------------------------------------------------------------

int getP ()
{
    if (s[p] == '(')
    {
        printf ("\nI`m in while now\n");
        p++;
        int val = getE ();
        assert (s[p] == ')');
        p++;
        return val;
    }
    else
        return getN ();
}

