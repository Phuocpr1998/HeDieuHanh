#ifndef _SEM_H
#define _SEM_H

#include "copyright.h"
#include "bitmap.h"
#include "pcb.h"
#include "schandle.h"
#include "semaphore.h"
#include "system.h"
#include <string.h>

class Sem{
private:
	char name[50];
	Semaphore *sem; // Tạo Semaphore để quản lý
public:
// khởi tạo đối tượng Sem. Gán giá trị ban đầu là null
// nhớ khởi tạo bm sử dụng
	Sem(char* na, int i);
	~Sem(); // hủy các đối tượng đã tạo
	void wait(); // thực hiện thao tác chờ
	void signal(); // thực hiện thao tác giải phóng Semaphore
	char* GetName(); // Trả về tên của Semaphore
}
#endif