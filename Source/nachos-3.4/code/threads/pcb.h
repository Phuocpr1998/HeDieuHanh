﻿#ifndef PCB_H
#define PCB_H
#include "string.h"
#include "synch.h"

class PCB 
{
private: 
	Semaphore* joinsem; // semaphore cho quá trình join
	Semaphore* exitsem; // semaphore cho quá trình exit
	Semaphore* multex;	// semaphore cho quá trình truy xuất đọc quyền 
	int exitcode; 
	int numwait;		// số tiến trình đã join
	int id;
	char * filename;
	Thread *thread;
public: 
	int parentID; 
	PCB(); 
	PCB(int id); 
	// nạp chương trình có tên lưu trong biến filename và processID là pid 
	int Exec(char *filename, int pid); // Tạo 1 thread mới có tên là filename và process là pid 
	int GetID();					// Trả về ProcessID của tiến trình gọi thực hiện
	Thread * GetThread();
	int GetNumWait();				// Trả về số lượng tiến trình chờ 
	void JoinWait();				// 1. Tiến trình cha đợi tiến trình con kết thúc
	void ExitWait();				// 4. Tiến trình con kết thúc 
	void JoinRelease();				// 2. Báo cho tiến trình cha thực thi tiếp
	void ExitRelease();				// 3. Cho phép tiến trình con kết thúc
	void IncNumWait();				// Tăng số tiến trình chờ
	void DecNumWait();				// Giảm số tiến trình chờ 
	void SetExitCode(int ec);		// Đặt exitcode của tiến trình
	int GetExitCode();				// Trả về exitcode 
	void SetFileName(char* fn);		// Đặt tên của tiến trình
	char* GetFileName();			// Trả về tên của tiến trình 		 
	~PCB();
};

#endif // !PCB_H
