#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 0, uniqueconsume = -1;
	uniqueconsume = CreateSemaphore("uniqueconsume", 1);
	if (uniqueconsume < 0)
		return -1;

	for (; i < 10; i++) {
		Down("produce2consume");
		Down("uniqueconsume");
		printf("CONSUME: san pham con trong kho la %d\n", consume());
		Up("uniqueconsume");
		Up("max");
	}
	return 0;
}