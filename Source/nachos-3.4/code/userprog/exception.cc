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
#include "synch.h"
#include <strings.h>

#define MAXBUFFER 1024

//global variable
void createFile();
void closeFile();
void openFile();
void readFile();
void writeFile();
void seek();
void exec();

void join();
void exit();
void up();
void down();
void createSemaphore();
void deleteSemaphore();
void strcmp();
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
		case SC_Create:
			createFile();
			break;
		case SC_Open:
			openFile();
			break;
		case SC_Close:
			closeFile();
			break;
		case SC_Write:
			writeFile();
			break;
		case SC_Read:
			readFile();
			break;
		case SC_Seek:
			seek();
			break;
		case SC_Exec:
			exec();
			break;
		case SC_Join:
			join();
			break;
		case SC_Exit:
			exit();
			break;
		case SC_Up:
			up();
			break;
		case SC_Down:
			down();
			break;
		case SC_CreateSemaphore:
			createSemaphore();
			break;
		case SC_DeleteSemaphore:
			deleteSemaphore();
			break;
		case SC_StrCmp:
			strcmp();
			break;

		default:
			break;
		}
		// tăng program counter
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
void openFile() {
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
	
	// khởi tạo con trỏ open file
	OpenFile* file = fileSystem->Open(fileName);

	// tìm vị trí trống
	int id = currentThread->fileManage->FindFreeSlot();
	if (id != -1) // còn vị trí trông
	{
		bool isOpen = currentThread->fileManage->Add(id, file, type);
		
		if (isOpen) // mở file thành công
		{
			machine->WriteRegister(2, id);
		}
		else
		{
			machine->WriteRegister(2, -1);
		}
	}
	else  // hết vị trí trống
	{
		machine->WriteRegister(2, -1);
	}
	delete[] fileName;
}
/////
void closeFile() {
	int id = machine->ReadRegister(4); //lay id
	bool isClose = currentThread->fileManage->CloseFile(id);

	if (isClose) 
	{
		machine->WriteRegister(2, 0);
	}
	else 
	{
		machine->WriteRegister(2, -1);
	}
}
/////
void createFile()
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
/////
void readFile()
{	
	int virtAddr, numByte, bytesRead, pos;
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
	else if (numByte < 0)
	{
		// trả về lỗi
		machine->WriteRegister(2, -1);
		return;
	}
	// id tập tin
	id = machine->ReadRegister(6);

	buffer = new char[numByte + 1];
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
		else if (bytesRead == -2) // cuối file
		{
			// trả về giá trị
			machine->WriteRegister(2, -2);
			delete[] buffer;
			return;
		}
		buffer[bytesRead] = '\0';
		bytesRead = System2User(virtAddr, bytesRead + 1, buffer);
		// trả về số byte đọc được
		machine->WriteRegister(2, bytesRead);
		delete[] buffer;
	}
	else // xử lý file
	{
		FileCustom *file = currentThread->fileManage->GetFile(id);
		// file không tồn tại hoặc đã bị đóng
		if (file == NULL)
		{
			machine->WriteRegister(2, -1);
			return;
		}
		
		if (file->pos >= file->file->Length()) // cuối file
		{
			// trả về giá trị
			machine->WriteRegister(2, -2);
			delete[] buffer;
			return;
		}

		pos = file->pos;
		bytesRead = file->file->ReadAt(buffer, numByte, pos);
		if (bytesRead == -1)
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesRead);
			delete[] buffer;
			return;
		}
		
		bytesRead = System2User(virtAddr, bytesRead, buffer);
		
		// cap nhat lai pos
		pos = pos + bytesRead;
		file->pos = pos;
		// trả về số byte đọc được
		machine->WriteRegister(2, bytesRead);
		delete[] buffer;
	}
}
/////
void writeFile()
{
	int virtAddr, numByte, bytesWrite, pos;
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
	else if (numByte < 0)
	{
		// trả về lỗi
		machine->WriteRegister(2, -1);
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
		bytesWrite = gSynchConsole->Write(buffer, numByte);
		if (bytesWrite == -1) // ghi lỗi
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesWrite);
			delete[] buffer;
			return;
		}
		
		// trả về số byte ghi được
		machine->WriteRegister(2, bytesWrite);
		delete[] buffer;
	}
	else // xử lý file
	{
		FileCustom *file = currentThread->fileManage->GetFile(id);
		// file không tồn tại hoặc đã bị đóng
		if (file == NULL)
		{
			machine->WriteRegister(2, -1);
			delete[] buffer;
			return;
		}
		else if (file->type == ReadOnly) // tập tin ko cho phép ghi
		{
			machine->WriteRegister(2, -1);
			delete[] buffer;
			return;
		}

		// ghi dữ liệu
		pos = file->pos;
		bytesWrite = file->file->WriteAt(buffer, numByte, pos);
		if (bytesWrite == -1)
		{
			// trả về giá trị
			machine->WriteRegister(2, bytesWrite);
			delete[] buffer;
			return;
		}

		pos = pos + bytesWrite;
		file->pos = pos;
		// trả về số byte ghi được
		machine->WriteRegister(2, bytesWrite);
		delete[] buffer;
	}
}
/////
void seek(){
	int pos = machine->ReadRegister(4);
	int id = machine->ReadRegister(5);

	int result = currentThread->fileManage->Seek(id, pos);

	machine->WriteRegister(2, result);
	return;
}

