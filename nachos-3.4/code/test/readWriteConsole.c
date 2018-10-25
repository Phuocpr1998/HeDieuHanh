#include "syscall.h"

#define MAXLENGHT 100

int main()
{
	char * data;
	writeFile("Nhap noi dung:\n", 16, ConsoleInput);
	if (readFile(data, MAXLENGHT, ConsoleOutput) == -1)
	{
		writeFile("Test that bai", 14, ConsoleInput);
	}
	else
	{
		writeFile("Noi dung:\n", 11, ConsoleInput);
		writeFile(data, MAXLENGHT, ConsoleInput);
		writeFile("\n", 1, ConsoleInput);
	}
	return 0;
}