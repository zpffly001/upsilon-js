#--------------------------------------------sqlite模块--------------------------------------------
# quickjs-sqlite.c ---> quickjs-sqlite.o
gcc -c -fPIC -o quickjs-sqlite.o quickjs-sqlite.c -I../include/sqlite/master -I../include/quickjs/master
# quickjs-sqlite.so
gcc -shared -o quickjs-sqlite.so quickjs-sqlite.o  -lsqlite3 -L../lib/sqlite3/master
#--------------------------------------------sqlite模块--------------------------------------------


# mqtt模块 当前方法一般不用，请使用下一个mqtt编译命令组
#--------------------------------------------mqtt模块 version: 1.3.12链接在一起，包比较重-----------------------------------------------------

# version: 1.3.12 quickjs-mqtt.c --->quickjs-mqtt.o
gcc -c -fPIC -o quickjs-mqtt.o quickjs-mqtt.c -I../include/paho.mqtt.c/1.3.12 -I../include/quickjs/master

# version: 1.3.12 pubsub_opts.c --->pubsub_opts.o
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../include/paho.mqtt.c/1.3.12

# version: 1.3.12 quickjs-mqtt.o pubsub_opts.o libpaho-mqtt3c.a ---> quickjs-mqtt.so
gcc -shared -o quickjs-mqtt.so quickjs-mqtt.o pubsub_opts.o ../lib/paho.mqtt.c/1.3.12/libpaho-mqtt3c.a
# gcc -shared -o quickjs-mqtt.so quickjs-mqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c/1.3.12

#--------------------------------------------mqtt模块 version: 1.3.12链接在一起，包比较重-----------------------------------------------------


# mqtt模块
#--------------------------------------------mqtt模块 version: 1.3.12动态链接在一起-----------------------------------------------------

# version: 1.3.12 quickjs-mqtt.c --->quickjs-mqtt.o
gcc -c -fPIC -o quickjs-mqtt.o quickjs-mqtt.c -I../include/paho.mqtt.c/1.3.12 -I../include/quickjs/master

# version: 1.3.12 pubsub_opts.c --->pubsub_opts.o
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../include/paho.mqtt.c/1.3.12

# version: 1.3.12 quickjs-mqtt.o pubsub_opts.o libpaho-mqtt3c.so ---> quickjs-mqtt.so
gcc -shared -o quickjs-mqtt.so quickjs-mqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c/1.3.12

sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local/1.3.12
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------mqtt模块 version: 1.3.12动态链接在一起-----------------------------------------------------


#--------------------------------------------gpio模块-----------------------------------------------------
# quickjs-gpio.c --->quickjs-gpio.o
gcc -c -fPIC -o quickjs-gpio.o quickjs-gpio.c -I../include/vgapp -I../include/quickjs/master

# version: 1.3.12 quickjs-gpio.o libgpio.so ---> quickjs-gpio.so
gcc -shared -o quickjs-gpio.so quickjs-gpio.o -lgpio -L../lib

# 是为了在mqtt require的时候，去/home/zpf/software/upsilon-js/local路径找gpio.so
sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------gpio模块-----------------------------------------------------


# uart模块



# net模块

















sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/lib/paho.mqtt.c/1.3.0/lib/
sudo /sbin/ldconfig -v
sudo ldconfig


gcc -c -fPIC -o quickjs-mqtt.o quickjs-mqtt.c -I../deps/paho.mqtt.c/src/samples/include -I../deps/quickjs
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../deps/paho.mqtt.c/src/samples/include
gcc -shared -o quickjs-mqtt.so quickjs-mqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c