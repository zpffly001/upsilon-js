#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "quickjs.h"
#include "quickjs-common.h"

// gcc -c -fPIC -o testFunc.o testFunc.c -I../../src -I../../include/quickjs/master
// gcc -shared -o testFunc.so testFunc.o

JSFullClassDef funcClass;
typedef int (*func) (int a, int b);

static JSValue funcCall(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    printf("funcCall\n");
    JSValue funObj = argv[0];
    if (!JS_IsFunction(ctx, funObj))
    {
        printf("not function\n");
    }else {
        printf("function\n");
    }

    JSValue result = JS_Call(ctx, funObj, JS_UNDEFINED, 0, NULL);
    int res;
    JS_ToInt32(ctx, &res, result);
    printf("rerere: %d\n", res);
    return JS_UNDEFINED;
}
/* 构造方法 */
static JSValue funcContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, funcClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry func_class_funcs[] = {
    JS_CFUNC_DEF("funcCall", 1, funcCall),
};


/* 当前类数据结构 */
JSFullClassDef funcClass = {
    .def = {
        .class_name = "funcClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { funcContructor, .args_count = 1 },
    .funcs_len = sizeof(func_class_funcs),
    .funcs = func_class_funcs
};


/* 给对象绑定属性 */
static int func_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &funcClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建funcClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前funcClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *js_init_module(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, func_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, funcClass.def.class_name);
    return m;
}