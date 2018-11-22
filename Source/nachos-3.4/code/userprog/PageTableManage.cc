#include "PageTableManage.h"
#include "bitmap.h"
#include "system.h"

PageTableManage::PageTableManage()
{
	pageTable = new BitMap(NumPhysPages);
}

int PageTableManage::FindFreeSlot()
{
	return pageTable->Find();
}

void PageTableManage::Free(int index)
{
	pageTable->Clear(index);
}

bool PageTableManage::Add(int index)
{
	if (pageTable->Test(index))
		return false;

	pageTable->Mark(index);
	return true;
}
