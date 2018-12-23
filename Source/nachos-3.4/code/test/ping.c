#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	char name[MAXLEN];
	int i=0;
	for(i; i< 1000; i++)
	{
		Write("A", 1, ConsoleInput);
	}

	ExitThread(0);
	return 1;
}