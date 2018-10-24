#include "syscall.h"

int main()
{
	OpenFileId index;
	char data[18];

	//if (createFile("text.txt") != -1)
	{
		//printf("Tao file thanh cong\n");
		///open file readwrite mode
		index = openFile("text.txt", ReadWrite);

		if (writeFile("Kiemra.txt", 7, index) == -1)
		{
			printf("Ghi file loi\n");
		}
		else
		{
			printf("Ghi file thanh cong\n");
			if (readFile(data, 7, index) == -1)
			{
				printf("Doc file loi\n");
			}
			else
			{
				printf("Noi dung file:\n");
				printf(data);
			}
		}

		closeFile(index);
	}
	//else
	//{
	//	printf("Tao file that bai\n");
	//}
	return 0;
}