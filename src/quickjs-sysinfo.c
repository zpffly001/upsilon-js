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
 * @brief 获取系统启动的运行时间
 */
static JSValue sysinfoGetUptime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    long uptime = vbar_sysinfo_get_uptime();
    return JS_NewInt64(ctx, uptime);
}

/**
 * @brief 获取系统的总内存
 */
static JSValue sysinfoGetTotalmem(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    long totalmem = vbar_sysinfo_get_totalmem();
    return JS_NewInt64(ctx, totalmem);
}

/**
 * @brief 获取系统剩余内存
 */
static JSValue sysinfoGetFreemem(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    long freemem = vbar_sysinfo_get_freemem();
    return JS_NewInt64(ctx, freemem);
}

/**
 * @brief 获取系统可用磁盘总量
 */
static JSValue sysinfoGetTotaldisk(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    char *path = JS_ToCString(ctx, argv[0]);
    long totaldisk = vbar_sysinfo_get_totaldisk(path);
    return JS_NewInt64(ctx, totaldisk);
}

/**
 * @brief 获取系统磁盘剩余可用量
 */
static JSValue sysinfoGetFreedisk(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    char *path = JS_ToCString(ctx, argv[0]);
    long freedisk = vbar_sysinfo_get_freedisk(path);
    return JS_NewInt64(ctx, freedisk);
}

/**
 * @brief 获取设备uuid（字符串）
 */
static JSValue sysinfoGetUuid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    char *uuid = JS_ToCString(ctx, argv[0]);
    uint32_t len;
    JS_ToInt32(ctx, &len, argv[1]);
    int res = vbar_sysinfo_get_uuid(uuid, len);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取通过uuid计算的mac地址
 */
static JSValue sysinfoGetUuid2mac(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    char *mac = JS_ToCString(ctx, argv[0]);
    uint32_t len;
    JS_ToInt32(ctx, &len, argv[1]);
    int res = vbar_sysinfo_get_uuid2mac(mac, len);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取cpu占用率
 */
static JSValue sysinfoGetFreecpu(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int freecpu = vbar_sysinfo_get_freecpu();
    return JS_NewInt32(ctx, freecpu);
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
    JS_CFUNC_DEF("sysinfoGetUptime", 0, sysinfoGetUptime),
    JS_CFUNC_DEF("sysinfoGetTotalmem", 0, sysinfoGetTotalmem),
    JS_CFUNC_DEF("sysinfoGetFreemem", 0, sysinfoGetFreemem),
    JS_CFUNC_DEF("sysinfoGetTotaldisk", 1, sysinfoGetTotaldisk),
    JS_CFUNC_DEF("sysinfoGetFreedisk", 1, sysinfoGetFreedisk),
    JS_CFUNC_DEF("sysinfoGetUuid", 2, sysinfoGetUuid),
    JS_CFUNC_DEF("sysinfoGetUuid2mac", 2, sysinfoGetUuid2mac),
    JS_CFUNC_DEF("vbar_sysinfo_get_freecpu", 0, vbar_sysinfo_get_freecpu),
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