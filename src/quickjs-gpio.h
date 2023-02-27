#ifndef QUICKJS_GPIO_H
#define QUICKJS_GPIO_H

#include "quickjs.h"
#include "quickjs-common.h"

#define JS_INIT_GPIO_MODULE js_init_module

enum gpio_function {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

JSFullClassDef gpioClass;

#endif // !QUICKJS_GPIO_H




