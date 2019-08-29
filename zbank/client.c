#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "msgq.h"
#include "tools.h"

Ctos ctos;
Stoc stoc;

void open_acc(void);
void login(void);
void destory(void);
void unlock(void);
void save(size_t n);
void take(size_t n);
void transf(size_t n);
void query(size_t n);
void main_menu(void);
void sub_menu(size_t n);

int main()
{
	ctos.pid = getpid();
	// 初始化消息队列
	init_msgq();
	// 进入主菜单
	main_menu();
}

void open_acc(void)
{
	ctos.type = TYPE_OPEN;
	
	pf("请输入姓名：");
	get_str(ctos.acc.name,20);
	pf("请输入身份证号:");
	get_str(ctos.acc.card,19);
	pf("请设置您的密码:");
	sf("%d",&ctos.acc.pass);
	pf("请设置您的金额:");
	sf("%f",&ctos.acc.money);
	ctos.acc.errno = 0;
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void login(void)
{
	ctos.type = TYPE_LOGIN;
	pf("请输入账号：");
	sf("%d",&ctos.acc.id);
	size_t n =ctos.acc.id;
	for(int i=0;i<3;i++)
	{
		pf("请输入您的密码:");
		sf("%d",&ctos.acc.pass);
		ctos_send(&ctos);
		stoc_recv(&stoc,ctos.pid);
		if(0 == strcmp("登录成功",stoc.str))
		{
			pf("server:%s\n",stoc.str);
			sub_menu(n);
			break;
		}
		else if (0 == strcmp("无此账号",stoc.str))
		{
			pf("server:%s\n",stoc.str);
			break;
		}
		else
		{
			pf("server:%s\n",stoc.str);
		}
		
	}
}

void destory(void)
{
	ctos.type = TYPE_DESTORY;
	pf("请输入账号：");
	sf("%d",&ctos.acc.id);
	pf("请输入身份证号:");
	get_str(ctos.acc.card,19);
	pf("请设置您的密码:");
	sf("%d",&ctos.acc.pass);
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void unlock(void)
{
	ctos.type = TYPE_UNLOCK;
	pf("请输入账号：");
	sf("%d",&ctos.acc.id);
	pf("请输入身份证号:");
	get_str(ctos.acc.card,19);
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void save(size_t n)
{
	ctos.type = TYPE_SAVE;
	ctos.acc.id = n;
	pf("请输入要存的金额:");
	sf("%f",&ctos.acc.money);
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void take(size_t n)
{
	ctos.type = TYPE_TAKE;
	ctos.acc.id = n;
	pf("请输入要取的金额:");
	sf("%f",&ctos.acc.money);
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void transf(size_t n)
{
	ctos.type = TYPE_TRANSF;
	ctos.acc.id = n;
	pf("请输入目标账号：");
	sf("%d",&ctos.acc.pass);
	pf("请输入要转的金额:");
	sf("%f",&ctos.acc.money);
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void query(size_t n)
{
	ctos.type = TYPE_QUERY;
	ctos_send(&ctos);
	stoc_recv(&stoc,ctos.pid);
	pf("server:%s\n",stoc.str);
}

void main_menu(void)
{
	for(;;)
	{
		system("clear");
		pf("1、开户	2、登录\n");
		pf("3、销户	4、解锁\n");
		switch(get_cmd('1','4'))
		{
			case '1': open_acc(); break;
			case '2': login(); break;
			case '3': destory(); break;
			case '4': unlock(); break;
			case 27: return;
		}
	}
}

void sub_menu(size_t n)
{
	for(;;)
	{
		system("clear");
		pf("1、存款	2、取款\n");
		pf("3、转账	4、查余	5、返回\n");
		switch(get_cmd('1','4'))
		{
			case '1': save(n); break;
			case '2': take(n); break;
			case '3': transf(n); break;
			case '4': query(n); break;
			case '5': return;
		}
	}
}

