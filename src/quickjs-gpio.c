#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


#include "quickjs.h"
#include "quickjs-gpio.h"
#include "quickjs-common.h"
#include "gpio.h"


/**
 * @brief gpio 初始化
 */
static JSValue gpioInit(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    /* gpio 初始化  return 0：成功， -1：失败 */
    vbar_gpio_init();
    return JS_UNDEFINED;
}

/**
 * @brief 释放gpio资源
 */
static JSValue gpioExit(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{


    /* 释放gpio资源 */
    vbar_gpio_exit();

    return JS_UNDEFINED;
}

/**
 * @brief 申请gpio
 */
static JSValue gpioRequest(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    JS_ToInt32(ctx, &gpio, argv[0]);

    /* 申请gpio  0：成功，<0：失败 */
    int res = vbar_gpio_request(gpio);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 释放指定gpio
 */
static JSValue gpioFree(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    JS_ToInt32(ctx, &gpio, argv[0]);

    /* 释放指定gpio */
    vbar_gpio_free(gpio);
    return JS_UNDEFINED;
}

/**
 * @brief 设置指定gpio功能
 */
static JSValue gpioSetFunc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int gpio;
    enum gpio_function func;

    JS_ToInt32(ctx, &gpio, argv[0]);
    JS_ToInt32(ctx, &func, argv[1]);

    /* 设置指定gpio功能  param gpio  gpio值  param func  功能类型 */
    vbar_gpio_set_func(gpio, func);
    return JS_UNDEFINED;
}

/**
 * @brief 设置指定gpio上拉状态
 */
static JSValue gpioSetPullState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    int state;
    JS_ToInt32(ctx, &gpio, argv[0]);
    JS_ToInt32(ctx, &state, argv[1]);

    /* 设置指定gpio上拉状态 */
    vbar_gpio_set_pull_state(gpio, state);
    return JS_UNDEFINED;
}

/**
 * @brief 获取指定gpio上拉状态
 */
static JSValue gpioGetPullState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    JS_ToInt32(ctx, &gpio, argv[0]);

    /* 获取指定gpio上拉状态 */
    int res = vbar_gpio_get_pull_state(gpio);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 设置指定gpio的值
 */
static JSValue gpioSetValue(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    int value;
    JS_ToInt32(ctx, &gpio, argv[0]);
    JS_ToInt32(ctx, &value, argv[1]);

    /* 设置指定gpio的值 */
    vbar_gpio_set_value(gpio, value);
    return JS_UNDEFINED;
}

/**
 * @brief 获取指定gpio值
 */
static JSValue gpioGetValue(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    JS_ToInt32(ctx, &gpio, argv[0]);

    /* 获取指定gpio值 */
    int res = vbar_gpio_get_value(gpio);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 设置指定gpio的驱动能力
 */
static JSValue gpioSetDriveStrength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    int strength;
    JS_ToInt32(ctx, &gpio, argv[0]);
    JS_ToInt32(ctx, &strength, argv[1]);

    /* 设置指定gpio的驱动能力 */
    vbar_gpio_set_drive_strength(gpio, strength);
    return JS_UNDEFINED;
}

/**
 * @brief 获取指定gpio的驱动能力
 */
static JSValue gpioGetDriveStrength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int gpio;
    JS_ToInt32(ctx, &gpio, argv[0]);

    /* 获取指定gpio的驱动能力  0：失败， >0 成功 */
    int res = vbar_gpio_get_drive_strength(gpio);
    return JS_NewInt32(ctx, res);
}



/* 构造方法 */
static JSValue gpioContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, gpioClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry gpio_class_funcs[] = {
    JS_CFUNC_DEF("gpioInit", 0, gpioInit),
    JS_CFUNC_DEF("gpioExit", 0, gpioExit),
    JS_CFUNC_DEF("gpioRequest", 1, gpioRequest),
    JS_CFUNC_DEF("gpioFree", 1, gpioFree),
    JS_CFUNC_DEF("gpioSetFunc", 2, gpioSetFunc),
    JS_CFUNC_DEF("gpioSetPullState", 2, gpioSetPullState),
    JS_CFUNC_DEF("gpioGetPullState", 1, gpioGetPullState),
    JS_CFUNC_DEF("gpioSetValue", 2, gpioSetValue),
    JS_CFUNC_DEF("gpioGetValue", 1, gpioGetValue),
    JS_CFUNC_DEF("gpioSetDriveStrength", 2, gpioSetDriveStrength),
    JS_CFUNC_DEF("gpioGetDriveStrength", 1, gpioGetDriveStrength),
};


/* 当前类数据结构 */
JSFullClassDef gpioClass = {
    .def = {
        .class_name = "gpioClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { gpioContructor, .args_count = 1 },
    .funcs_len = sizeof(gpio_class_funcs),
    .funcs = gpio_class_funcs
};


/* 给对象绑定属性 */
static int gpio_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &gpioClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建gpioClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前gpioClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_GPIO_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, gpio_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, gpioClass.def.class_name);
    return m;
}