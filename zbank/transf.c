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

void transf_acc(void)
{
	char path1[PATH_MAX];
	char path2[PATH_MAX];
	sprintf(path1,"%s/%u",ACC_PATH,ctos.acc.id);
	sprintf(path2,"%s/%u",ACC_PATH,ctos.acc.pass);
	int fd1 =open(path1,O_RDONLY);
	int fd2 =open(path2,O_RDWR);
	Account data1,data2;
	if(ERROR == fd2)
	{
		strcpy(stoc.str,"目标账户不存在");
		stoc_send(&stoc);
		return;
	}
	read(fd1,&data1,sizeof(Account));
	read(fd2,&data2,sizeof(Account));
	if (0 < (data1.money-ctos.acc.money))
	{
		data1.money-=ctos.acc.money;
		data2.money+=ctos.acc.money;
		lseek(fd1,0,SEEK_SET);
		lseek(fd2,0,SEEK_SET);
		write(fd1,&data1,sizeof(Account));
		write(fd2,&data2,sizeof(Account));
		strcpy(stoc.str,"转账成功");
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
		ctos_recv(&ctos,TYPE_TRANSF);
		stoc.type = ctos.pid;
		transf_acc();
	}
}