void exec(){
	int virtAddr;
	char* progName;


	//Lay ten file
	virtAddr = machine->ReadRegister(4);
	progName = User2System(virtAddr, MaxFileLength +1);
	if (progName == NULL)
	{
		machine->WriteRegister(2, -1);
		return;
	}

	int idProcess = pTab->ExecUpdate(progName);
	machine->WriteRegister(2, idProcess);

	delete[] progName;
}

void join(){
	int pid, ec;

	pid = machine->ReadRegister(4);
	ec = pTab->JoinUpdate(pid);

	machine->WriteRegister(2,ec);
}

void exit(){
	int exitStatus,ec ;

	exitStatus = machine->ReadRegister(4);

	ec = pTab->ExitUpdate(exitStatus);

	machine->WriteRegister(2,ec);
}

void up() {
	int virtAddr, result;
	char* semName; //name of semephore
	// lấy địa chỉ name
	virtAddr = machine->ReadRegister(4);
	semName = User2System(virtAddr, MaxFileLength + 1);
	result = semTab->Signal(semName);

	//return result
	machine->WriteRegister(2, result);
	delete[] semName;
}

void down() {
	int virtAddr, result;
	char* semName; //name of semephore
	// lấy địa chỉ name
	virtAddr = machine->ReadRegister(4);
	semName = User2System(virtAddr, MaxFileLength + 1);
	result = semTab->Wait(semName);

	//return result
	machine->WriteRegister(2, result);
	delete[] semName;
}

void createSemaphore(){
	char* name;
	int virtAddr, semval;
	int result;
	virtAddr = machine->ReadRegister(4);
	semval = machine->ReadRegister(5);
	name = User2System(virtAddr, MaxFileLength + 1);
	result = semTab->Create(name, semval);
	if(result == -1){
		printf("Already exist!\n");
	}
	else if(result == -2){
		printf("Out of bitmap!\n");
	}
	machine->WriteRegister(2,result);
	delete[] name;
}

void strcmp(){
	char* str1;
	char* str2;
	int virtAddr1, virtAddr2;
	int result;

	virtAddr1 = machine->ReadRegister(4);
	virtAddr2 = machine->ReadRegister(5);

	str1 = User2System(virtAddr1, MaxFileLength + 1);
	str2 = User2System(virtAddr2, MaxFileLength + 1);

	if(str1 == NULL || str2 == NULL){
		machine->WriteRegister(2, -1);
	}else{
		result = strcmp(str1, str2);
		machine->WriteRegister(2, result);
	}

	delete[] str1;
	delete[] str2;
}



void deleteSemaphore() {
	char* name;
	int virtAddr;
	int result;
	virtAddr = machine->ReadRegister(4);
	name = User2System(virtAddr, MaxFileLength + 1);
	result = semTab->Delete(name);
	if (result == -1) {
		printf("Semaphore not exist!\n");
	}
	else if (result == -2) {
		printf("Out of bitmap!\n");
	}
	machine->WriteRegister(2, result);
	delete[] name;

}