#include "syscall.h"
#define MAXLEN 32

int main(){

	int pingID = 0;
	int pongID = 0;

	pingID = Exec("./test/ping");
	//pongID = Exec("./test/pong");

	Join(pingID);
	//Join(pongID);
}
