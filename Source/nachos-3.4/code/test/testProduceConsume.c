#include "syscall.h"
#define MAXLEN 32

int main() {

	int uniqueproduce = -1, uniqueconsume = -1, max = -1, produceID = 0, consumeID = 0;
	max = CreateSemaphore("product_of_box", 0);
	uniqueproduce = CreateSemaphore("uniqueproduce", 1);
	uniqueconsume = CreateSemaphore("uniqueconsume", 1);
	if (uniqueproduce < 0 || uniqueconsume < 0 || max < 0) {
		return -1;
	}

	consumeID = Exec("./test/consume");
	produceID = Exec("./test/produce");
	if (consumeID != -1 && produceID != -1)
	{
		Join(consumeID);
		Join(produceID);
	}
	DeleteSemaphore("product_of_box");
	DeleteSemaphore("uniqueproduce");
	DeleteSemaphore("uniqueconsume");
	return 0;
	
}
