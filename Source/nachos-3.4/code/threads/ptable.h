#ifndef _P_TABLE_H
#define _P_TABLE_H

#include "copyright.h"
#include "bitmap.h"
#include "pcb.h"

#define MAX_PROCESS 10

class Semaphore;

class PTable{
private:
	BitMap* bm;
	PCB *pcb[MAX_PROCESS];
	int psize;
	Semaphore *bmsem;
	// đánh dấu các vị trí đã được sử dụng trong pcb
	// dùng để ngăn chặn trường hợp nạp 2 tiến trình cùng lúc
public:
	PTable();
	// khởi tạo size đối tượng PCB để lưu size process. Gán giá trị ban đầu là null
	// nhớ khởi tạo bm và bmsem để sử dụng
	PTable(int size);
	~PTable(); // hủy các đối tượng đã tạo
	int ExecUpdate(char* name); // Xử lý cho system call SC_Exit
	int ExitUpdate(int ec); // Xử lý cho system call SC_Exit
	int JoinUpdate(int id); // Xử lý cho system call SC_Join
	int GetFreeSlot(); // tìm free slot để lưu thông tin cho tiến trình mới
	bool IsExist(int pid); // kiểm tra tồn tại processID này không?
	void Remove(int pid); // khi tiến trình kết thúc, delete processID ra khỏi mang ql no
	char* GetFileName(int id);// Trả về tên của tiến trình
	Thread * GetThread(int id); // Trả về Thread của tiến trình
};

#endif