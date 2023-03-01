#include <stdio.h>
#include <string.h>
// #include <stddef.h>

#include "channel.h"

int channel_send(struct vbar_channel * channel, const unsigned char * buf, size_t len)
{
    printf("send\n");
    return 1;
}

int channel_recv(struct vbar_channel * channel, const unsigned char * buf, size_t len)
{
    printf("recv\n");
    return 1;
}

int channel_ioctl(struct vbar_channel * channel, int value, size_t len)
{
    printf("ioctl\n");
    return 1;
}

int channel_flush(struct vbar_channel * channel, int value)
{
    printf("flush\n");
    return 1;
}

int channel_close(struct vbar_channel * channel)
{
    printf("close\n");
    return 1;
}

static struct vbar_channel channel =
{
    .send = channel_send,
    .recv = channel_recv,
    .ioctl = channel_ioctl,
    .flush = channel_flush,
    .close = channel_close,
};

/* 打开信道 */
VBARLIB_API struct vbar_channel *vbar_channel_open(int type, unsigned long arg)
{
    printf("vbar_channel_open\n");
    channel.type = type;
    return &channel;
}

/* 发送数据 */
VBARLIB_API int vbar_channel_send(struct vbar_channel *channel,
                                  const unsigned char *buffer, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("send[%d]: %d\n", i, buffer[i]);
    }

    printf("vbar_channel_send\n");
    return 1;
}

/* 接收数据 */
VBARLIB_API int vbar_channel_recv(struct vbar_channel *channel,
                                  unsigned char *buffer, size_t size, int milliseconds)
{
    printf("vbar_channel_recv\n");
    buffer[0] = 0x55;
    buffer[1] = 0x55;
    buffer[2] = 0x55;
    buffer[3] = 0x55;
    buffer[4] = 0x55;
    buffer[5] = 0x55;
    return 1;
}

/* 调用信道特殊IO接口 */
VBARLIB_API int vbar_channel_ioctl(struct vbar_channel *channel, int request, unsigned long arg)
{
    printf("vbar_channel_ioctl\n");
    return 1;
}

/* 关闭信道 */
VBARLIB_API void vbar_channel_close(struct vbar_channel *channel)
{
    printf("vbar_channel_close\n");
}

/* 刷新信道 */
VBARLIB_API int vbar_channel_flush(struct vbar_channel *channel, int queue_selector)
{
    printf("vbar_channel_flush\n");
    return 1;
}