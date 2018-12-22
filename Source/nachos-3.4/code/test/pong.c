#include "copyright.h"
#include "syscall.h"
int main()
{
	int i = 0;

	for(i; i < 1000; i++)
	{
		Write("B", 1, ConsoleInput);
	}

	//Exit(0);
}