#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 0;

	for (; i < 10; i++) {
		Down("max");
		Down("uniqueproduce");
		//printf("%s\n", (const char)"produce");
		Write("produce\n",9, ConsoleInput);
		Up("uniqueproduce");
		Up("produce2consume");
	}
	return 1;
}