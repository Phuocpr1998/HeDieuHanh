#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main()
{
	if(createFile("text.txt") != -1)
	{
		printf("Tao file thanh cong\n");	
	}
	else
	{
		printf("Tao file that bai\n");
	}
	return 0;
}
