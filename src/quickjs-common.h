#ifndef QUICKJS_COMMON_H
#define QUICKJS_COMMON_H

#include "quickjs.h"


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


#endif