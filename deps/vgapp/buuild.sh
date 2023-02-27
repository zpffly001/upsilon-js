# build gpio.c ---> gpio.so
gcc -fPIC -o gpio.o -c gpio.c
gcc -shared -o libgpio.so gpio.o
