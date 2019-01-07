#include "stable.h"
#include "synch.h"
#include "system.h"

STable::STable() {
	bm = new BitMap(MAX_SEMAPHORE);
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		semTab[i] = NULL;
	}
}

STable::~STable() {
	if (bm != NULL) {
		delete bm;
	}

	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (semTab[i] != NULL)
			delete semTab[i];
	}
}

int STable::Create(char* name, int init) {
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (semTab[i] != NULL && (strcmp(name, semTab[i]->GetName()) == 0)) {
			printf("semaphore already %s\n", name);
			return -1; //already exists
		}
	}
	int index = bm->Find();
	if (index < 0) {
		return -2; // out of bitmap
	}
	
	semTab[index] = new Sem(name, init);
	printf("create semaphore %s\n", name);
	bm->Mark(index);
	return index;
}

int STable::Wait(char* name) {
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (semTab[i] != NULL && (strcmp(name, semTab[i]->GetName()) == 0)) {
			semTab[i]->wait();
			return 1;
		}
	}
	return -1;
}

int STable::Delete(char *name) {
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (semTab[i] != NULL && (strcmp(name, semTab[i]->GetName()) == 0)) {
			delete semTab[i];
			bm->Clear(i);
			printf("delete semaphore %s\n", name);
			return 1;
		}
	}
	return -1;
}

int STable::Signal(char* name) {
	for (int i = 0; i < MAX_SEMAPHORE; i++) {
		if (semTab[i] != NULL && (strcmp(name, semTab[i]->GetName()) == 0)) {
			semTab[i]->signal();
			return 1;
		}
	}
	return -1;
}

int STable::FindFreeSlot(int id) {
	return bm->Find();
}