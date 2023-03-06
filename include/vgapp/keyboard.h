#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <pthread.h>
#include <linux/input.h>

// #include <vbar/export.h>
#include "export.h"

#define MAX_KEYBOARD_CALLBACK   10
#define VBAR_KEYBOARD_KEY_DOWN  1
#define VBAR_KEYBOARD_KEY_UP    0
typedef void (*key_press_cb)(struct input_event *key, void *pdata);

struct keyboard_data {
    key_press_cb func_cb;
    void *pdata;
};
struct keyboard_callback_table {
    unsigned int index;
    unsigned int amount;
    struct keyboard_data *kdatas;
    pthread_mutex_t index_mutex;
};

#ifdef	__cplusplus
extern "C" {
#endif

VBARLIB_API int vbar_keyboard_init(void);

VBARLIB_API void vbar_keyboard_exit(void);

VBARLIB_API int vbar_keyboard_callback_register(key_press_cb func, void *pdata);
#ifdef	__cplusplus
}
#endif

#endif
