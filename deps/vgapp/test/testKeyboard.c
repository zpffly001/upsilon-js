#include <stdio.h>
#include <time.h>
#include "keyboard.h"

// gcc -o testKeyboard testKeyboard.c -I ../ ../keyboard.c

struct input_event event = {
    .time.tv_usec = 0,
    .type         = EV_KEY,
    .code         = 1,
    .value        = 0,
};

void keyPressCallback(struct input_event *key, void *pdata)
{

}

int main()
{
    vbar_keyboard_init();

    event.time.tv_sec  = time(0);

    key_press_cb func = keyPressCallback;
    void *pdata = "hhh";

    int res = vbar_keyboard_callback_register(func, pdata);
    printf("result: %d\n", res);

    vbar_keyboard_exit();
    return 1;
}