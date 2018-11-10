#ifndef _FILEMANAGE_H
#define _FILEMANAGE_H
#include "copyright.h"

#define MAXFILE 10

class OpenFile;

struct FileCustom {
	OpenFile* file;
	int type;
	int pos;
};

class FileManage {
private:
	FileCustom** arrayFile;
	int size;
public:
	FileManage(int maxFile);
	// trả về vị trí còn trống (ID)
	// nếu không còn vị trí trống trả về -1
	int FindFreeSlot();

	// thêm file mới vào vị trí id (được tìm ở trên)
	// type: 0 là readonly, 1 là read write
	// nếu thành công trả về true, ngược lại trả về false
	bool Add(int id, OpenFile *openFile, int type);

	// lấy con trỏ Open file tại vị trí id
	// nếu lỗi sẽ trả về null
	FileCustom* GetFile(int id);

	// chuyển vị trí đọc ghi
	// trả về vị trí thật đã dịch
	// nếu có lỗi trả về -1
	int Seek(int id, int position);

	// nếu đóng thành công trả về true
	// ngược lại false
	bool CloseFile(int id);

	~FileManage()
	{
		if (arrayFile != NULL)
		{
			for (int i = 0; i < size; i++)
			{
				if (arrayFile[i] != NULL)
					delete arrayFile;
			}
			delete[] arrayFile;
		}
	}
};


#endif