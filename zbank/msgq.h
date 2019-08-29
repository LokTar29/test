#ifndef MSGQ_H
#define MSGQ_H

#include <stdio.h>
#include "states.h"

#define TYPE_OPEN		111
#define TYPE_LOGIN		222
#define TYPE_DESTORY	333
#define TYPE_UNLOCK		444
#define TYPE_SAVE		555
#define TYPE_TAKE		666
#define TYPE_TRANSF		777
#define TYPE_QUERY		888

typedef struct Account
{
	size_t id;
	int pass;
	char name[20];
	char card[19];
	float money;
	size_t errno;
}Account;

typedef struct Ctos
{
	long type;
	pid_t pid;
	Account acc;
}Ctos;

typedef struct Stoc
{
	long type;
	char str[256];
}Stoc;

// 初始化消息队列
void init_msgq(void);

// 删除消息队列
void destory_msgq(void);

// client 发送消息给 server
States ctos_send(const Ctos* ctos);

// server 发送消息给 client
States stoc_send(const Stoc* stoc);

// client 接收server发来的消息
States ctos_recv(Ctos* ctos,long type);

// server 接收client发来的消息
States stoc_recv(Stoc* stoc,long type);

#endif//MSGQ_H
