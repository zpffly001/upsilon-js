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

#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"


/* ---------------------MQTTClient 改造--------------------- */

volatile int toStop = 0;

MQTTClient client;
MQTTClient_deliveryToken last_token;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;

struct pubsub_opts opts =
{
	0, 0, 1, 0, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT, NULL, "path/to/my/topic", 0, 0, NULL, NULL, "150.158.83.55", "1883", NULL, 10, /* MQTT options */
	NULL, NULL, 0, 0, /* will options */
	0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
	0, {NULL, NULL}, /* MQTT V5 options */
	NULL, NULL, /* HTTP and HTTPS proxies */
};


int myconnect(MQTTClient client)
{
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
	MQTTClient_willOptions will_opts = MQTTClient_willOptions_initializer;
	int rc = 0;

	if (opts.verbose)
		printf("Connecting\n");

	if (opts.MQTTVersion == MQTTVERSION_5)
	{
		MQTTClient_connectOptions conn_opts5 = MQTTClient_connectOptions_initializer5;
		conn_opts = conn_opts5;
	}

	conn_opts.keepAliveInterval = opts.keepalive;
	conn_opts.username = opts.username;
	conn_opts.password = opts.password;
	conn_opts.MQTTVersion = opts.MQTTVersion;

	if (opts.will_topic) 	/* will options */
	{
		will_opts.message = opts.will_payload;
		will_opts.topicName = opts.will_topic;
		will_opts.qos = opts.will_qos;
		will_opts.retained = opts.will_retain;
		conn_opts.will = &will_opts;
	}

	if (opts.connection && (strncmp(opts.connection, "ssl://", 6) == 0 ||
			strncmp(opts.connection, "wss://", 6) == 0))
	{
		if (opts.insecure)
			ssl_opts.verify = 0;
		else
			ssl_opts.verify = 1;
		ssl_opts.CApath = opts.capath;
		ssl_opts.keyStore = opts.cert;
		ssl_opts.trustStore = opts.cafile;
		ssl_opts.privateKey = opts.key;
		ssl_opts.privateKeyPassword = opts.keypass;
		ssl_opts.enabledCipherSuites = opts.ciphers;
		conn_opts.ssl = &ssl_opts;
	}

	if (opts.MQTTVersion == MQTTVERSION_5)
	{
		MQTTProperties props = MQTTProperties_initializer;
		MQTTProperties willProps = MQTTProperties_initializer;
		MQTTResponse response = MQTTResponse_initializer;

		conn_opts.cleanstart = 1;
		response = MQTTClient_connect5(client, &conn_opts, &props, &willProps);
		rc = response.reasonCode;
		MQTTResponse_free(response);
	}
	else
	{
		conn_opts.cleansession = 1;
		rc = MQTTClient_connect(client, &conn_opts);
	}

	if (opts.verbose && rc == MQTTCLIENT_SUCCESS)
		fprintf(stderr, "Connected\n");
	else if (rc != MQTTCLIENT_SUCCESS && !opts.quiet)
		fprintf(stderr, "Connect failed return code: %s\n", MQTTClient_strerror(rc));

	return rc;
}

/* ---------------------MQTTClient 改造--------------------- */


enum _mqtt_parser_event {
    MQTT_PARSER_EVENT_MESSAGE_BEGIN = 0,
    MQTT_PARSER_EVENT_MESSAGE,
    MQTT_PARSER_EVENT_MAX,
};

typedef struct _mqtt_parser {
    JSContext* ctx;
    JSValue events[MQTT_PARSER_EVENT_MAX];
    DynBuf buffer;
    size_t bufferOffset;
    size_t valueCount;
} TJSMqttParser;

static JSClassID mqtt_class_id;


/**
 * @brief 消息订阅
 *
 * @param ctx
 * @param this_val
 * @param argc
 * @param argv
 * @return JSValue
 */
static JSValue mqttSubscribe(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int rc = 1;
    /* 订阅 */
	rc = MQTTClient_subscribe(client, opts.topic, opts.qos);
	printf("MQTTClient_subscribe: %d, topic:  %s\n", rc, opts.topic);

	if (rc != MQTTCLIENT_SUCCESS && rc != opts.qos)
	{
		if (!opts.quiet)
			fprintf(stderr, "Error %d subscribing to topic %s\n", rc, opts.topic);
	}
}


/**
 * @brief 消息发布
 *
 * @param ctx
 * @param this_val
 * @param argc
 * @param argv
 * @param client
 * @param topic
 * @return JSValue
 */
static JSValue mqttPublish(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue res;
    char* topic = NULL;
    char* buffer = NULL;
    int rc = 1;
    int buf_len = 0;

    topic = JS_ToCString(ctx, argv[0]);
    buffer = JS_ToCString(ctx, argv[1]);
    JS_ToInt32(ctx, &buf_len, argv[2]);
    printf("topic: %s\n", topic);
    printf("buffer: %s\n", buffer);
    printf("topic: %d\n", buf_len);


    rc = MQTTClient_publish(client, opts.topic, buf_len, buffer, opts.qos, opts.retained, &last_token);
    return JS_UNDEFINED;
}


/**
 * @brief 消息体读取
 *
 * @param ctx
 * @param this_val
 * @param argc
 * @param argv
 * @param client
 * @param topic
 * @return JSValue
 */
