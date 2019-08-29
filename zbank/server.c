#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "msgq.h"
#include "tools.h"

pid_t sub_pid[8];
void sigint(int sig)
{
	for(int i=0; i<8; i++)
	{
		kill(sub_pid[i],SIGKILL);
	}
	raise(SIGKILL);
	
	destory_msgq();
}

int main()
{
	init_msgq();
	
	init_id(19080001);

	signal(SIGINT,sigint);
	
	sub_pid[0] = vfork();
	if(0 == sub_pid[0])
	{
		execl("open","open",NULL);
	}
	pf("开户子进程启动成功...\n");
	sub_pid[1] = vfork();
	if(0 == sub_pid[1])
	{
		execl("login","login",NULL);
	}
	pf("登录子进程启动成功...\n");
	sub_pid[2] = vfork();
	if(0 == sub_pid[2])
	{
		execl("destory","destory",NULL);
	}
	pf("销户子进程启动成功...\n");
	
	sub_pid[3] = vfork();
	if(0 == sub_pid[3])
	{
		execl("unlock","unlock",NULL);
	}
	pf("解锁子进程启动成功...\n");

	sub_pid[4] = vfork();
	if(0 == sub_pid[4])
	{
		execl("save","save",NULL);
	}
	pf("存款子进程启动成功...\n");
		
	sub_pid[5] = vfork();
	if(0 == sub_pid[5])
	{
		execl("take","take",NULL);
	}
	pf("取款子进程启动成功...\n");

	sub_pid[6] = vfork();
	if(0 == sub_pid[6])
	{
		execl("transf","transf",NULL);
	}
	pf("转账子进程启动成功...\n");
		
	sub_pid[7] = vfork();
	if(0 == sub_pid[7])
	{
		execl("query","query",NULL);
	}
	pf("查余子进程启动成功...\n");
		
	while(-1 != wait(NULL));
}
