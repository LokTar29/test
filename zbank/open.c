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

void open_acc(void)
{
	size_t id = get_id();
	char path[PATH_MAX];
	sprintf(path,"%s/%u",ACC_PATH,id);
	pf("acc path:%s\n",path);
	int fd = open(path,O_WRONLY|O_CREAT|O_EXCL,0644);
	if(ERROR == fd)
	{
		perror("open acc");
		strcpy(stoc.str,"服务器正在升级，请耐心等待...");
	}
	else
	{
		write(fd,&ctos.acc,sizeof(ctos.acc));
		sprintf(stoc.str,"恭喜您开户成功，您的银行卡号为:%u",id);
	}
	// 返回开户成功信息
	stoc_send(&stoc);
}

int main()
{
	init_msgq();
	for(;;)
	{
		ctos_recv(&ctos,TYPE_OPEN);
		stoc.type = ctos.pid;
		open_acc();
	}
}
