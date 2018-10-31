#include "syscall.h"
#include "copyright.h"
#define MAXLEN 40

int main(){
	int index, fnl, read_len;
	char data[MAXLEN + 1];
	writeFile("Nhap ten file:",15,ConsoleInput);
	fnl = readFile(data, MAXLEN,ConsoleOutput );	
	if(fnl == -1)
	{
		printf("Loi\n");
	}
	else{
		index = openFile(data, ReadOnly);
		printf("Noi dung file:\n");
		do{
			read_len = readFile(data, MAXLEN, index);
			if(read_len != -1 && read_len != -2){
				writeFile(data, read_len, ConsoleInput);
			}
		}while(read_len != -2);
		printf("\n");
	}
	return 0;
}