#include <stdio.h>

extern "C" int _myStrcmp (const char* str1, const char* str2);

int main()
{
	int a = 2;
	a = _myStrcmp ("privet", "privet");
	

	printf ("%d", a);
    return 0;
}
