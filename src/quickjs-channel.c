#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>


#include "quickjs.h"
#include "quickjs-common.h"
#include "quickjs-channel.h"
#include "channel.h"

struct vbar_channel *channel;

/**
 * @brief 打开信道
 */
static JSValue channelOpen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int type;
    unsigned long arg;
    JS_ToInt32(ctx, &type, argv[0]);
    JS_ToInt64(ctx, &arg, argv[1]);
    channel = vbar_channel_open(type, arg);
    return JS_UNDEFINED;
}

/**
 * @brief 信道数据发送
 */
static JSValue channelSend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const unsigned char *buffer = JS_ToCString(ctx, argv[0]);
    int length;
    JS_ToInt32(ctx, &length, argv[1]);
    printf("length: %d\n", length);
    int res = vbar_channel_send(channel, buffer, 11);

    return JS_NewInt32(ctx, 1);
}

/**
 * @brief 接收数据
 */
static JSValue channelRecv(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned char *buffer;
    size_t size;
    int milliseconds;
    buffer = JS_GetArrayBuffer(ctx, &size, argv[0]);
    JS_ToInt32(ctx, &milliseconds, argv[1]);
    int res = vbar_channel_recv(channel, buffer, size, milliseconds);

    for (size_t i = 0; i < size; i++)
    {
        printf("recv[%d]: %c\n", i, buffer[i]);
    }

    return JS_NewInt32(ctx, res);
}

/**
 * @brief 调用信道特殊IO接口
 */
static JSValue channelIoctl(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int request;
    unsigned long arg;
    JS_ToInt32(ctx, &request, argv[0]);
    JS_ToInt64(ctx, &arg, argv[1]);
    int res = vbar_channel_ioctl(channel, request, arg);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 关闭信道
 */
static JSValue channelClose(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    vbar_channel_close(channel);
    return JS_UNDEFINED;
}

/**
 * @brief 刷新信道
 */
static JSValue channelFlush(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int queue_selector;
    JS_ToInt32(ctx, &queue_selector, argv[0]);
    int res = vbar_channel_flush(channel, queue_selector);
    return JS_NewInt32(ctx, res);
}


/* 构造方法 */
static JSValue channelContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, channelClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry channel_class_funcs[] = {
    JS_CFUNC_DEF("channelOpen", 2, channelOpen),
    JS_CFUNC_DEF("channelSend", 3, channelSend),
    JS_CFUNC_DEF("channelRecv", 4, channelRecv),
    JS_CFUNC_DEF("channelIoctl", 3, channelIoctl),
    JS_CFUNC_DEF("channelClose", 1, channelClose),
    JS_CFUNC_DEF("channelFlush", 2, channelFlush),
};


/* 当前类数据结构 */
JSFullClassDef channelClass = {
    .def = {
        .class_name = "channelClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { channelContructor, .args_count = 1 },
    .funcs_len = sizeof(channel_class_funcs),
    .funcs = channel_class_funcs
};


/* 给对象绑定属性 */
static int channel_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &channelClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建channelClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前channelClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_CHANNEL_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, channel_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, channelClass.def.class_name);
    return m;
}