#include <stdio.h>
#include<dlfcn.h>

// build gcc -o testDopen testDopen.c

int main()
{
    void *hd = dlopen("../channel-main.so", RTLD_NOW | RTLD_LOCAL);
    if (!hd) {
        printf("open so fail\n");
    }else{
        printf("open so success\n");
    }

    return 0;
}