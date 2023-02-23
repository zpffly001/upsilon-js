#include <string.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <signal.h>
#include <sys/time.h>

#include "quickjs.h"
#include "cutils.h"
#include "list.h"
#include "quickjs-bindmqtt.h"



/* 打开数据库链接 */
/* 关闭数据库链接 */

/* 执行SQL */

/*  */





/* 构造方法 */
static JSValue sqliteContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, sqliteClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry sqlite_class_funcs[] = {
    // JS_CFUNC_DEF("createMqttClient", 0, createMqttClient),
    // JS_CFUNC_DEF("mqttSubscribe", 1, mqttSubscribe),
    // JS_CFUNC_DEF("mqttPacketRead", 0, mqttPacketRead),
    // JS_CFUNC_DEF("mqttPublish", 3, mqttPublish),
};


/* 当前类数据结构 */
JSFullClassDef sqliteClass = {
    .def = {
        .class_name = "sqliteClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { sqliteContructor, .args_count = 1 },
    .funcs_len = sizeof(sqlite_class_funcs),
    .funcs = sqlite_class_funcs
};


/* 给对象绑定属性 */
static int sqlite_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &sqliteClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建sqliteClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前sqliteClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_MQTT_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, sqlite_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, sqliteClass.def.class_name);
    return m;
}