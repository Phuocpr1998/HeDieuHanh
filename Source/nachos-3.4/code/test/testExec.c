#include "syscall.h"
#define MAXLEN 32

int main(){

	int pingID = 0;
	int pongID = 0;
	char a[1];
	
	pingID = Exec("./test/ping");
	//pongID = Exec("./test/pong");

	Join(pingID);
	//Join(pongID);
	//Read(a, 1, ConsoleOutput);
}
