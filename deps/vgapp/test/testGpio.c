#include <stdio.h>
#include "gpio.h"

int main()
{
    printf("hello\n");
    vbar_gpio_init();
    int res = vbar_gpio_request(2);
    printf("res: %d\n", res);
}

// build gcc -o testGpio testGpio.c -I ../ ../gpio.c