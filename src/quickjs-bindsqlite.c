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
#include "sqlite3.h"
#include "quickjs-bindsqlite.h"


/* 数据库操作句柄 */
sqlite3 *ppDb = NULL;


/**
 * 打开数据库链接
*/
static JSValue sqlite3Open(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int ret;
    /* 打开指定路径的数据库，有则打开，无则创建 */
    char* dbPath = JS_ToCString(ctx, argv[0]);

    ret = sqlite3_open(dbPath, &ppDb);
	if(ret != SQLITE_OK){
		printf("open config.db failed %s\n",sqlite3_errmsg(ppDb));
		return JS_NewInt32(ctx, 0);
	}

	printf("open %s ok\n", dbPath);
    return JS_NewInt32(ctx, 1);
}


/**
 * 关闭数据库链接
*/
static JSValue sqlite3Close(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    sqlite3_close(ppDb);
    return JS_UNDEFINED;
}


/**
 * SQL执行
*/
static JSValue sqlite3SqlExec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int ret;
    char* sql = JS_ToCString(ctx, argv[0]);
    char *errMsg = NULL;
	ret = sqlite3_exec(ppDb,sql, NULL ,NULL, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_exec err %s\n",errMsg);
		sqlite3_free(errMsg);
	}

	printf("sql: %s exec ok\n", sql);
    sqlite3_free(errMsg);
    return JS_UNDEFINED;
}


/**
 * 数据查询
*/
static JSValue sqlite3Select(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int nRow, nCol, ret;
	char **pazResult = NULL;
    char *errMsg = NULL;
    char* sql = JS_ToCString(ctx, argv[0]);
	ret = sqlite3_get_table(ppDb, sql, &pazResult, &nRow, &nCol, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_get_table err %s\n",errMsg);
		sqlite3_free(errMsg);
		return JS_UNDEFINED;
	}

	printf("nRow = %d , nCol = %d\n", nRow, nCol);
	for(int i = 0; i < nCol*(nRow+1); i++){
		printf("pazResult[%d] = %s\n",i,pazResult[i]);
	}

	//正确且安全的释放内存
	sqlite3_free_table(pazResult);
    return JS_NewString(ctx, "halalal");
}


/* 类方法列表填充 */
static const JSCFunctionListEntry sqlite_class_funcs[] = {
    JS_CFUNC_DEF("sqlite3Open", 1, sqlite3Open),
    JS_CFUNC_DEF("sqlite3Close", 0, sqlite3Close),
    JS_CFUNC_DEF("sqlite3SqlExec", 1, sqlite3SqlExec),
    JS_CFUNC_DEF("sqlite3Select", 1, sqlite3Select),
};


/* 构造方法 */
static JSValue sqliteContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, sqliteClass.id);
    return obj;
}


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
JSModuleDef *JS_INIT_SQLITE_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, sqlite_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, sqliteClass.def.class_name);
    return m;
}