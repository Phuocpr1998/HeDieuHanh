#include "syscall.h"
#define MAXLEN 32

int main() {

	int max, uniqueproduce, produce2consume, uniqueconsume;
	int produceID = 0;
	int consumeID = 0;
	max = CreateSemaphore("max", 3);
	uniqueproduce = CreateSemaphore("uniqueproduce", 1);
	uniqueconsume = CreateSemaphore("uniqueconsume", 1);
	produce2consume = CreateSemaphore("produce2consume", 0);
	if (max < 0 || uniqueproduce < 0 || uniqueconsume < 0 || produce2consume < 0) {
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
