#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>


#include "quickjs.h"
#include "quickjs-common.h"
#include "quickjs-keyboard.h"
#include "keyboard.h"

JSValue events[100];
JSContext *current;

static JSValue eventGet(JSContext *ctx, JSValueConst this_val, int magic)
{
    return JS_DupValue(ctx, events[magic]);
}

static JSValue eventSet(JSContext *ctx, JSValueConst this_val, JSValueConst value, int magic)
{
    if (JS_IsFunction(ctx, value))
        events[magic] = JS_DupValue(ctx, value);
    else
        events[magic] = JS_UNDEFINED;
    return JS_UNDEFINED;
}

/**
 * @brief keyboard回调函数
 */
void keyPressCallback(struct input_event *key, void *pdata)
{
    JSValue argv[2];
    argv[0] = JS_NewString(current, "TODO");
    argv[1] = JS_NewString(current, "TODO");
    JS_Call(current, events[0], JS_UNDEFINED, 2, argv);
}

/**
 * @brief keyboard初始化
 */
static JSValue keyboardInit(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int res = vbar_keyboard_init();
    return JS_NewInt32(ctx, res);
}

/**
 * @brief keyboard退出
 */
static JSValue keyboardExit(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    vbar_keyboard_exit();
    return JS_UNDEFINED;
}

/**
 * @brief keyboard设置回调函数
 */
static JSValue keyboardCallbackRegister(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    key_press_cb func = keyPressCallback;
    void *pdata = JS_ToCString(ctx, argv[0]);
    current = ctx;
    int res = vbar_keyboard_callback_register(func, pdata);
    return JS_NewInt32(ctx, res);
}



/* 构造方法 */
static JSValue keyboardContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, keyboardClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry keyboard_class_funcs[] = {
    JS_CFUNC_DEF("keyboardInit", 0, keyboardInit),
    JS_CFUNC_DEF("keyboardExit", 0, keyboardExit),
    JS_CFUNC_DEF("keyboardCallbackRegister", 2, keyboardCallbackRegister),
    JS_CGETSET_MAGIC_DEF("callbackInit", NULL, eventSet, 0),
};


/* 当前类数据结构 */
JSFullClassDef keyboardClass = {
    .def = {
        .class_name = "keyboardClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { keyboardContructor, .args_count = 1 },
    .funcs_len = sizeof(keyboard_class_funcs),
    .funcs = keyboard_class_funcs
};


/* 给对象绑定属性 */
static int keyboard_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &keyboardClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建keyboardClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前keyboardClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_KEYBOARD_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, keyboard_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, keyboardClass.def.class_name);
    return m;
}