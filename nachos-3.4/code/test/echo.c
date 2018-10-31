#include "syscall.h"
#include "copyright.h"
#define MAXLEN 100

int main()
{	
	char * data;
	writeFile("Echo is on.\n", 13, ConsoleInput);
	if (readFile(data, MAXLEN, ConsoleOutput) == -1)
	{
		writeFile("Error!\n", 8, ConsoleInput);
	}
	else
	{
		writeFile(data, MAXLEN, ConsoleInput);
	}
	return 0;
}