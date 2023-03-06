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
gcc -shared -o quickjs-gpio.so quickjs-gpio.o -lgpio -L../lib/vgapp

# 是为了在mqtt require的时候，去/home/zpf/software/upsilon-js/local路径找gpio.so
sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local
sudo /sbin/ldconfig -v
sudo ldconfig


gcc -c -fPIC -o quickjs-gpio.o quickjs-gpio.c -I../include/vgapp -I../include/quickjs/master
# 依赖gpio.o，这是ldd时不会发现gpio.so，nm -D xxx.so会发现使用到的gpio中的方法已经导出
gcc -shared -o quickjs-gpio.so quickjs-gpio.o ../deps/vgapp/gpio.o
#--------------------------------------------gpio模块-----------------------------------------------------


# channel模块
#--------------------------------------------channel模块-----------------------------------------------------
# quickjs-channel.c --->quickjs-channel.o
gcc -c -fPIC -o quickjs-channel.o quickjs-channel.c -I../include/vgapp -I../include/quickjs/master

# version: 1.3.12 quickjs-channel.o libchannel.so ---> quickjs-channel.so
gcc -shared -o quickjs-channel.so quickjs-channel.o -lchannel -L../lib/vgapp

# 是为了在mqtt require的时候，去/home/zpf/software/upsilon-js/local路径找channel.so
sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------channel模块-----------------------------------------------------


# net模块
#--------------------------------------------net模块-----------------------------------------------------
# quickjs-net.c --->quickjs-net.o
gcc -c -fPIC -o quickjs-net.o quickjs-net.c -I../include/vgapp -I../include/quickjs/master

# version: 1.3.12 quickjs-net.o libnet.so ---> quickjs-net.so
gcc -shared -o quickjs-net.so quickjs-net.o -lnet -L../lib/vgapp

# 是为了在mqtt require的时候，去/home/zpf/software/upsilon-js/local路径找net.so
sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------net模块-----------------------------------------------------



# watchdog模块
#--------------------------------------------watchdog模块-----------------------------------------------------
# quickjs-watchdog.c --->quickjs-watchdog.o
gcc -c -fPIC -o quickjs-watchdog.o quickjs-watchdog.c -I../include/vgapp -I../include/quickjs/master

# version: 1.3.12 quickjs-watchdog.o libwatchdog.so ---> quickjs-watchdog.so
gcc -shared -o quickjs-watchdog.so quickjs-watchdog.o -lwatchdog -L../lib/vgapp

# 是为了在mqtt require的时候，去/home/zpf/software/upsilon-js/local路径找watchdog.so
sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/local
sudo /sbin/ldconfig -v
sudo ldconfig
#--------------------------------------------net模块-----------------------------------------------------

















sudo vi /etc/ld.so.conf
/home/zpf/software/upsilon-js/lib/paho.mqtt.c/1.3.0/lib/
sudo /sbin/ldconfig -v
sudo ldconfig


gcc -c -fPIC -o quickjs-mqtt.o quickjs-mqtt.c -I../deps/paho.mqtt.c/src/samples/include -I../deps/quickjs
gcc -c -fPIC -o pubsub_opts.o pubsub_opts.c -I../deps/paho.mqtt.c/src/samples/include
gcc -shared -o quickjs-mqtt.so quickjs-mqtt.o pubsub_opts.o -lpaho-mqtt3c -L../lib/paho.mqtt.c