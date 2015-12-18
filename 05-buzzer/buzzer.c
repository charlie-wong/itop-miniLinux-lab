#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUZZER_CNT 2

#include "buzzerConfig.h"

int main(int argc, char ** argv)
{
        int fd;
        char* buzzer_dev = "/dev/buzzer_ctl";
        int ret;

        if(argc != BUZZER_CNT || atoi(argv[1]) >= BUZZER_CNT)
        {
        	printf("only need one arg, and the only arg is 1/0\n");
                return 0;
        }


        fd = open(buzzer_dev, O_RDWR|O_NOCTTY|O_NDELAY);
        if(fd < 0)
        {
                printf("open device: '%s', failed.\n", buzzer_dev);
                return 0;
        }
        else
        {
                ret = ioctl(fd,atoi(argv[1]),NULL);
                printf("ioctl operation on '%s' success\n", buzzer_dev);
        }
        close(fd);

        return (0); 
}
