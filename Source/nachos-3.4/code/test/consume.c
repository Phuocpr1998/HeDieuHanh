#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 0;
	
	for (; i < 10; i++) {
		Down("product_of_box");
		Down("product_of_box");
		Down("product_of_box");
		Down("uniqueconsume");
		printf("ENCAPSULATE: dong goi thung hang thu %d\n", i + 1);
		Up("uniqueconsume");
	}
	return 0;
}