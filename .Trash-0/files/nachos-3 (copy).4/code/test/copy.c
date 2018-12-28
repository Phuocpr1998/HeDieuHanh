#include "syscall.h"

#define MAXBUFFER 10
#define MAXLENGHT 32

int main()
{
	OpenFileId idSrc, idDes;
	int bytesRead = 0;
	char nameSrc[MAXLENGHT], nameDes[MAXLENGHT];
	char temp[MAXBUFFER];
	

	// lay ten file va mo file
	Write("Nhap ten file nguon: ", 21, ConsoleInput);
	if (Read(nameSrc, MAXLENGHT, ConsoleOutput) <= 0)
	{
		Write("Lay file nguon that bai\n", 25, ConsoleInput);
		return 0;
	}
	idSrc = Open(nameSrc, ReadWrite);

	Write("Nhap ten file dich: ", 20, ConsoleInput);
	if (Read(nameDes, MAXLENGHT, ConsoleOutput) <= 0)
	{
		Write("Lay file dich that bai\n", 24, ConsoleInput);
		return 0;
	}
	idDes = Open(nameDes, ReadWrite);

	// copy file
	if (idSrc > 1 && idDes > 1)
	{
		do 
		{
			bytesRead = Read(temp, MAXBUFFER, idSrc);
			if (bytesRead > 0) 
			{
				Write((char*)temp, bytesRead, idDes);
			}
		} while (bytesRead > 0);

		Write("Copy file thanh cong\n", 22, ConsoleInput);
		CloseFile(idDes);
		CloseFile(idSrc);
	}
	else
	{
		Write("Mo file that bai.\n", 17, ConsoleInput);
		if (idDes > 0)
			CloseFile(idDes);
		if (idSrc > 0)
			CloseFile(idSrc);
	}

	Write("\n", 1, ConsoleInput);

	return 0;
}