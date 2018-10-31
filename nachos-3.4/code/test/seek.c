#include "syscall.h"

int main()
{
	OpenFileId index;
	char data[18];

	if (createFile("textSeek.txt") != -1)
	{
		printf("Tao file thanh cong\n");
		index = openFile("textSeek.txt", ReadWrite);
		if (writeFile("make file",9 , index) == -1)
		{
			printf("Ghi file loi\n");
		}
		else
		{
			printf("Ghi file thanh cong\n");
		}
		if(Seek(5, index)!= -1){ 
			printf("seek thanh cong \n"); 
		}
		if (writeFile("life", 4, index) == -1)
		{
			printf("Ghi file loi\n");
		}
		else
		{
			printf("Ghi file thanh cong\n");
		}

		closeFile(index);
	}
	else
	{
		printf("Tao file that bai\n");
	}
	return 0;
}