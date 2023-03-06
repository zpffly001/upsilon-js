#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>


#include "quickjs.h"
#include "quickjs-common.h"
#include "quickjs-sysinfo.h"
#include "sysinfo.h"




/**
 * @brief 打开信道
 */
static JSValue channelOpen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    return JS_UNDEFINED;
}




/* 构造方法 */
static JSValue sysinfoContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, sysinfoClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry sysinfo_class_funcs[] = {
    JS_CFUNC_DEF("channelOpen", 2, channelOpen),
};


/* 当前类数据结构 */
JSFullClassDef sysinfoClass = {
    .def = {
        .class_name = "sysinfoClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { sysinfoContructor, .args_count = 1 },
    .funcs_len = sizeof(sysinfo_class_funcs),
    .funcs = sysinfo_class_funcs
};


/* 给对象绑定属性 */
static int sysinfo_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &sysinfoClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建sysinfoClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前sysinfoClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_SYSINFO_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, sysinfo_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, sysinfoClass.def.class_name);
    return m;
}