static JSValue mqttPacketRead(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int rc = 1;
    char* topicName = NULL;
    int topicLen;
    MQTTClient_message* message = NULL;
    JSValue msg;
    int received = 0;

    rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);
    if (rc == MQTTCLIENT_DISCONNECTED)
        myconnect(client);
    else if (message)
    {
        size_t delimlen = 0;

        if (opts.verbose)
            printf("%s\t", topicName);
        if (opts.delimiter)
            delimlen = strlen(opts.delimiter);
        printf("%.*s%s", message->payloadlen, (char*)message->payload, opts.delimiter);
        msg = JS_NewString(ctx, (char*)message->payload);
        received = 1;
        if (message->struct_version == 1 && opts.verbose)
            logProperties(&message->properties);
        fflush(stdout);
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
    }

    /* 返回去的数据有三个：toopic，message，messageLength */
    if (received)
    {
        return msg;
    }else
    {
        return JS_UNDEFINED;
    }
}


/**
 * @brief Mqtt连接关闭
 *
 * @param ctx
 * @param this_val
 * @param argc
 * @param argv
 * @return JSValue
 */
static JSValue mqttdisconnect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    MQTTClient_disconnect(client, 0);

	MQTTClient_destroy(&client);
}


/**
 * @brief Create a Mqtt Client object 创建一个MQTT客户端
 *
 * @param ctx
 * @param this_val
 * @param argc
 * @param argv
 * @return JSValue
 */
static JSValue createMqttClient(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    /* 创建mqttClient连接对象。对象属于mqttClass类 */
    JSValue mqttClient = JS_NewObjectClass(ctx, mqttClass.id);

    int rc = 0;
	char* url;
	const char* version = NULL;

	const char* program_name = "paho_cs_sub";
	MQTTClient_nameValue* infos = MQTTClient_getVersionInfo();

    char *argvv[]={ "ls", "path/to/my/topic"};
	getopts(argc, argvv, &opts);

	if (strchr(opts.topic, '#') || strchr(opts.topic, '+'))
		opts.verbose = 1;

	if (opts.connection)
		url = opts.connection;
	else
	{
		url = malloc(100);
		sprintf(url, "%s:%s", opts.host, opts.port);
	}
	if (opts.verbose)
		printf("URL is %s\n", url);

	if (opts.MQTTVersion >= MQTTVERSION_5)
		createOpts.MQTTVersion = MQTTVERSION_5;
	rc = MQTTClient_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
			NULL, &createOpts);
	if (rc != MQTTCLIENT_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to create client, return code: %s\n", MQTTClient_strerror(rc));
		exit(EXIT_FAILURE);
	}

	/* 连接 */
	if (myconnect(client) != MQTTCLIENT_SUCCESS)
		printf("connect failed\n");


    /* 把MQTTClient进行包装(就是把connect作为一个属性放入，当然mqttClient仍然有已经定义过的：sub、pub等功能)，包装为JS可识别的对象 */
    JS_SetOpaque(mqttClient, &client);
    return mqttClient;
}


/* 构造方法 */
static JSValue mqttContructor(
    JSContext *ctx, JSValueConst this_val,
    int argc, JSValueConst *argv)
{
    JSValue obj = JS_NewObjectClass(ctx, mqttClass.id);
    return obj;
}


/* 类方法列表填充 */
static const JSCFunctionListEntry mqtt_class_funcs[] = {
    JS_CFUNC_DEF("createMqttClient", 0, createMqttClient),
    JS_CFUNC_DEF("mqttSubscribe", 1, mqttSubscribe),
    JS_CFUNC_DEF("mqttPacketRead", 0, mqttPacketRead),
    JS_CFUNC_DEF("mqttPublish", 3, mqttPublish),
};


/* 当前类数据结构 */
JSFullClassDef mqttClass = {
    .def = {
        .class_name = "mqttClass",
        .finalizer = { NULL, 0 },
        .gc_mark = { NULL, 0 },
    },
    .constructor = { mqttContructor, .args_count = 1 },
    .funcs_len = sizeof(mqtt_class_funcs),
    .funcs = mqtt_class_funcs
};


/* 给对象绑定属性 */
static int mqtt_init(JSContext* ctx, JSModuleDef* module)
{
    /* variable */
    JSValue proto, obj;
    JSFullClassDef *fullDef;
    fullDef = &mqttClass;

    /* 准备类名 */
    const char *className = fullDef->def.class_name;
    /* 准备构造函数 */
    JSContructorDef *constructor = &fullDef->constructor;
    /* 初始化类ID */
    JS_NewClassID(&fullDef->id);
    /* 创建mqttClass类 */
    JS_NewClass(JS_GetRuntime(ctx), fullDef->id, &fullDef->def);
    /* 创建类的原型对象 */
    proto = JS_NewObject(ctx);
    /* 给对象设置方法 */
    JS_SetPropertyFunctionList(ctx, proto, fullDef->funcs, fullDef->funcs_len / sizeof(fullDef->funcs[0]));
    /* 把原型类和当前mqttClass类进行绑定 */
    JS_SetClassProto(ctx, fullDef->id, proto);
    /* 准备类名 */
    obj = JS_NewCFunction2(ctx, constructor->fn, className, constructor->args_count, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, module, className, obj);
    return 0;
}


/* 模块导出 */
JSModuleDef *JS_INIT_MQTT_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, mqtt_init);
    if (!m) return NULL;
    JS_AddModuleExport(ctx, m, mqttClass.def.class_name);
    return m;
}

