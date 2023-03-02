/**
 * 测试enum和js数据的转换
 * gcc -fPIC -o testEnum.o -c testEnum.c -I../../include/quickjs/master
 * gcc -shared -o testEnum.so testEnum.o
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quickjs.h"

#define JS_INIT_MODULE js_init_module
#define countof(x) (sizeof(x) / sizeof((x)[0]))


enum net_status {
    VBAR_NET_STATUS_NONE             = 0,   /* 未初始态 */
    VBAR_NET_STATUS_DOWN             = 1,   /* 网卡处于关闭状态 */
    VBAR_NET_STATUS_UP               = 2,   /* 网卡处于打开状态 */
    VBAR_NET_STATUS_CONNECTING_ROUTE = 3,   /* 网线已插入或者wifi已连接ssid 但未分配ip */
    VBAR_NET_STATUS_CONNECTED_ROUTE  = 4,   /* 已成功分配ip */
    VBAR_NET_STATUS_CONNECTED_SERVER = 5    /* 已连接指定服务或者通过测试可以连接到广域网 */
};


static JSValue js_enum_convert(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv)
{
    enum net_status status;

    JS_ToInt32(ctx, &status, argv[0]);
    printf("js_enum_convert status: %d\n", status);

    status = VBAR_NET_STATUS_CONNECTED_SERVER;
    return JS_NewInt32(ctx, status);
}

/* 定义API的函数入口名称及列表 */
static const JSCFunctionListEntry js_test_funcs[] = {
    /* JS_CFUNC_DEF(函数入口名称，入参个数，QuickJS C 函数) */
    JS_CFUNC_DEF("enumConvert", 0, js_enum_convert),
};

/* 定义初始化回调方法（由系统调用，入参格式固定），将函数入口列表 在模块中暴露 */
static int js_test_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_test_funcs, countof(js_test_funcs));
}

/* 定义初始化模块方法，由系统自动调用，且函数名称不可更改 */
JSModuleDef *js_init_module(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_test_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_test_funcs, countof(js_test_funcs));
    return m;
}