#include "syscall.h"

int main()
{

	if (copyFile("des.txt", "src.txt") != 1)
	{
		printf("Loi\n");
	}
	else
	{
		printf("Copy thanh cong\n");
	}

	/*if (createFile("text.txt") != -1)
	{
		printf("Tao file thanh cong\n");
		///open file readwrite mode
		index = openFile("text.txt", ReadWrite);

		

		if (writeFile("Kiemra.txt", 7, index) == -1)
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
	}*/
	return 0;
}