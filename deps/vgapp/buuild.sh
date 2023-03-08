# build gpio.c ---> gpio.so
gcc -fPIC -o gpio.o -c gpio.c
gcc -shared -o libgpio.so gpio.o

# build channel.c ---> channel.so
gcc -fPIC -o channel.o -c channel.c
gcc -shared -o channel.so channel.o

# build net.c ---> net.so
gcc -fPIC -o net.o -c net.c
gcc -shared -o net.so net.o

# build watchdog.c ---> watchdog.so
gcc -fPIC -o watchdog.o -c watchdog.c
gcc -shared -o watchdog.so watchdog.o

# build keyboard.c ---> libkeyboard.so
gcc -fPIC -o keyboard.o -c keyboard.c
gcc -shared -o libkeyboard.so keyboard.o

# build sysinfo.c ---> libsysinfo.so
gcc -fPIC -o sysinfo.o -c sysinfo.c
gcc -shared -o libsysinfo.so sysinfo.o