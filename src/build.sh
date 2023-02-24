


# quickjs-bindsqlite.c ---> quickjs-bindsqlite.o
gcc -c -fPIC -o quickjs-bindsqlite.o quickjs-bindsqlite.c -I../include/sqlite/master -I../include/quickjs/master
# quickjs-bindsqlite.so
gcc -shared -o qjsbindsqlite.so quickjs-bindsqlite.o ../lib/quickjs/master/quickjs.o -lsqlite3 -L../lib/sqlite3/master


#--------------------------------------------version: 1.3.12链接在一起，包比较重-----------------------------------------------------

# version: 1.3.12 quickjs-bindmqtt.c --->quickjs-bindmqtt.o
gcc -c -fPIC -o quickjs-bindmqtt.o quickjs-bindmqtt.c -I../include/paho.mqtt.c/1.3.12 -I../include/quickjs/master

# version: 1.3.12 pubsub_opts.c --->pubsub_opts.o
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../include/paho.mqtt.c/1.3.12

# version: 1.3.12 quickjs-bindmqtt.o pubsub_opts.o libpaho-mqtt3c.a ---> quickjs-bindmqtt.so
gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o ../lib/paho.mqtt.c/1.3.12/libpaho-mqtt3c.a
# gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c/1.3.12

#--------------------------------------------version: 1.3.12链接在一起，包比较重-----------------------------------------------------



#--------------------------------------------version: 1.3.12动态链接在一起-----------------------------------------------------

# version: 1.3.12 quickjs-bindmqtt.c --->quickjs-bindmqtt.o
gcc -c -fPIC -o quickjs-bindmqtt.o quickjs-bindmqtt.c -I../include/paho.mqtt.c/1.3.12 -I../include/quickjs/master

# version: 1.3.12 pubsub_opts.c --->pubsub_opts.o
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../include/paho.mqtt.c/1.3.12

# version: 1.3.12 quickjs-bindmqtt.o pubsub_opts.o libpaho-mqtt3c.a ---> quickjs-bindmqtt.so
gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c/1.3.12

sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local/1.3.12
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------version: 1.3.12动态链接在一起-----------------------------------------------------







#--------------------------------------------version: 1.3.0链接在一起，包比较重-----------------------------------------------------

# version: 1.3.0 quickjs-bindmqtt.c --->quickjs-bindmqtt.o
gcc -c -fPIC -o quickjs-bindmqtt.o quickjs-bindmqtt.c -I../include/paho.mqtt.c/1.3.0 -I../include/quickjs/master

# version: 1.3.0 pubsub_opts.c --->pubsub_opts.o
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../include/paho.mqtt.c/1.3.0

# version: 1.3.0 quickjs-bindmqtt.o pubsub_opts.o libpaho-mqtt3c.a ---> quickjs-bindmqtt.so
gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o ../lib/paho.mqtt.c/1.3.0/libpaho-mqtt3c-static.a
# gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c/1.3.12

#--------------------------------------------version: 1.3.0链接在一起，包比较重-----------------------------------------------------


#--------------------------------------------version: 1.3.0动态链接在一起-----------------------------------------------------

# version: 1.3.0 quickjs-bindmqtt.c --->quickjs-bindmqtt.o
gcc -c -fPIC -o quickjs-bindmqtt.o quickjs-bindmqtt.c -I../include/paho.mqtt.c/1.3.0 -I../include/quickjs/master

# version: 1.3.0 pubsub_opts.c --->pubsub_opts.o
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../include/paho.mqtt.c/1.3.0

# version: 1.3.0 quickjs-bindmqtt.o pubsub_opts.o libpaho-mqtt3c.a ---> quickjs-bindmqtt.so
gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c/1.3.0

sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local/1.3.0
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------version: 1.3.0动态链接在一起-----------------------------------------------------














sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/lib/paho.mqtt.c/1.3.0/lib/
sudo /sbin/ldconfig -v
sudo ldconfig


gcc -c -fPIC -o quickjs-bindmqtt.o quickjs-bindmqtt.c -I../deps/paho.mqtt.c/src/samples/include -I../deps/quickjs
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../deps/paho.mqtt.c/src/samples/include
gcc -shared -o quickjs-bindmqtt.so quickjs-bindmqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c