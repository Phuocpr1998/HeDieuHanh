#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 0;
	for (; i < 10; i++) {
		Down("produce2consume");
		Down("uniqueconsume");
		printf("=================%s\n", (const char)"consume");
		Up("uniqueconsume");
		Up("max");
	}
	return 1;
}