#include <stdio.h>
#include <channel.h>

// gcc -fPIC -o channel-main.o -c channel-main.c -I./
// gcc -shared -o channel-main.so channel-main.o libchannel.so

void tttt()
{
    vbar_channel_open(11, 22);
}