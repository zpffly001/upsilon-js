#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>

#include "net.h"
#include "quickjs.h"
#include "quickjs-common.h"
#include "quickjs-net.h"

JSValue netStatusFunction;
JSContext *currentCtx;

/**
 * @brief 注册网络状态回调函数
 */
void netStatusCallback(uint8_t type, enum net_status status, void *pdata)
{

    JSValue result = JS_Call(currentCtx, netStatusFunction, JS_UNDEFINED, 0, NULL);

}


/**
 * @brief 网络模块初始化
 */
static JSValue netInit(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    vbar_net_init();
    return JS_UNDEFINED;
}

/**
 * @brief 清理网络模块资源
 */
static JSValue netExit(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    vbar_net_exit();
    return JS_UNDEFINED;
}

/**
 * @brief 使能网卡，并添加到网络管理模块
 */
static JSValue netCardEnable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int type;
    bool on;
    JS_ToInt32(ctx, &type, argv[0]);
    on = JS_ToBool(ctx, argv[1]);
    int res = vbar_net_card_enable(type, on);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 注册网络状态回调函数
 */
static JSValue netStatusCallbackRegister(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    netStatusFunction = argv[0];
    currentCtx = ctx;
    vbar_net_status_cb func = netStatusCallback;
    void *pdata = "123"; // int string obj
    int res = vbar_net_status_callback_register(func, pdata);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 设置指定网卡的模式及对应参数网络参数
 */
static JSValue netSetModeByCard(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    uint8_t type;
    enum net_mode mode;
    struct net_static_param *param;
    JS_ToInt32(ctx, &type, argv[0]);
    JS_ToInt32(ctx, &mode, argv[0]);
    /* JS对象转化为C结构体 */
    char *ip = JS_ToCString(ctx, argv[1]);
    for (size_t i = 0; i < 10; i++)
    {
        param->ip[i] = ip[i];
        printf("%c", param->ip[i]);
    }

    /* todo 其余的gateway netmask dns0 dns1 也是一样 */


    int res = vbar_net_set_mode_by_card(type, mode, param);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取指定网卡的模式及对应参数网络参数
 */
static JSValue netGetModeByCard(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    uint8_t type;
    struct net_static_param *param;

    /* 获取网卡模式以及参数 */
    int res = vbar_net_get_mode_by_card(type, param);

    /* 把获取到的模式以及参数转化为js类型 */
    JSValue netModeInfo = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, netModeInfo, "type", JS_NewInt32(ctx, type));

    JSValue netParam = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, netModeInfo, "ip", JS_NewStringLen(ctx, param->ip, 20));
    JS_SetPropertyStr(ctx, netModeInfo, "gateway", JS_NewStringLen(ctx, param->gateway, 20));
    JS_SetPropertyStr(ctx, netModeInfo, "netmask", JS_NewStringLen(ctx, param->netmask, 20));
    JS_SetPropertyStr(ctx, netModeInfo, "dns0", JS_NewStringLen(ctx, param->dns0, 20));
    JS_SetPropertyStr(ctx, netModeInfo, "dns1", JS_NewStringLen(ctx, param->dns1, 20));

    JS_SetPropertyStr(ctx, netModeInfo, "param", netParam);

    return JS_NewInt32(ctx, res);
}

/**
 * @brief 设置主网卡，应用程序网络状态由次网卡决定
 */
static JSValue netSetMasterCard(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    uint8_t type;
    int res = vbar_net_set_master_card(type);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取主网卡
 */
static JSValue netGetMasterCard(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int res = vbar_net_get_master_card();
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取网络状态
 */
static JSValue netGetStatus(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    enum net_status status = vbar_net_get_status();
    // 此处应该返回enum，可以和js中的enum做一个映射
    return JS_NewInt32(ctx, status);
}

/**
 * @brief 设置网络状态
 */
static JSValue netSetStatus(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    enum net_status status;
    JS_ToInt32(ctx, &status, argv[0]);
    vbar_net_set_status(status);
    return JS_UNDEFINED;
}

/**
 * @brief 获取wifi热点列表
 */
static JSValue netGetWifiSsidList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct vbar_ssid_scan_list *list;
    uint32_t timeout_ms;
    uint32_t interval_ms;
    int res = vbar_net_get_wifi_ssid_list(list, timeout_ms, interval_ms);
    /* TODO 待优化 */
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 连接到wifi热点
 */
static JSValue netConnectWifiSsid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char *ssid = JS_ToCString(ctx, argv[0]);
    const char *psk = JS_ToCString(ctx, argv[1]);
    const char *params = JS_ToCString(ctx, argv[2]);
    int res = vbar_net_connect_wifi_ssid(ssid, psk, params);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取已保存的热点列表
 */
static JSValue netGetWifiSavedList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct vbar_wifi_save_list *list;
    int res = vbar_net_get_wifi_saved_list(list);
    /* TODO 待优化 */
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 获取当前热点的信息
 */
static JSValue netGetCurrentWifiInfo(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    struct vbar_wpa_wifi_info *info;
    uint32_t timeout_ms;
    int res = vbar_net_get_current_wifi_info(info, timeout_ms);
    /* TODO 待优化 */
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 连接到已保存的wifi热点
 */
static JSValue netNetConnectSavedWifi(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    uint16_t id;
    JS_ToUint32(ctx, &id, argv[0]);
    int res = vbar_net_connect_saved_wifi(id);
    return JS_NewInt32(ctx, res);
}

/**
 * @brief 断开当前连接的wifi热点
 */
static JSValue netDisconnetWifi(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    vbar_net_disconnet_wifi();
    return JS_UNDEFINED;
}

/* 构造方法 */
static JSValue netContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, netClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry net_class_funcs[] = {
    JS_CFUNC_DEF("netInit", 0, netInit),
    JS_CFUNC_DEF("netExit", 0, netExit),
    JS_CFUNC_DEF("netCardEnable", 2, netCardEnable),
    JS_CFUNC_DEF("netStatusCallbackRegister", 2, netStatusCallbackRegister),
    JS_CFUNC_DEF("netSetModeByCard", 3, netSetModeByCard),
    JS_CFUNC_DEF("netGetModeByCard", 2, netGetModeByCard),
    JS_CFUNC_DEF("netSetMasterCard", 1, netSetMasterCard),
    JS_CFUNC_DEF("netGetMasterCard", 0, netGetMasterCard),
    JS_CFUNC_DEF("netGetStatus", 0, netGetStatus),
    JS_CFUNC_DEF("netSetStatus", 1, netSetStatus),
    JS_CFUNC_DEF("netGetWifiSsidList", 3, netGetWifiSsidList),
    JS_CFUNC_DEF("netConnectWifiSsid", 3, netConnectWifiSsid),
    JS_CFUNC_DEF("netGetWifiSavedList", 1, netGetWifiSavedList),
    JS_CFUNC_DEF("netGetCurrentWifiInfo", 2, netGetCurrentWifiInfo),
    JS_CFUNC_DEF("netNetConnectSavedWifi", 1, netNetConnectSavedWifi),
    JS_CFUNC_DEF("netDisconnetWifi", 1, netDisconnetWifi),
};


/* 当前类数据结构 */
JSFullClassDef netClass = {
    .def = {
        .class_name = "netClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { netContructor, .args_count = 1 },
    .funcs_len = sizeof(net_class_funcs),
    .funcs = net_class_funcs
};


/* 给对象绑定属性 */
static int net_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &netClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建netClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前netClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_NET_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, net_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, netClass.def.class_name);
    return m;
}