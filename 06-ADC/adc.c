#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char ** argv)
{
        int fd;
        char* adc_dev = "/dev/adc";
        char buff[512];
        int len = 0;
        memset(buff,0,sizeof(buff));
        
        printf("adc is ready\n");
        
        
        fd = open(adc_dev, O_RDWR|O_NOCTTY|O_NDELAY);
        if(fd < 0)
        {
                printf("open device: '%s', failed.\n", adc_dev);
                return 0;
        }
        else
        {	
        	printf("ioctl operation on '%s' success\n", adc_dev);
                len = read(fd,buff,10);
                close(fd);
                
                if(len == 0)
                {
                	printf("return 'null'\n");
                }
                else
                {
                	int v = atoi(buff);
                	v = (int)(v*10000/4095);
                	printf("re's value is %d\n",v);
                }  
        }

        return (0); 
}
