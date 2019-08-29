#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <getch.h>
#include "states.h"
#include "tools.h"

//清理输入缓冲区
void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}

//获取字符串
char* get_str(char* str,size_t size)
{
	clear_stdin();

	fgets(str,size,stdin);
	size_t len = strlen(str);

	if(str[len-1] == '\n') 
	{
		str[len-1] = '\0';
	}

	clear_stdin();
	
	return str;
}

// 初始化id
void init_id(size_t id)
{
	if(SUCCESS == access(ID_PATH,F_OK))
	{
		return;
	}
	int fd = open(ID_PATH,O_WRONLY|O_CREAT,0644);
	if(ERROR == fd)
	{
		perror("open ID_PATH");
		return;
	}
	
	write(fd,&id,sizeof(id));
}

// 获取id
size_t get_id(void)
{
	size_t id = 0;
	int fd = open(ID_PATH,O_RDWR);
	if(ERROR == fd)
	{
		perror("open ID_PATH");
		return 0;
	}
	
	read(fd,&id,sizeof(id));
	id++;
	lseek(fd,0,SEEK_SET);
	write(fd,&id,sizeof(id));
	return id-1;
}

//获取指令
char get_cmd(char start,char end)
{
	clear_stdin();

	printf("请输入指令:");
	for(;;)
	{
		char val = getch();
		if(val >= start && val <= end)
		{
			printf("%c\n",val);
			return val;
		}
	}
}
