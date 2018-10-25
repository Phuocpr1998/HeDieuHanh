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
#include "openfile.h"
#define MAXLENGHT 10


struct FileCustom {
	OpenFile* file;
	int type;
};

FileCustom* arrayID[10];


void Create();
void closeFile();
void open();
void readFile();
void writeFile();

//Ham copy vung data tu user space sang kernel space
//Tra ve con tro tro den vung data da dc chuyen sang kernel space
char * User2System(int virtAddr, int limit);
//Ham copy data o vung kernel sang vung user
// Tra ve so byte da copy
int System2User(int virtAddr, int len, char *buffer);


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
		case SC_OpenFile:
			open();
			break;
		case SC_CloseFile:
			closeFile();
			break;
		case SC_WriteFile:
			writeFile();
			break;
		case SC_ReadFile:
			readFile();
			break;
		case SC_Printf:
		{
			int virtAddr = machine->ReadRegister(4);
			printf("%d",virtAddr);
			char * str = User2System(virtAddr, 256);
			if (str != NULL)
			{
			  gSynchConsole->Write(str, 256);
			  delete[] str;			
			}
			break;
		}
		default:
		  DEBUG('d', "Shutdown, don't have type in systemcall.\n");
			interrupt->Halt();
			break;
		}
		machine->registers[PrevPCReg] = machine->registers[PCReg];
		machine->registers[PCReg] = machine->registers[NextPCReg];
		machine->registers[NextPCReg] += 4;
		break;
	case PageFaultException:
				
		DEBUG('d', "Shutdown, Have a PageFaultException.\n");
		interrupt->Halt();
		break;
	case ReadOnlyException:
		DEBUG('d', "Shutdown, Have a ReadOnlyException.\n");
		interrupt->Halt();
		break;
	case BusErrorException:
		DEBUG('d', "Shutdown, Have a BusErrorException.\n");
		interrupt->Halt();
		break;
	case AddressErrorException:
		DEBUG('d', "Shutdown, Have a AddressErrorException.\n");
		interrupt->Halt();
		break;
	case OverflowException:
		DEBUG('d', "Shutdown, Have a OverflowException.\n");
		interrupt->Halt();
		break;
	case IllegalInstrException:
		DEBUG('d', "Shutdown, Have a IllegalInstrException.\n");
		interrupt->Halt();
		break;
	case NumExceptionTypes:
		DEBUG('d', "Shutdown, Have a NumExceptionTypes.\n");
		interrupt->Halt();
		break;
	default:
		printf("Unexpected user mode exception %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	}

}  

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
	for (int i = 0; i < limit; i++)
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
	} while (i < len && oneChar != 0);

	return i;
}
/////
void open() {
	int virtAddr, type = 0;
	char *fileName;

	DEBUG('a', "\nSC_OpenFile...");
	DEBUG('a', "\nReading virtual address of filename");
	virtAddr = machine->ReadRegister(4);
	DEBUG('a', "\nReading filename.");
	fileName = User2System(virtAddr, MaxFileLength + 1);
	

	if (fileName == NULL) {
		printf("\nNot enough memory in system");
		DEBUG('a', "\nNot enough memory in system");
		//tra ve gia tri loi -1
		machine->WriteRegister(2, -1);
		delete[] fileName; // xoa vung nho da cap phat trong ham User2System
		return; // ket thuc ham
	}
	type = machine->ReadRegister(5);
	DEBUG('a', "\nReading type.");
	
	//
	OpenFile* file = fileSystem->Open(fileName);

	if (file != NULL) { //file != null
		int index = -1;
		// vị trí 0 và 1 là vị trí cho console input và console out
		for (int i = 2; i < MAXLENGHT; i++) { //tim vi tri rong trong mang neu het vi tri tra ve loi
			if (arrayID[i] == NULL) {
				index = i;
				break;
			}
		}
		if (index != -1) { //neu co vi tri tra ve fileid = index
			FileCustom* fileCustom = new FileCustom;
			fileCustom->file = file;
			fileCustom->type = type;
			arrayID[index] = fileCustom;
		}
		machine->WriteRegister(2, index);
	}
	else {
		machine->WriteRegister(2, -1);
	}
	delete[] fileName;
}
//////
void closeFile() {
	int id = machine->ReadRegister(4); //lay id
	if (arrayID[id] == NULL) { //neu file da duoc dong hoac chua mo
		machine->WriteRegister(2, -1);
	}
	else {
		FileCustom* temp = arrayID[id];
		if (id > 2) {
			delete temp->file;
		}
		delete temp;
		arrayID[id] = NULL;
		machine->WriteRegister(2, 1);
	}
}
/////
void Create()
{
	int virtAddr;
	char *fileName;

	DEBUG('a', "\nSC_CreateFile all...");
	DEBUG('a', "\nReading virtual address of filename");

	// lay dia chi cua filename trong thanh ghi 4
	virtAddr = machine->ReadRegister(4);

	DEBUG('a', "\nReading filename.");
	// copy vung du lieu cua file name ngoai user space vao vung kernel space
	// gia tri tra ve la dia chi cua filename trong vung kenel space
	fileName = User2System(virtAddr, MaxFileLength + 1);
	if (fileName == NULL)
	{
		printf("\nNot enough memory in system");
		DEBUG('a', "\nNot enough memory in system");
		//tra ve gia tri loi -1
		machine->WriteRegister(2, -1);
		delete[] fileName; // xoa vung nho da cap phat trong ham User2System
		return; // ket thuc ham
	}

	DEBUG('a', "\nFinish reading filename.");
	if (!fileSystem->Create(fileName, 0))
	{
		printf("\nError create file '%s'", fileName);
		machine->WriteRegister(2, -1);
		delete[] fileName;
		return; //ket thuc ham
	}

	DEBUG('a', "\nFinish create file");
	machine->WriteRegister(2, 0);//tra gia tri thanh cong
	delete[] fileName;

}
////
void readFile()
{	
	int virtAddr, numByte, bytesRead;
	char * buffer;
	OpenFileId id;

	// lấy địa chỉ data
	virtAddr = machine->ReadRegister(4);
	// số byte cần đọc
	numByte = machine->ReadRegister(5);
	if (numByte == 0)
	{
		// trả về số byte đọc được
		machine->WriteRegister(2, 0);
		return;
	}
	// id tập tin
	id = machine->ReadRegister(6);
	buffer = new char[numByte];
	if (id == ConsoleOutput || id == ConsoleInput) // xử lý console
	{
		if (id == ConsoleInput) // không hợp lệ
		{
			// trả về lỗi
			machine->WriteRegister(2, -1);
			return;
		}
		
		bytesRead = gSynchConsole->Read(buffer, numByte);
		if (bytesRead == -1)
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesRead);
			delete[] buffer;
			return;
		}
		else if (bytesRead == 0) // cuối file
		{
			// trả về giá trị
			machine->WriteRegister(2, -2);
			delete[] buffer;
			return;
		}
		bytesRead = System2User(virtAddr, bytesRead, buffer);
		// trả về số byte đọc được
		machine->WriteRegister(2, bytesRead);
		delete[] buffer;
	}
	else // xử lý file
	{
		// file không tồn tại hoặc đã bị đóng
		if (id >= 10 || arrayID[id] == NULL)
		{
			machine->WriteRegister(2, -1);
			return;
		}

		bytesRead = arrayID[id]->file->Read(buffer, numByte);
		if (bytesRead == -1)
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesRead);
			delete[] buffer;
			return;
		}
		else if (bytesRead == 0) // cuối file
		{
			// trả về giá trị
			machine->WriteRegister(2, -2);
			delete[] buffer;
			return;
		}
		bytesRead = System2User(virtAddr, bytesRead, buffer);
		// trả về số byte đọc được
		machine->WriteRegister(2, bytesRead);
		delete[] buffer;
	}
}
////
void writeFile()
{
	int virtAddr, numByte, bytesRead;
	OpenFileId id;
	char * buffer;

	// lấy địa chỉ chuỗi data
	virtAddr = machine->ReadRegister(4);
	// lấy số byte cần ghi
	numByte = machine->ReadRegister(5);

	if (numByte == 0)
	{
		// trả về số byte đọc được
		machine->WriteRegister(2, 0);
		return;
	}
	// id tập tin
	id = machine->ReadRegister(6);
	buffer = User2System(virtAddr, numByte);

	if (buffer == NULL)
	{
		machine->WriteRegister(2, -1);
		return;
	}

	if (id == ConsoleOutput || id == ConsoleInput) // xử lý console
	{
		if (id == ConsoleOutput) // không hợp lệ
		{
			// trả về lỗi
			machine->WriteRegister(2, -1);
			delete[] buffer;
			return;
		}
		// ghi
		bytesRead = gSynchConsole->Write(buffer, numByte);
		if (bytesRead == -1) // ghi lỗi
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesRead);
			delete[] buffer;
			return;
		}
		else if (bytesRead == 0) // cuối file
		{
			// trả về giá trị
			machine->WriteRegister(2, -2);
			delete[] buffer;
			return;
		}
		
		// trả về số byte ghi được
		machine->WriteRegister(2, bytesRead);
		delete[] buffer;
	}
	else // xử lý file
	{
		// file không tồn tại hoặc đã bị đóng
		if (id >= 10 || arrayID[id] == NULL)
		{
			machine->WriteRegister(2, -1);
			delete[] buffer;
			return;
		}
		else if (arrayID[id]->type == ReadOnly) // tập tin ko cho phép ghi
		{
			machine->WriteRegister(2, -1);
			delete[] buffer;
			return;
		}
		// ghi dữ liệu
		bytesRead = arrayID[id]->file->Write(buffer, numByte);
		if (bytesRead == -1)
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesRead);
			delete[] buffer;
			return;
		}
		else if (bytesRead == 0) // cuối file
		{
			// trả về giá trị
			machine->WriteRegister(2, -2);
			delete[] buffer;
			return;
		}
		
		// trả về số byte đọc được
		machine->WriteRegister(2, bytesRead);
		delete[] buffer;
	}
}
