/**
 * 测试c结构体转换为js对象
 * gcc -fPIC -o test_obj.o -c test_obj.c -I../../include/quickjs/master
 * gcc -shared -o test_obj.so test_obj.o
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <quickjs.h>

#define JS_INIT_MODULE js_init_module
#define countof(x) (sizeof(x) / sizeof((x)[0]))

struct mode
{
    int modeNum;
    char *modeName;
};


typedef struct {
    int id;
    char name[100];
    double balance;
    struct mode *mymode1;
    struct mode mymode2;
} Account;


static JSValue js_get_obj(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv)
{
    Account account = { 123, "Alice", 1000.0 };

    JSValue obj = JS_NewObject(ctx);

    JS_DefinePropertyValueStr(ctx, obj, "id", JS_NewInt32(ctx, account.id), JS_PROP_C_W_E);
    JS_DefinePropertyValueStr(ctx, obj, "name", JS_NewString(ctx, account.name), JS_PROP_C_W_E);
    JS_DefinePropertyValueStr(ctx, obj, "balance", JS_NewFloat64(ctx, account.balance), JS_PROP_C_W_E);

    JSValue modeObj1 = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, modeObj1, "modeNum", JS_NewInt32(ctx, 88));
    JS_SetPropertyStr(ctx, modeObj1, "modeName", JS_NewString(ctx, "xiaoli"));
    JS_SetPropertyStr(ctx, obj, "mymode1", modeObj1);

    JSValue modeObj2 = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, modeObj2, "modeNum", JS_NewInt32(ctx, 99));
    JS_SetPropertyStr(ctx, modeObj2, "modeName", JS_NewString(ctx, "xiaowang"));
    JS_SetPropertyStr(ctx, obj, "mymode2", modeObj2);

    // use the JSValue object...
    return obj;
}

/* 定义API的函数入口名称及列表 */
static const JSCFunctionListEntry js_test_funcs[] = {
    /* JS_CFUNC_DEF(函数入口名称，入参个数，QuickJS C 函数) */
    JS_CFUNC_DEF("getObj", 0, js_get_obj),
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