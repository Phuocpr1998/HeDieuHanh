#include "ptable.h"
#include "system.h"
#include "synch.h"

PTable::PTable()
{
	psize = 0;
	for (int i = 0; i < MAX_PROCESS; i++) {
		pcb[i] = NULL;
	}
	bmsem = NULL;
	bm = NULL;
}

PTable::PTable(int size){
	if (size > MAX_PROCESS)
		size = MAX_PROCESS;

	psize = size;
	bm = new BitMap(size);
	bmsem = new Semaphore("bmsem", 1);

	for (int i = 0; i < size; i++) {
		pcb[i] = NULL;
	}

	bm->Mark(0);

	//Khoi tao PCB
	pcb[0] = new PCB(0);//tien trinh co id = 0
	pcb[0]->parentID = -1; // khong co tien trinh cha
	pcb[0]->SetFileName("main");
}

PTable::~PTable(){
	if(bm != 0){
		delete bm;
	}

	if(bmsem != 0){
		delete bmsem;
	}

	for (int i = 0; i < this->psize; i++) {
		if(pcb[i] != 0){
			delete pcb[i];
		}
	}
}

int PTable::ExecUpdate(char* name){
	//Gọi mutex->P(); để giúp tránh tình trạng nạp 2 tiến trình cùng 1 lúc.
	bmsem->P();

	//Kiểm tra tính hợp lệ của chương trình “name”.
	if(name == NULL){
		// loi

		bmsem->V();
		return -1;
	}

	//Kiểm tra sự tồn tại của chương trình “name” bằng cách gọi phương thức Open của lớp fileSystem
	OpenFile *exec = fileSystem->Open(name);

	if(exec == NULL){
		printf("Unable to open file %s\n", name);
		bmsem->V();
		return -1;
	}
	//So sánh tên chương trình và tên của currentThread để chắc chắn rằng chương trình này không gọi
    //thực thi chính nó.
	char * nameParentThread = currentThread->getName();
	if (strcmp(name, nameParentThread) == 0) {
    	printf("Unable to execute it self!!!");
    	bmsem->V();
    	return -1;
    }

    //Tìm slot trống trong bảng Ptable.
    int freeSlot = this->GetFreeSlot();

    if(freeSlot < 0 ){
    	printf("No free slot ");
    	bmsem->V();
    	return -1;
    }

    //Nếu có slot trống thì khởi tạo một PCB mới với processID chính là index của slot này, parrentID là
    //processID của currentThread.
    pcb[freeSlot] = new PCB(freeSlot);
	int parentID = -1;
	for (int i = 0; i < this->psize; i++)
	{
		if (pcb[i] != NULL)
		{
			if (strcmp(nameParentThread, pcb[i]->GetFileName()) == 0)
			{
				parentID = pcb[i]->GetID();
				break;
			}
		}
	}

	if (parentID == -1)
	{
		printf("No have parent");
		bmsem->V();
		return -1;
	}
	
	pcb[freeSlot]->parentID = parentID;

    //Gọi thực thi phương thức Exec của lớp PCB.
	int pID = pcb[freeSlot]->Exec(name, freeSlot);
    //Gọi bmsem->V().
	//Trả về kết quả thực thi của PCB->Exec.
    bmsem->V();

    return pID;
}

int PTable::ExitUpdate(int ec){	
	printf("Exit %d\n", ec);
	char * nameThread = currentThread->getName();
	int pid = -1;
	for (int i = 0; i < this->psize; i++)
	{
		if (pcb[i] != NULL)
		{
			if (strcmp(nameThread, pcb[i]->GetFileName()) == 0)
			{
				pid = i;
				break;
			}
		}
	}

	if (pid == -1)
		return -1;

	//Nếu tiến trình gọi là main process thì gọi Halt().
	if(pid == 0){
		interrupt->Halt();
		return 0;
	}

	//Ngược lại gọi SetExitCode để đặt exitcode cho tiến trình gọi.
	int idParent = pcb[pid]->parentID;
	pcb[pid]->SetExitCode(ec);
	if (idParent != -1)
	{
		//Gọi JoinRelease để giải phóng tiến trình cha đang đợi nó(nếu có) và ExitWait() để xin tiến trình cha
		//cho phép thoát.
		pcb[idParent]->JoinRelease();
		pcb[pid]->ExitWait();
	}

    this->Remove(pid);
	currentThread->Finish();
	return ec;
}

int PTable::JoinUpdate(int id){
	char * nameParentThread = currentThread->getName();
	int parrentID = -1;
	for (int i = 0; i < this->psize; i++)
	{
		if (pcb[i] != NULL)
		{
			if (strcmp(nameParentThread, pcb[i]->GetFileName()) == 0)
			{
				parrentID = i;
				break;
			}
		}
	}

	if (parrentID == -1)
		return -1;

	//kt xem phai la parent cua tien trinh co parrentID = id hay khong
	if(parrentID != pcb[id]->parentID){
		printf("khong phai la tien trinh cha cua %d",id);
		return -1;
	}

	//Tăng numwait và gọi JoinWait() để chờ tiến trình con thực hiện.
	pcb[parrentID]->IncNumWait();
	pcb[parrentID]->JoinWait();

	printf("OK Release\n");
	//Xử lý exitcode.
	int ec = pcb[id]->GetExitCode();
	//Sau khi tiến trình con thực hiện xong, tiến trình đã được giải phóng,ExitRelease() để cho phép tiến trình con thoát.
	pcb[id]->ExitRelease();
	pcb[parrentID]->DecNumWait();
	return ec;
}

int PTable::GetFreeSlot(){
	return bm->Find();
}

bool PTable::IsExist(int pid){
	return bm->Test(pid);
}

void PTable::Remove(int pid)
{
	bm->Clear(pid);
	if(pcb[pid] != NULL)
		delete pcb[pid];
}

char* PTable::GetFileName(int id)
{
	if (pcb[id] != NULL) {
		char *fileName = pcb[id]->GetFileName();
		return fileName;
	}
	return NULL;
}

Thread * PTable::GetThread(int id)
{
	if (pcb[id] != NULL) {
		return pcb[id]->GetThread();
	}
	return NULL;
}

