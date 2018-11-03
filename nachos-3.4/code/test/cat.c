#include "syscall.h"
#include "copyright.h"
#define MAXLEN 40

int main(){
	int index, fnl, read_len;
	char data[MAXLEN + 1];
	
	Write("Nhap ten file:", 15, ConsoleInput);
	fnl = Read(data, MAXLEN, ConsoleOutput );

	if(fnl == -1)
	{
		Write("Loi\n", 5, ConsoleInput);
	}
	else{
		index = Open(data, ReadOnly);
		Write("Noi dung file:\n",16, ConsoleInput);

		do{
			read_len = Read(data, MAXLEN, index);
			if(read_len != -1 && read_len != -2){
				Write(data, read_len, ConsoleInput);
			}
		}while(read_len != -2);
		
		Write("\n", 1, ConsoleInput);
	}
	Write("\n", 1, ConsoleInput);

	return 0;
}