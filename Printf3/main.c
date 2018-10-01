#include <stdio.h>

extern "C" void _myPrintf (const char* text, ...);

int main()
{
	_myPrintf ("Privet\n");

    	_myPrintf ("He %b %%%oworld!! And %c %s %h %d %% %d %s \n", 15505, 15566, 'I', "LOVE", 3802, 100, 200, "heeeeeeeeeeeeeeeeeeeu");
	
	_myPrintf ("%c %s %h %d %%", 'I', "LOVE", 3802, 100);

	

	printf ("\n Hello world once more\n");
    return 0;
}
