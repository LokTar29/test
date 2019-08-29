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

void unlock(void)
{
	char path[PATH_MAX];
	sprintf(path,"%s/%u",ACC_PATH,ctos.acc.id);
	int fd =open(path,O_RDWR);
	Account data;
	if(ERROR == fd)
	{
		strcpy(stoc.str,"无此账号");
		stoc_send(&stoc);
		return;
	}
	read(fd,&data,sizeof(Account));
	if (0 == strcmp(ctos.acc.card,data.card))
	{
		lseek(fd,0,SEEK_SET);
		data.errno=0;
		write(fd,&data,sizeof(Account));
		strcpy(stoc.str,"解锁成功");
	}
	else
	{
		strcpy(stoc.str,"信息错误，解锁失败");
	}
	stoc_send(&stoc);
}

int main()
{
	init_msgq();
	for(;;)
	{
		ctos_recv(&ctos,TYPE_UNLOCK);
		stoc.type = ctos.pid;
		unlock();
	}
}
