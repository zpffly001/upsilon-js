#include <stdio.h>
#include "net.h"

void net_status_cb(uint8_t type, enum net_status status, void *pdata)
{
    printf("net_status_cb\n");
}

int main()
{
    printf("hello\n");

    int res = vbar_net_init();
    printf("res: %d\n", res);

    void *pdata = "123";
    vbar_net_status_cb func_cb = net_status_cb;
    vbar_net_status_callback_register(func_cb, pdata);

}

// build gcc -o testNet testNet.c -I ../ ../net.c