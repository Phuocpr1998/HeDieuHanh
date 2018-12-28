#include "syscall.h"
#include "copyright.h"

#define MAXLEN 100


int main()
{
	char command[MAXLEN];
	OpenFileId file; 
	int threadId, byteReaded;
	int i = 0;
	do
	{
		Write("~: ",4, ConsoleInput);
		byteReaded = Read(command, MAXLEN, ConsoleOutput);
		if(byteReaded == -1){
			Write("Error!\n", 8, ConsoleInput);
		}
		else{
			if(StrCmp(command,"exit") == 0){
				break;
			}
			else{
				file = Open(command,ReadOnly);
				if(file <= 0){
					Write("Ten file loi\n",15, ConsoleInput);
				}
				else{
					CloseFile(file);

					threadId = Exec(command);
					Join(threadId);

					Write("\n",1 , ConsoleInput);
				}
				for (; i < byteReaded; ++i)
				{
					command[i] = 0;
				}
			}

		}

	}while(1);
}