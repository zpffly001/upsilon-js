#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>


#include "quickjs.h"
#include "quickjs-common.h"
#include "quickjs-watchdog.h"
#include "watchdog.h"


struct vbar_watchdog *wdt;

/**
 * @brief 打开看门狗设备
 */
static JSValue watchdogOpen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int type;
    unsigned long arg;
    JS_ToInt32(ctx, &type, argv[0]);
    JS_ToInt64(ctx, &arg, argv[1]);
    wdt = vbar_watchdog_open(type, arg);
    return JS_NewInt32(ctx, 1);
}

// /**
//  * @brief 判断是否是上电复位
//  */
// static JSValue watchdogIsPoweron(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
// {
//     wdt = JS_VALUE_GET_PTR(argv[0]);
//     bool isPoweron = vbar_watchdog_is_poweron(wdt);
//     return JS_NewBool(ctx, isPoweron);
// }

// /**
//  * @brief 开启看门狗总定时器
//  */
// static JSValue watchdogStart(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
// {
//     int timeout;
//     wdt = JS_VALUE_GET_PTR(argv[0]);
//     JS_Toint32(ctx, &timeout, argv[1]);
//     vbar_watchdog_start(wdt, timeout);
//     return JS_UNDEFINED;
// }

// /**
//  * @brief 关闭看门狗总定时器
//  */
// static JSValue watchdogStop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
// {
//     wdt = JS_VALUE_GET_PTR(argv[0]);
//     vbar_watchdog_stop(wdt);
//     return JS_UNDEFINED;
// }

// /**
//  * @brief 控制指定通道开关
//  */
// static JSValue watchdogEnable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
// {
//     unsigned int chan;
//     wdt = JS_VALUE_GET_PTR(argv[0]);
//     JS_Toint32(ctx, &chan, argv[1]);
//     int toset = JS_ToBool(ctx, argv[2]);

//     int res = vbar_watchdog_enable(wdt, chan, toset);
//     return JS_NewBool(ctx, res);
// }

// /**
//  * @brief 喂狗指定通道
//  */
// static JSValue watchdogRestart(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
// {
//     unsigned int chan;
//     wdt = JS_VALUE_GET_PTR(argv[0]);
//     JS_Toint32(ctx, &chan, argv[1]);
//     int res = vbar_watchdog_restart(wdt, chan);
//     return JS_NewBool(ctx, res);
// }

// /**
//  * @brief 关闭看门狗设备
//  */
// static JSValue watchdogClose(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
// {
//     wdt = JS_VALUE_GET_PTR(argv[0]);
//     vbar_watchdog_close(wdt);
//     return JS_UNDEFINED;
// }


/* 构造方法 */
static JSValue watchdogContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, watchdogClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry watchdog_class_funcs[] = {
    JS_CFUNC_DEF("watchdogOpen", 2, watchdogOpen),
};


/* 当前类数据结构 */
JSFullClassDef watchdogClass = {
    .def = {
        .class_name = "watchdogClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { watchdogContructor, .args_count = 1 },
    .funcs_len = sizeof(watchdog_class_funcs),
    .funcs = watchdog_class_funcs
};


/* 给对象绑定属性 */
static int watchdog_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &watchdogClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建watchdogClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前watchdogClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_WATCHDOG_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, watchdog_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, watchdogClass.def.class_name);
    return m;
}