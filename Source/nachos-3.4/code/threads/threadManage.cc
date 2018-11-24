#include "thread.h"
#include "threadManage.h"

ThreadManage::ThreadManage(){
	arr = new Thread*[MAXP];
	size = MAXP;
}

int ThreadManage::FindFreeSlot(){
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == NULL)
			return i;
	}
	return -1;
}

bool ThreadManage::Add(int id, Thread* newThread){
	if(id < 0 || id >= MAXP || arr[id] != NULL){
		return false;
	}

	if(newThread == NULL){
		return false;
	}

	arr[id] = newThread;
	return true;
}

Thread* ThreadManage::GetThread(int id){
	if(id < 0 || id >= MAXP || arr[id] == NULL){
		return NULL;
	}
	return arr[id];
}

bool ThreadManage::EndThread(int id){
	if(id < 0 || id >= MAXP || arr[id] == NULL){
		return false;
	}

	delete arr[id];
	arr[id] = NULL;
	return true;
}