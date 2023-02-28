#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "channel.h"


/* 打开信道 */
VBARLIB_API struct vbar_channel *vbar_channel_open(int type, unsigned long arg)
{
    printf("vbar_channel_open\n");
    return NULL;
}

/* 发送数据 */
VBARLIB_API int vbar_channel_send(struct vbar_channel *channel,
                                  const unsigned char *buffer, size_t length)
{
    printf("vbar_channel_send\n");
    return 1;
}

/* 接收数据 */
VBARLIB_API int vbar_channel_recv(struct vbar_channel *channel,
                                  unsigned char *buffer, size_t size, int milliseconds)
{
    printf("vbar_channel_recv\n");
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