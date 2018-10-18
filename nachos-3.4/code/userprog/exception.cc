// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//Ham copy vung data tu user space sang kernel space
//Tra ve con tro tro den vung data da dc chuyen sang kernel space

char * User2System(int virtAddr, int limit)
{
	int oneChar;
        char * kernelBuf = new char[limit + 1];
        if (kernelBuf == NULL)
                return NULL;
        memset(kernelBuf, 0, limit + 1);
        //doc vaf copy du lieu tai dia chi virtAddr sang kernelBuff
        for (int i = 0;i <limit;i++)
        {
                machine->ReadMem(virtAddr + i, 1, &oneChar);
                kernelBuf[i] = (char)oneChar;
                if (oneChar == 0)
                        break;
        }
        return kernelBuf;

}

//Ham copy data o vung kernel sang vung user
// Tra ve so byte da copy
int System2User(int virtAddr, int len, char *buffer)
{
        if (len < 0)
                return -1;
        if (len == 0)
                return 0;

        int oneChar = 0;
        int i = 0;
        do
        {
                oneChar = (int)buffer[i];
                machine->WriteMem(virtAddr + i, 1, oneChar);
                i++;
        }
        while (i <len && oneChar != 0);

        return i;
}


void Create()
{
	int virtAddr;
        char *fileName;

        DEBUG('a',"\nSC_CreateFile all...");
        DEBUG('a',"\nReading virtual address of filename");

        // lay dia chi cua filename trong thanh ghi 4
        virtAddr = machine->ReadRegister(4);

        DEBUG('a',"\nReading filename.");
        // copy vung du lieu cua file name ngoai user space vao vung kernel space
        // gia tri tra ve la dia chi cua filename trong vung kenel space
        fileName = User2System(virtAddr, MaxFileLength + 1);
        if (fileName == NULL)
        {
                printf("\nNot enough memory in system");
                DEBUG('a',"\nNot enough memory in system");
                //tra ve gia tri loi -1
                machine->WriteRegister(2,-1);
                delete[] fileName; // xoa vung nho da cap phat trong ham User2System
                return; // ket thuc ham
        }

        DEBUG('a',"\nFinish reading filename.");
        if (!fileSystem->Create(fileName,0))
        {
                printf("\nError create file '%s'", fileName);
                machine->WriteRegister(2,-1);
                delete[] fileName;
                return; //ket thuc ham
        }

        DEBUG('a',"\nFinish create file");
        machine->WriteRegister(2,0);//tra gia tri thanh cong
        delete[] fileName;

}


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
	int type = machine->ReadRegister(2);

	switch (which)
	{
	case SyscallException:
		switch (type)
		{
		case SC_Halt:
			DEBUG('a', "Shutdown, initiated by user program.\n");
			interrupt->Halt();
			break;
		case SC_CreateFile:
			Create();
			break;
		case SC_PRINTF:
		{
			int virtAddr = machine->ReadRegister(4);
			char * str = User2System(virtAddr, 256);
			SynchConsole * synchConsole;
			synchConsole->Write(str, 256);
			delete[] str;
			break;
		}
		default:
		  DEBUG('e', "Shutdown, don't have type in systemcall.\n");
			interrupt->Halt();
			break;
		}

		break;
	case PageFaultException:
		DEBUG('e', "Shutdown, Have a PageFaultException.\n");
		interrupt->Halt();
		break;
	case ReadOnlyException:
		DEBUG('e', "Shutdown, Have a ReadOnlyException.\n");
		interrupt->Halt();
		break;
	case BusErrorException:
		DEBUG('e', "Shutdown, Have a BusErrorException.\n");
		interrupt->Halt();
		break;
	case AddressErrorException:
		DEBUG('e', "Shutdown, Have a AddressErrorException.\n");
		interrupt->Halt();
		break;
	case OverflowException:
		DEBUG('e', "Shutdown, Have a OverflowException.\n");
		interrupt->Halt();
		break;
	case IllegalInstrException:
		DEBUG('e', "Shutdown, Have a IllegalInstrException.\n");
		interrupt->Halt();
		break;
	case NumExceptionTypes:
		DEBUG('e', "Shutdown, Have a NumExceptionTypes.\n");
		interrupt->Halt();
		break;
	default:
		printf("Unexpected user mode exception %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	}

}  
