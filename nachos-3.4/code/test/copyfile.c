#include "syscall.h"

#define MAXBUFFER 10
#define MAXLENGHT 32

int main()
{
	OpenFileId idSrc, idDes;
	int bytesRead = 0;
	char *buffer;
	char *temp;
	

	// lay ten file va mo file
	writeFile("Nhap ten file nguon: ", 21, ConsoleInput);
	if (readFile(buffer, MAXLENGHT, ConsoleOutput) <= 0)
	{
		writeFile("Lay file nguon that bai\n", 25, ConsoleInput);
		return 0;
	}
	idSrc = openFile(buffer, ReadWrite);

	writeFile("Nhap ten file dich: ", 20, ConsoleInput);
	if (readFile(buffer, MAXLENGHT, ConsoleOutput) <= 0)
	{
		writeFile("Lay file dich that bai\n", 24, ConsoleInput);
		return 0;
	}
	idDes = openFile(buffer, ReadWrite);

	// copy file
	if (idSrc > 1 && idDes > 1)
	{
		do 
		{
			bytesRead = readFile(temp, MAXBUFFER, idSrc);
			if (bytesRead > 0) 
			{
				writeFile((char*)temp, bytesRead, idDes);
			}
		} while (bytesRead > 0);

		writeFile("Copy file thanh cong\n", 22, ConsoleInput);
		closeFile(idDes);
		closeFile(idSrc);
	}
	else
	{
		writeFile("Mo file that bai.\n", 17, ConsoleInput);
		if (idDes > 0)
			closeFile(idDes);
		if (idSrc > 0)
			closeFile(idSrc);
	}

	return 0;
}