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

void login(void)
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
	if (ctos.acc.pass == data.pass)
	{
		strcpy(stoc.str,"登录成功");
	}
	else
	{
		strcpy(stoc.str,"密码错误");
	}
	stoc_send(&stoc);
}
int main()
{
	init_msgq();
	for(;;)
	{
		ctos_recv(&ctos,TYPE_LOGIN);
		stoc.type = ctos.pid;
		login();
	}
}
