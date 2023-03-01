/**
 * 测试对象的引用传递 把js对象传递给c c修改后，js这边对象属性内容也随之修改
 * gcc -fPIC -o testObjRef.o -c testObjRef.c -I../../include/quickjs/master
 * gcc -shared -o testObjRef.so testObjRef.o
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quickjs.h"

#define JS_INIT_MODULE js_init_module
#define countof(x) (sizeof(x) / sizeof((x)[0]))



static JSValue js_obj_ref(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv)
{
    JSValue obj = argv[0];
    JS_SetPropertyStr(ctx, obj, "name", JS_NewString(ctx, "ikun"));
    printf("objRef\n");
    return JS_UNDEFINED;
}

/* 定义API的函数入口名称及列表 */
static const JSCFunctionListEntry js_test_funcs[] = {
    /* JS_CFUNC_DEF(函数入口名称，入参个数，QuickJS C 函数) */
    JS_CFUNC_DEF("objRef", 0, js_obj_ref),
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