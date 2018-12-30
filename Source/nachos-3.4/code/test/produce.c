#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 1;
	
	for (; i <= 30; i++) {
		Down("uniqueproduce");
		Write("PRODUCE: Tao 1 san pham\n", 25, ConsoleInput);
		Up("uniqueproduce");
		Up("product_of_box");
	}
	return 0;
}