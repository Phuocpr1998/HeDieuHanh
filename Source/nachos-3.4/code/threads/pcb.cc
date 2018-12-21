#include "pcb.h"
#include "system.h"

PCB::PCB()
{
	numwait = 0;
	this->filename = NULL;
	this->joinsem = new Semaphore("joinsem", 0);
	this->exitsem = new Semaphore("exitsem", 0);
	this->multex = new Semaphore("multex", 1);
	thread = NULL;
}

PCB::PCB(int id)
{
	numwait = 0;
	this->id = id;
	this->filename = NULL;

	this->joinsem = new Semaphore("joinsem", 0);
	this->exitsem = new Semaphore("exitsem", 0);
	this->multex = new Semaphore("multex", 1);
	thread = NULL;
}

PCB::~PCB()
{
	if (this->filename != NULL)
		delete[] filename;

	delete joinsem;
	delete exitsem;
	delete multex;
	/*if (thread != NULL)
		delete thread;*/
}

int PCB::Exec(char * filename, int pid)
{
	SetFileName(filename);
	this->id = pid;

	this->multex->P();
	thread = new Thread(this->filename);
	this->multex->V();

	if (thread == NULL) {
		return -1;
	}

	//int threadId = (int)execable;
	thread->setStatus(RUNNING);
	thread->Fork(StartProcess_2, pid); //threadId
	return this->id;
}	

int PCB::GetID()
{
	return this->id;
}

Thread * PCB::GetThread()
{
	return thread;
}

int PCB::GetNumWait()
{
	return this->numwait;
}

void PCB::JoinWait()
{
	joinsem->P();
}

void PCB::ExitWait()
{
	exitsem->P();
}

void PCB::JoinRelease()
{
	joinsem->V();
}

void PCB::ExitRelease()
{
	exitsem->V();
}

void PCB::IncNumWait()
{
	this->numwait++;
}

void PCB::DecNumWait()
{
	if (this->numwait > 0)
		this->numwait--;
}

void PCB::SetExitCode(int ec)
{
	this->exitcode = ec;
}

int PCB::GetExitCode()
{
	return this->exitcode;
}

void PCB::SetFileName(char * fn)
{
	if (this->filename != NULL)
	{
		delete[] this->filename;
	}

	this->filename = new char[strlen(fn)];
	strcpy(filename, fn);
}

char* PCB::GetFileName()
{
	return this->filename;
}
