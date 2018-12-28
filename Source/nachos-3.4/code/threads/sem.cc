#include "sem.h"
Sem::Sem(char* na, int i){
	this->name = new char[strlen(na) + 1];
	strcpy(this->name, na);
	sem = new Semaphore(this->name,i);
}

Sem::~Sem(){
	delete sem;
	if (name != NULL)
		delete name;
}
void Sem::wait(){ 
	sem->P(); 
} 
void Sem::signal(){ 
	sem->V(); 
} 
char* Sem::GetName(){
	return name;
}
