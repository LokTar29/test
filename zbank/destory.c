#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include "msgq.h"
#include "tools.h"

Ctos ctos;
Stoc stoc;

void destory_acc(void)
{
	char path[PATH_MAX];
	sprintf(path,"%s/%u",ACC_PATH,ctos.acc.id);
	int fd =open(path,O_RDONLY);
	Account data;
	if(ERROR == fd)
	{
		strcpy(stoc.str,"无此账号");
		stoc_send(&stoc);
		return;
	}
	read(fd,&data,sizeof(Account));
	if ((ctos.acc.pass == data.pass)&&(0 == strcmp(ctos.acc.card,data.card)))
	{
		if (0 == remove(path))
		{
			strcpy(stoc.str,"销户成功");
			int fd2 =open(path,O_WRONLY|O_APPEND);
			write(fd2,&ctos.acc.id,4);
		}
	}
	else
	{
		strcpy(stoc.str,"销户失败");
	}
	stoc_send(&stoc);
}
int main()
{
	init_msgq();
	for(;;)
	{
		ctos_recv(&ctos,TYPE_DESTORY);
		stoc.type = ctos.pid;
		destory_acc();
	}
}
