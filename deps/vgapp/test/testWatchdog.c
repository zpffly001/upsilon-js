#include <stdio.h>
#include "watchdog.h"

// gcc -o testWatchdog testWatchdog.c -I ../ ../watchdog.c

int main()
{

    struct vbar_watchdog *dog = vbar_watchdog_open(1, 1);
    char *buf = dog->pdata;
    printf("buf[1]: %d\n", ((char *)dog->pdata)[0]);
    printf("buf[2]: %d\n", ((char *)dog->pdata)[1]);

    bool isStart = vbar_watchdog_start(dog, 3000);
    printf("is start: %d\n", isStart);
    printf("buf[1]: %d\n", buf[0]);
    printf("buf[2]: %d\n", buf[1]);

    vbar_watchdog_enable(dog, 1, true);

    vbar_watchdog_close(dog);

    return 1;
}