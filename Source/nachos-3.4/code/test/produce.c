#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 0;
	
	for (; i < 30; i++) {
		Down("uniqueproduce");
		printf("PRODUCE: san pham thu %d\n", i + 1);
		Up("uniqueproduce");
		Up("product_of_box");
	}
	return 0;
}