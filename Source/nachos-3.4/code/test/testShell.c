#include "syscall.h"
#include "copyright.h"

#define MAXLEN 32


int main()
{
	char command[MAXLEN + 1];
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
				if(file < 0){
					Write("Ten file loi\n",15, ConsoleInput);
				}
				else{
					CloseFile(file);

					threadId = Exec(command);
					Join(threadId);

					Write("\n",1 , ConsoleInput);
				}
				command[0] = '\0';

				/*for (; i < byteReaded; ++i)
				{
					command[i] = 0;
				}*/
			}

		}

	}while(1);
}