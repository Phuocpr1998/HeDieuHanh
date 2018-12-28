#ifndef _PAGETABLE_MANAGE_H
#define _PAGETABLE_MANAGE_H

class BitMap;

class PageTableManage {
private:
	BitMap *pageTable;
public:
	PageTableManage();

	int FindFreeSlot(); // tìm page trống nếu có trả về vị trí, ngược lại trả về -1

	void Free(int index); // giải phóng page thứ index

	bool Add(int index); // đánh dấu page đã được sử dụng, nếu đánh dấu thành công trả về true, 
						// ngược lại trả về false

	~PageTableManage()
	{
		delete pageTable;
	}
};



#endif // !_PAGETABLE_MANAGE_H
