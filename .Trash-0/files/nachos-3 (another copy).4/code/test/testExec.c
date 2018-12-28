#include "syscall.h"
#define MAXLEN 32

int main(){

	int pingID = 0;
	int pongID = 0;
	char a[1];
	
	pingID = Exec("./test/ping");
	pongID = Exec("./test/pong");

	if (pingID != -1 && pongID != -1)
	{
		Join(pingID);
		Join(pongID);
	}
}
