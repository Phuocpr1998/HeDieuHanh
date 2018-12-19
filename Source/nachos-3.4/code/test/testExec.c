#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main(){

	int pingID = 0;
	int pongID = 0;
	char a[] = "./test/ping";
	char b[] = "./test/pong";

	char name[1];

	pingID = Exec(a);
	pongID = Exec(b);

	// wait
	Read(name, 1, ConsoleOutput);
}
