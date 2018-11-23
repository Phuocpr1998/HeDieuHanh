#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main(){

	int pingID =0 ;
	int pongID = 0;

	char name[MAXLEN];
	Write("1\n", 2, ConsoleInput);

	pingID = Exec("./test/ping");

	Write("2\n", 2, ConsoleInput);

	pongID = Exec("./test/pong");

	Write("3\n", 2, ConsoleInput);

	Read(name, MAXLEN, ConsoleOutput);

}
