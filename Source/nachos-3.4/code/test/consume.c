#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int uniqueconsume;
	uniqueconsume = CreateSemaphore("uniqueconsume", 1);
	if (uniqueconsume < 0) {
		return -1;
	}
	int i = 0;
	for (; i < 10; i++) {
		Down("produce2consume");
		Down("uniqueconsume");
		//printf("=================%s\n", (const char)"consume");
		Write("=================consume\n",27, ConsoleInput);
		Up("uniqueconsume");
		Up("max");
	}
	return 1;
}