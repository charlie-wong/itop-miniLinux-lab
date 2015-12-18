#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

void set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop);

void main(int argc, char **argv)
{
	int fd;
	
	char *uart3 = "/dev/ttySAC1";
	char *import_str = "waiting data";
	char *import_clo = "closed!\n";
	
	printf("\nUART write test from con3 start\n");
	
	fd = open(uart3, O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd < 0)
	{
		printf("open '%s' is failed", uart3);
	}
	else
	{
		printf("open '%s' is success\n", uart3);
		
		set_opt(fd, 115200, 8, 'N', 1);
		int wr_state;

		char read_buff[512];
		memset(read_buff, 0, sizeof(read_buff));
		int read_char_cnt = 1;
		while(read_char_cnt)
		{
			wr_state = write(fd,import_str, strlen(import_str));	
			if(wr_state<0)
			{
				printf("write failed\n");
			}
			int time_cnt = 10;
			while(time_cnt)
			{
				time_cnt--;
				wr_state = write(fd,".", strlen("."));	
				if(wr_state<0)
				{
					printf("write failed\n");
				}
				sleep(1);
			}
			
			read_char_cnt = read(fd, read_buff, sizeof(read_buff)-1);
			
			char ref_read_buff[1024];
			memset(ref_read_buff, 0, sizeof(ref_read_buff));
			
			sprintf(ref_read_buff, "\n[%d] => [%s]", read_char_cnt, read_buff);
			
			wr_state = write(fd, ref_read_buff, strlen(ref_read_buff));	
			if(wr_state<0)
			{
				printf("write failed\n");
			}
			
			memset(read_buff, 0, sizeof(read_buff));
		}
		
		wr_state = write(fd,import_clo, strlen(import_clo));	
		if(wr_state<0)
		{
			printf("write failed\n");
		}
	}
	close(fd);
	return 0;
}


void set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio;
	struct termios oldtio;
	
	if(tcgetattr(fd,&oldtio) != 0)
	{ 
		perror("SetupSerial 1");
		return;
	}
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch(nBits)
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch(nEvent)
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch(nSpeed)
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	if(nStop == 1)
	{
		newtio.c_cflag &=  ~CSTOPB;
	}
	else if(nStop == 2)
	{
		newtio.c_cflag |=  CSTOPB;
	}
	
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN]   = 0;
	tcflush(fd,TCIFLUSH);
	
	if((tcsetattr(fd,TCSANOW,&newtio)) != 0)
	{
		perror("com set error");
		return;
	}
	return;
}


