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

void save_acc(void)
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
	if (0 < (data.money-ctos.acc.money))
	{
		data.money-=ctos.acc.money;
		lseek(fd,0,SEEK_SET);
		write(fd,&data,sizeof(Account));
		strcpy(stoc.str,"取款成功");
	}
	else
	{
		strcpy(stoc.str,"余额不足");
	}
	stoc_send(&stoc);
}
int main()
{
	init_msgq();
	for(;;)
	{
		ctos_recv(&ctos,TYPE_TAKE);
		stoc.type = ctos.pid;
		save_acc();
	}
}
