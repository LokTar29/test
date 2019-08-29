#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("num.txt",O_RDONLY);
	int num=-1;

	printf("%d",read(fd,&num,4));
	printf("  %d",num);
}
