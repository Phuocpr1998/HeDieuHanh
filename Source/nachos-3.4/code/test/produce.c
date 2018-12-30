#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 0, max = -1, uniqueproduce = -1;
	max = CreateSemaphore("max", 3);
	uniqueproduce = CreateSemaphore("uniqueproduce", 1);
	if(max < 0 || uniqueproduce < 0)
		return -1;

	for (; i < 10; i++) {
		Down("max");
		Down("uniqueproduce");
		printf("PRODUCE: san pham trong kho la %d\n", produce());
		Up("uniqueproduce");
		Up("produce2consume");
	}
	return 0;
}