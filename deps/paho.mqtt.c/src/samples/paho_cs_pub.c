/*******************************************************************************
 * Copyright (c) 2012, 2022 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *   https://www.eclipse.org/legal/epl-2.0/
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *    Ian Craggs - add full capability
 *******************************************************************************/

#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)
#define sleep Sleep
#else
#include <sys/time.h>
#endif

volatile int toStop = 0;


void cfinish(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}


struct pubsub_opts opts =
{
	1, 0, 0, 0, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT, NULL, "paho-cs-pub", 0, 0, NULL, NULL, "150.158.83.55", "1883", NULL, 10, /* MQTT options */
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
	conn_opts.httpProxy = opts.http_proxy;
	conn_opts.httpsProxy = opts.https_proxy;

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
		printf("Connected\n");
	else if (rc != MQTTCLIENT_SUCCESS && !opts.quiet)
		fprintf(stderr, "Connect failed return code: %s\n", MQTTClient_strerror(rc));

	return rc;
}


int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* m)
{
	/* not expecting any messages */
	return 1;
}


void connectionLost(void* context, char* reason)
{
	MQTTClient client = (MQTTClient)context;
	if (opts.verbose)
		printf("ConnectionLost, reconnecting\n");
	myconnect(client);
}


void trace_callback(enum MQTTCLIENT_TRACE_LEVELS level, char* message)
{
	fprintf(stderr, "Trace : %d, %s\n", level, message);
}


int main(int argc, char** argv)
{
	MQTTClient client;
	MQTTProperties pub_props = MQTTProperties_initializer;
	MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;
	MQTTClient_deliveryToken last_token;
	char* buffer = NULL;
	int rc = 0;
	char* url;
	const char* version = NULL;
#if !defined(_WIN32)
    struct sigaction sa;
#endif
	const char* program_name = "paho_cs_pub";
	MQTTClient_nameValue* infos = MQTTClient_getVersionInfo();


	char *argvv[]={ "ls", "path/to/my/topic"};
	getopts(argc, argv, &opts);

	if (opts.connection)
		url = opts.connection;
	else
	{
		url = malloc(100);
		sprintf(url, "%s:%s", opts.host, opts.port);
	}



	rc = MQTTClient_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
			NULL, &createOpts);
	if (rc != MQTTCLIENT_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to create client, return code: %s\n", MQTTClient_strerror(rc));
	}


	rc = MQTTClient_setCallbacks(client, client, connectionLost, messageArrived, NULL);
	if (rc != MQTTCLIENT_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTClient_strerror(rc));
	}

	if (myconnect(client) != MQTTCLIENT_SUCCESS)
		printf("client connect failed \n");

	while (!toStop)
	{
		int data_len = 0;
		int delim_len = 0;

		if (opts.stdin_lines)
		{
			buffer = malloc(opts.maxdatalen);

			delim_len = (int)strlen(opts.delimiter);
			do
			{
				int c = getchar();

				if (c < 0)
					printf("please input! \n");
				buffer[data_len++] = c;
				if (data_len > delim_len)
				{
					if (strncmp(opts.delimiter, &buffer[data_len - delim_len], delim_len) == 0)
						break;
				}
			} while (data_len < opts.maxdatalen);
		}
		else if (opts.message)
		{
			buffer = opts.message;
			data_len = (int)strlen(opts.message);
		}
		else if (opts.filename)
		{
			buffer = readfile(&data_len, &opts);
			if (buffer == NULL)
				printf("readfile failed \n");
		}
		if (opts.verbose)
			fprintf(stderr, "Publishing data of length %d\n", data_len);

		rc = MQTTClient_publish(client, opts.topic, data_len, buffer, opts.qos, opts.retained, &last_token);
		if (opts.stdin_lines == 0)
			break;

		if (rc != 0)
		{
			myconnect(client);
			rc = MQTTClient_publish(client, opts.topic, data_len, buffer, opts.qos, opts.retained, &last_token);
		}
		if (opts.qos > 0)
			MQTTClient_yield();
	}

	// rc = MQTTClient_waitForCompletion(client, last_token, 5000);


	return EXIT_SUCCESS;
}
