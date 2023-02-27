#ifndef __VBAR_CHANNEL_H__
#define __VBAR_CHANNEL_H__

#include <unistd.h>
#include <stddef.h>
#include <stdint.h>


// #include <vbar/export.h> /* for VBARLIB_API */
#include "export.h"

/* 通道类型定义 for vbar_channel_open */
enum {
    VBAR_CHANNEL_TYPE_USBKBW    = 1,
    VBAR_CHANNEL_TYPE_USBHID    = 2,
    VBAR_CHANNEL_TYPE_UART      = 3,
	VBAR_CHANNEL_TYPE_WIEGAND   = 4,
    VBAR_CHANNEL_TYPE_TCPSERVER = 5,
    VBAR_CHANNEL_TYPE_TCPCLIENT = 6,
};

/* 请求定义 for vbar_channel_ioctl */
/* usbkwb*/
enum {
    VBAR_CHANNEL_IOC_SET_KBW_CONFIG      = 1,
    VBAR_CHANNEL_IOC_SET_KBW_UPPER       = 2,
    VBAR_CHANNEL_IOC_SET_KBW_UPTIME      = 3,
    VBAR_CHANNEL_IOC_SET_KBW_DOWNTIME    = 4,
};
/* usbhid */
enum {
    VBAR_CHANNEL_IOC_SET_HID_REPORT_LEN  = 1,
};
/* uart */
enum {
    VBAR_CHANNEL_IOC_SET_UART_PARAM      = 1,
};
/* wiegand */
enum {
    VBAR_CHANNEL_IOC_SET_WIEGAND_MODE         = 1,
    VBAR_CHANNEL_IOC_SET_WIEGAND_BUSY_TIME    = 2,
    VBAR_CHANNEL_IOC_SET_WIEGAND_FREE_TIME    = 3,
};

#define VBAR_CHANNEL_WIEGAND_MODE_26		  1
#define VBAR_CHANNEL_WIEGAND_MODE_34		  2
#define VBAR_CHANNEL_WIEGAND_MODE_128         3
#define VBAR_CHANNEL_WIEGAND_MODE_256         4
#define VBAR_CHANNEL_WIEGAND_MODE_2048        5

/* 信道结构 */
struct vbar_channel {
    uint32_t type;
    int (*send)(struct vbar_channel *, const unsigned char *, size_t);
    int (*recv)(struct vbar_channel *, unsigned char *, size_t, int);
    int (*ioctl)(struct vbar_channel *, int, unsigned long);
	int (*flush)(struct vbar_channel *, int);
    void (*close)(struct vbar_channel *);
    void *private_data;
};

#ifdef	__cplusplus
extern "C" {
#endif

/* 打开信道 */
VBARLIB_API struct vbar_channel *vbar_channel_open(int type, unsigned long arg);

/* 发送数据 */
VBARLIB_API int vbar_channel_send(struct vbar_channel *channel,
                                  const unsigned char *buffer, size_t length);

/* 接收数据 */
VBARLIB_API int vbar_channel_recv(struct vbar_channel *channel,
                                  unsigned char *buffer, size_t size, int milliseconds);

/* 调用信道特殊IO接口 */
VBARLIB_API int vbar_channel_ioctl(struct vbar_channel *channel, int request, unsigned long arg);

/* 关闭信道 */
VBARLIB_API void vbar_channel_close(struct vbar_channel *channel);

VBARLIB_API int vbar_channel_flush(struct vbar_channel *channel, int queue_selector);
#ifdef __cplusplus
}
#endif

#endif /* __VBAR_CHANNEL_H__ */
