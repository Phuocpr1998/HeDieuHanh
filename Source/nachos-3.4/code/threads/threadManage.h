#ifndef _THREADMANAGE_H_
#define _THREADMANAGE_H_
#include "copyright.h"


#define MAXP 5

class Thread;

class ThreadManage {
private:
	Thread **arr;
	int size;
public:
	ThreadManage();
	int FindFreeSlot() ;
	bool Add(int id, Thread* newThread);
	Thread* GetThread(int id);
	bool EndThread(int id);
	~ThreadManage(){
		if(arr != NULL){
			for(int i=0; i< size; i++){
				if(arr[i] != NULL){
					delete arr[i];
				}
			}
			delete[] arr;
		}
		
	}
};

#endif