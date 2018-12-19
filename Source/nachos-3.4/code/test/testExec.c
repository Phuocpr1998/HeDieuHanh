#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main(){

	int pingID =0 ;
	int pongID = 0;

	char name[MAXLEN];

	pingID = Exec("./test/ping");

	pongID = Exec("./test/pong");

	// wait
	//Read(name, 1, ConsoleOutput);

	Join(pingID);
	Join(pongID);
}
