#ifndef QUICKJS_MQTT_H
#define QUICKJS_MQTT_H

#include "quickjs.h"


#define JS_INIT_MQTT_MODULE js_init_module

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

#endif /* QUICKJS_MQTT_H */