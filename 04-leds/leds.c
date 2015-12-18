#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LED_NUM 5       // 两个led等，1(led2)表示靠近蜂鸣器，0表示靠近独立按键
#define LED_CMD 5       // led等状态，0灭，1亮

#include "ledsConfig.h"

int main(int argc, char ** argv)
{
        int fd;

        char* led_dev = "/dev/leds";

        if(argc != 3)
        {
                printf("i need two number args\n");
                printf("argv[1]=> 亮(1), 灭(0)\n");
                printf("argv[2]=> 蜂led2(1), 键(0)\n");
                return 0;
        }

        printf("argv1 => cmd, argv2 => io\n");
        if(atoi(argv[1]) >= LED_CMD)
        {
                printf("argv1 must be 0/1.\n");
                return 0;
        }

        if(atoi(argv[2]) >= LED_NUM)
        {
                printf("argv2 must be 0/1.\n");
                return 0;
        }

        fd = open(led_dev, O_RDWR|O_NOCTTY|O_NDELAY);
        if(fd < 0)
        {
                printf("open device: '%s', failed.\n",led_dev);
                return 0;
        }
        else
        {
                ioctl(fd,atoi(argv[1]),atoi(argv[2]));
                printf("ioctl operation on '%s' success\n",led_dev);
        }
        close(fd);

        return (0); 
}
