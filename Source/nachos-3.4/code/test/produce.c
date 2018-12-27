#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	for (int i = 0; i < 10; i++) {
		Down("max");
		Down("uniqueproduce");
		printf("%s\n", (const char)"produce");
		Up("uniqueproduce");
		Up("produce2consume");
	}
	return 1;
}