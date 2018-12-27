#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	for (int i = 0; i < 10; i++) {
		Down("produce2consume");
		Down("uniqueconsume");
		printf("=================%s\n", (const char)"consume");
		Up("uniqueconsume");
		Up("max");
	}
	return 1;
}