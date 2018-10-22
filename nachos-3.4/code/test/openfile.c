#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main()
{

	if (openFile("text.txt", 0) != -1) {
		printf("Mo file thanh cong\n");
	}
	else {
		printf("Mo file that bai\n");
	}
	
	if (closeFile(2) != -1) {
		printf("Dong file thanh cong\n");
	}
	else {
		printf("Dong file that bai\n");
	}
	return 0;
}
