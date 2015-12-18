#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	char *leds  = "/dev/leds";
	char *test1 = "/bin/test1";
	char *test2 = "/bin/test2";
	
	if(fd = open(leds,O_RDWR|O_NOCTTY|O_NDELAY) < 0)
	{
		printf("--[1]--open [%s] failed!\n",leds);
	}
	else
	{
		printf("--[2]--open [%s] ok, fd = [%d]\n",leds,fd);
	}

	if(fd = open(test1, O_RDWR, 0777) < 0 )
	{
		printf("--[3]--open [%s] failed!\n",test1);
	}
	else
	{
		printf("--[3]--open [%s] ok, fd = [%d]\n",test1,fd);
	}

	if(fd = open(test2, O_RDWR|O_CREAT, 0777) < 0 )
	{
		printf("--[4]--open [%s] failed!\n",test2);
	}
	else
	{
		printf("--[5]--open [%s] ok, fd = [%d]\n",test2,fd);
	}
	
	return 0;
}
