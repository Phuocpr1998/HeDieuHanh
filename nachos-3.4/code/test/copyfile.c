#include "syscall.h"

#define MAXBUFFER 10
#define MAXLENGHT 32

int main()
{
	OpenFileId idSrc, idDes;
	int src, des, bytesRead = 0;
	char *fileNameDes, *fileNameSrc;
	char *temp;
	writeFile("Nhap ten file nguon: ", 21, ConsoleInput);
	src = readFile(fileNameSrc, MAXLENGHT, ConsoleOutput);
	writeFile("Nhap ten file dich: ", 20, ConsoleInput);
	des = readFile(fileNameDes, MAXLENGHT, ConsoleOutput);

	writeFile(fileNameSrc, MAXLENGHT, ConsoleInput);
	writeFile(fileNameDes, MAXLENGHT, ConsoleInput);

	if ((src != -1) && (des != -1))
	{//sao no y chang z
		idSrc = openFile(fileNameSrc, ReadWrite);
		idDes = openFile(fileNameDes, ReadWrite);
		if (idSrc > 1 && idDes > 1) {
			do {
				bytesRead = readFile(temp, MAXBUFFER, idSrc);
				printf((char*)bytesRead);
				if (bytesRead > 0) {
					writeFile((char*)temp, bytesRead, idDes);
				}
			} while (bytesRead > 0);
			
			//writeFile("Copy file thanh cong.", 21, ConsoleInput);
			closeFile(idDes);
			closeFile(idSrc);
		}
		else {
			writeFile("Mo file that bai.", 17, ConsoleInput);
			if (idDes > 0)
				closeFile(idDes);
			if (idSrc > 0)
				closeFile(idSrc);
		}
	}
	else
	{
		writeFile("Lay ten file that bai.", 22, ConsoleInput);
	}

	/*if (fileNameDes) {
		delete[] fileNameDes;
	}
	if (fileNameSrc) {
		delete[] fileNameSrc;
	}*/

	return 0;
}