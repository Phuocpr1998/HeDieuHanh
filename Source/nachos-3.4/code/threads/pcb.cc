#include "pcb.h"

PCB::PCB()
{
	numwait = 0;
	this->filename = NULL;
}

PCB::PCB(int id)
{
	numwait = 0;
	this->id = id;
	this->filename = NULL;
}

PCB::~PCB()
{
	if (this->filename != NULL)
		delete[] filename;
}

int PCB::Exec(char * filename, int pid)
{
	this->id = pid;

	this->multex->P();
	Thread* execable = new Thread(filename);
	this->multex->V();

	if (execable == NULL) {
		return -1;
	}

	int threadId = (int)execable;
	execable->setStatus(RUNNING);
	execable->Fork(StartProcess_2, threadId);

	return this->id;
}	

int PCB::GetID()
{
	return this->id;
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

char * PCB::GetFileName()
{
	return this->filename;
}
