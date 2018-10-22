#include "syscall.h"
#include "copyright.h"
#define MAXLEN 32

int main()
{
	if (openFile("console", 0) != -1) {
		printf("Mo file thanh cong");
	}
	else {
		printf("Mo file that bai");
	}
	return 0;
}
