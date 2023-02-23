#ifndef QUICKJS_BINDMQTT_H
#define QUICKJS_BINDMQTT_H

#include "../../../../quickjs.h"


#ifdef JS_SHARED_LIBRARY
#define JS_INIT_MQTT_MODULE js_init_module
#else
// #define JS_INIT_MQTT_MODULE js_init_module_mqtt
#define JS_INIT_MQTT_MODULE js_init_module
#endif

typedef struct JSContructorDef_s {
    JSCFunction *fn;
    int args_count;
} JSContructorDef;

typedef struct JSFullClassDef_s
{
    JSClassID id;
    JSClassID baseClass;
    JSClassDef def;
    JSContructorDef constructor;
    size_t funcs_len;
    JSCFunctionListEntry *funcs;
} JSFullClassDef;



extern JSFullClassDef mqttClass;

#endif /* QUICKJS_BINDMQTT_H */