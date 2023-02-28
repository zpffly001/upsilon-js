#include <stdio.h>
#include "channel.h"

int main()
{
    printf("hello\n");

    struct vbar_channel *channel = vbar_channel_open(66, 77);
    channel->flush(channel, 1);

    int res = vbar_channel_flush(channel, 1);
    printf("res: %d\n", res);
}

// build gcc -o testChannel testChannel.c -I ../ ../channel.c