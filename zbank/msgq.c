#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include "msgq.h"
#include "tools.h"

static int ctosid;
static int stocid; 

// 初始化消息队列
void init_msgq(void)
{
	ctosid = msgget(ftok(".",123),IPC_CREAT|0644);
	if(ERROR == ctosid)
	{
		perror("msgget ctos");
		exit(ERROR);
	}
	stocid = msgget(ftok(".",321),IPC_CREAT|0644);
	if(ERROR == stocid)
	{
		perror("msgget stoc");
		exit(ERROR);
	}
	pf("ctosid=%d stocid=%d\n",ctosid,stocid);
}

// 删除消息队列
void destory_msgq(void)
{
	if(SUCCESS != msgctl(ctosid,IPC_RMID,NULL))
	{
		perror("msgctl ctosid rmid");
		return; 
	}
	
	if(SUCCESS != msgctl(stocid,IPC_RMID,NULL))
	{
		perror("msgctl stocid rmid");
		return; 
	}
}

// client 发送消息给 server
States ctos_send(const Ctos* ctos)
{
	if(NULL == ctos) return PTRNULL;
	if(SUCCESS!=msgsnd(ctosid,ctos,sizeof(Ctos)-sizeof(ctos->type),0))
	{
		perror("msgsnd ctosid");
		return FAIL;
	}
	
	return SUCCESS;
}

// server 发送消息给 client
States stoc_send(const Stoc* stoc)
{
	if(NULL == stoc) return PTRNULL;
	if(SUCCESS!=msgsnd(stocid,stoc,strlen(stoc->str)+1,0))
	{
		perror("msgsnd stocid");
		return FAIL;
	}
	
	return SUCCESS;
}

// 接收client到server的消息
States ctos_recv(Ctos* ctos,long type)
{
	if(NULL == ctos) return PTRNULL;
	size_t size = msgrcv(ctosid,ctos,sizeof(Ctos),type,0);
	if(FAIL == size)
	{
		perror("msgrcv ctosid");
		return FAIL;
	}
	
	return size;	
}

// 接收server到clitn的消息
States stoc_recv(Stoc* stoc,long type)
{
	if(NULL == stoc) return PTRNULL;
	size_t size = msgrcv(stocid,stoc,sizeof(Stoc),type,0);
	if(FAIL == size)
	{
		perror("msgrcv stocid");
		return FAIL;
	}
	
	return size;
}
