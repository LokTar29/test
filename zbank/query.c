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

void query_acc(void)
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
	sprintf(stoc.str,"余额为%f",data.money);
	stoc_send(&stoc);
}
int main()
{
	init_msgq();
	for(;;)
	{
		ctos_recv(&ctos,TYPE_QUERY);
		stoc.type = ctos.pid;
		query_acc();
	}
	
}
