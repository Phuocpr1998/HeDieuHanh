#ifndef _SEM_H
#define _SEM_H

#include "copyright.h"
#include "synch.h"
#include <string.h>

class Sem{
private:
	char *name;
	Semaphore *sem; // Tạo Semaphore để quản lý
public:
// khởi tạo đối tượng Sem. Gán giá trị ban đầu là null
// nhớ khởi tạo bm sử dụng
	Sem(char* na, int i);
	~Sem(); // hủy các đối tượng đã tạo
	void wait(); // thực hiện thao tác chờ
	void signal(); // thực hiện thao tác giải phóng Semaphore
	char* GetName(); // Trả về tên của Semaphore
};
#endif