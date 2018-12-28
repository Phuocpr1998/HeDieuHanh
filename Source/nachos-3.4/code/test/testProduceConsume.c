#include "syscall.h"
#define MAXLEN 32

int main() {

	int produce2consume = -1, produceID = 0, consumeID = 0;
	produce2consume = CreateSemaphore("produce2consume", 0);
	
	if (produce2consume < 0) {
		return -1;
	}

	consumeID = Exec("./test/consume");
	produceID = Exec("./test/produce");
	if (consumeID != -1 && produceID != -1)
	{
		Join(consumeID);
		Join(produceID);
	}
	return 0;
	
}
