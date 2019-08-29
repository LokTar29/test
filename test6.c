#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main()
{
	char* netip ="192.168.1.1";
	in_addr_t ip = inet_addr(netip);
	printf("%u\n",ip);
	printf("%u\n",htonl(ip));
}
