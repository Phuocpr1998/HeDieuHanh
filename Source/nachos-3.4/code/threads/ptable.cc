#include "ptable.h"

PTable::PTable(int size){

	psize = size;
	bm = new BitMap(size);
	bmsem = new Semaphore("bmsem", 1);

	for(int i=0, i < MAX_PROCESS, i++){
		pcb[i] = 0;//null :v 
	}

	bm->Mark(0);

	//Khoi tao PCB
	pcb[0] = new PCB(0);//tien trinh co id = 0
	pcb[0]->parentID = -1; // khong co tien trinh cha
}

PTable::~PTable(){
	if(bm != 0){
		delete bm;
	}

	if(bmsem != 0){
		delete bmsem;
	}

	for(int i =0, i < MAX_PROCESS, i++){
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

    if(strcmp(name,currentThread->getName())== 0){
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
    pcb[freeSlot]->parrentID = currentThread->processID

    //Danh dau da su dung ????

    //Gọi thực thi phương thức Exec của lớp PCB.
    int pID = pcb[freeSlot]->Exec(name, freeSlot)

    //Gọi bmsem->V().
	//Trả về kết quả thực thi của PCB->Exec.

    bmsem->V();

    return pID;
}

int PTable::ExitUpdate(int ec){	

	//KT pid co ton tai khong
	int pid = currentThread->processID;

	if(this->IsExist(pid) == false){
		printf("Tien trinh khong ton tai\n");
		return -1;
	}
	//freeSpace
	currentThread->FreeSpace()
	//Nếu tiến trình gọi là main process thì gọi Halt().
	if(pid == 0){
		interrupt->Halt();
		return 0;
	}
	currentThread->Finish();
	//Ngược lại gọi SetExitCode để đặt exitcode cho tiến trình gọi.
	pcb[pid]->SetExitCode(ec);
	//Gọi JoinRelease để giải phóng tiến trình cha đang đợi nó(nếu có) và ExitWait() để xin tiến trình cha
    //cho phép thoát.
    pcb[pid]->JoinRelease();
    pcb[pid]->ExitWait();

    this->Remove(pid);

    return ec;
}

int PTable::JoinUpdate(int id){

	int parrentID = currentThread->currentThread;
	//check
	if(id < 0){
		printf("id khong hop le\n");
		return -1;
	}
	//kt xem phai la parent cua tien trinh co pid = id hay khong
	if(parrentID != pcb[id]->parrentID){
		printf("khong phai la tien trinh cha cua %d",id);
		return -1;
	}

	//Tăng numwait và gọi JoinWait() để chờ tiến trình con thực hiện.
	pcb[parrentID]->IncNumWait();
	pcb[id]->JoinWait();

	//Xử lý exitcode.
	int ec = pcb[id]->GetExitCode();
	//Sau khi tiến trình con thực hiện xong, tiến trình đã được giải phóng,ExitRelease() để cho phép tiến trình con thoát.
	pcb[id]->ExitRelease();

	return ec;
}

int PTable::GetFreeSlot(){
	return bm->Find();
}

bool PTable::IsExist(int pid){
	return bm->Test(pid);
}

void PTable::Remove(int pid){
	bm->Clear(pid);
	if(pcb[pid] !=0)
		delete pcb[pid];
}

char* PTable::GetFileName(int id){
	return pcb[id]->GetFileName();
}