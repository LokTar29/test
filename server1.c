#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

void* startup(void* arg)
{
	int clifd = *(int*)arg;
	char buf[1024] = {};
			for(;;)
			{
				printf("read:");
				read(clifd,buf,sizeof(buf));
				printf("%s\n",buf);
				if(0 == strcmp("quit",buf))
				{
					close(clifd);
					return 0;
				}
				write(clifd,buf,strlen(buf)+1);
			}
}

int main()
{
	printf("服务器创建socket...\n");
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > sockfd)
	{
		perror("socket");
		return -1;
	}

	printf("准备地址...\n");
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7777);
	addr.sin_addr.s_addr = inet_addr("192.168.43.183");
	socklen_t len = sizeof(addr);

	printf("绑定socket与地址...\n");
	if(bind(sockfd,(struct sockaddr*)&addr,len))
	{
		perror("bind");
		return -1;
	}

	printf("设置监听...\n");
	if(listen(sockfd,5))
	{
		perror("listen");
		return -1;
	}

	printf("等待客户端连接...\n");
	for(;;)
	{
		struct sockaddr_in addrcli = {};
		int clifd = accept(sockfd,(struct sockaddr*)&addrcli,&len);
		if(0 > clifd)
		{
			perror("accept");
			continue;
		}
		pthread_t pid;
		pthread_create(&pid,NULL,startup,&clifd);
	}
}
