#include <iostream>
#include <stdio.h>

class fakeInt
{
    public:

        int useNum;
        int value ;

        fakeInt (int i)
        {
            value = i;
            useNum = 0;
        }

        fakeInt operator+(int addedInt);
        fakeInt operator+(const fakeInt& addedInt);

        fakeInt operator=(int equalInt);
        fakeInt operator=(const fakeInt& equalInt);

        //friend: fakeInt operator+(int leftData, fakeInt leftData);
};

//fakeInt operator+(int leftData, fakeInt leftData);

fakeInt fakeInt::operator+(int addedInt)
{
    useNum++;
    if ( useNum < 5)
    {
        value = value + addedInt;
        return *this;
    }
    else
    {
        printf (" int will not work untill you pay 20$");
        return *this;
    }
}


fakeInt fakeInt::operator+(const fakeInt& addedInt)
{
    useNum++;
    if (useNum < 5)
    {
        value = value + addedInt.value;
        return *this;
    }
    else
    {
        printf (" int will not work untill you pay 20$\n");
        return *this;
    }
}

fakeInt fakeInt::operator=(int equalInt)
{
    useNum++;
    if ( useNum < 5)
    {
        value = equalInt;
        return *this;
    }
    else
    {
        printf (" int will not work untill you pay 20$");
        return *this;
    }
}

fakeInt fakeInt::operator=(const fakeInt& equalInt)
{
    useNum++;
    if (useNum < 5)
    {
        value = equalInt.value;
        return *this;
    }
    else
    {
        printf (" int will not work untill you pay 20$\n");
        return *this;
    }
}




int main()
{
    int smth = 5;
    fakeInt var1 (1);
    fakeInt var2 (2);

    for (int counter = 0; counter < 8; counter++)
    {
        var1 = smth;
        smth++;
        printf ("value is %d   UseNum is : %d\n", var1.value, var1.useNum );
    }
    return 0;
}





