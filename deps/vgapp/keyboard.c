#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "keyboard.h"

int vbar_keyboard_init(void)
{
    printf("vbar_keyboard_init\n");
    return 1;
}

void vbar_keyboard_exit(void)
{
    printf("vbar_keyboard_exit\n");
}

int vbar_keyboard_callback_register(key_press_cb func, void *pdata)
{
    printf("vbar_keyboard_callback_register\n");
    return 1;
}