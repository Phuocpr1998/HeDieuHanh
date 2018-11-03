#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main()
{
	char name[MAXLEN];

	Write("Nhap vao ten file: ",20, ConsoleInput);
	if (Read(name, MAXLEN, ConsoleOutput) == -1)
	{
		Write("Khong lay duoc ten file\n", 25, ConsoleInput);
	}
	else
	{
		if (CreateFile(name) != -1)
		{
			Write("Tao file thanh cong\n", 21, ConsoleInput);
		}
		else
		{
			Write("Tao file that bai\n", 19, ConsoleInput);
		}
	}
	Write("\n", 1, ConsoleInput);
	return 0;
}
