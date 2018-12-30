#include "copyright.h"
#include "syscall.h"
#define MAXLEN 32
int main()
{
	int i = 1;
	
	for (; i <= 10; i++) {
		Down("product_of_box");
		Down("product_of_box");
		Down("product_of_box");
		Down("uniqueconsume");
		Write("ENCAPSULATE: dong goi 1 thung hang\n", 36, ConsoleInput);
		Up("uniqueconsume");
	}
	return 0;
}