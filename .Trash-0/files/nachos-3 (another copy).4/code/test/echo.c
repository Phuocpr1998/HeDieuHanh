#include "syscall.h"
#include "copyright.h"
#define MAXLEN 100

int main()
{	
	char data[MAXLEN];
	Write("Echo is on.\n", 13, ConsoleInput);
	if (Read(data, MAXLEN, ConsoleOutput) == -1)
	{
		Write("Error!\n", 8, ConsoleInput);
	}
	else
	{
		Write("Dong vua nhap:\n", 15, ConsoleInput);
		Write(data, MAXLEN, ConsoleInput);
		Write("\n\n", 2, ConsoleInput);
	}
	return 0;
}