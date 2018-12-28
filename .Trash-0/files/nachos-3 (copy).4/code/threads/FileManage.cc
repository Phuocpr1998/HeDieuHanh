#include "openfile.h"
#include "FileManage.h"

FileManage::FileManage(int maxFile)
{
	if (maxFile > 0)
	{
		arrayFile = new FileCustom*[maxFile];
		size = maxFile;
	}
	else 
	{
		arrayFile = new FileCustom*[10];
		size = 10;
	}

	for (int i = 0; i < size; i++)
	{
		arrayFile[i] = NULL;
	}
}

int FileManage::FindFreeSlot()
{
	for (int i = 2; i < size; i++)
	{
		if (arrayFile[i] == NULL)
			return i;
	}
	return -1;
}

bool FileManage::Add(int id, OpenFile * openFile, int type)
{
	// kiểm tra id
	if (id < 2 || id >= size || arrayFile[id] != NULL)
		return false;

	// kiểm tra loại tập tin
	if (type != 0 && type != 1)
		return false;

	// kiểm tra con trỏ open file
	if (openFile == NULL)
		return false;


	FileCustom *file = new FileCustom;
	file->file = openFile;
	file->pos = 0;
	file->type = type;

	arrayFile[id] = file;
	return true;
}

FileCustom * FileManage::GetFile(int id)
{
	// kiểm tra id
	if (id < 2 || id >= size || arrayFile[id] == NULL)
		return NULL;

	return arrayFile[id];
}

int FileManage::Seek(int id, int position)
{
	// kiểm tra id
	if (id < 2 || id >= size || arrayFile[id] == NULL)
		return -1;
	// kiểm tra position
	int len = arrayFile[id]->file->Length();
	if (position < 0 || position >= len) {
		position = len - 1;
	}

	arrayFile[id]->pos = position;
	return position;
}

bool FileManage::CloseFile(int id)
{
	// kiểm tra id
	if (id < 2 || id >= size || arrayFile[id] == NULL)
		return false;
	
	// xóa vùng nhớ đã cấp phát
	delete arrayFile[id]->file;
	delete arrayFile[id];

	// 
	arrayFile[id] = NULL;
	return true;
}
