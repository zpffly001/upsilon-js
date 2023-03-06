#ifndef __VBAR_WATCHDOG_H__
#define __VBAR_WATCHDOG_H__

/*
 * 看门狗
 */

// #include "vbar/export.h"
#include "export.h"
#include <pthread.h>

/* 看门狗类型定义 */
enum {
    VBAR_WATCHDOG_TYPE_SOFTWARE = 1,  /* bit1 */
    VBAR_WATCHDOG_TYPE_HARDWARE = 2,  /* bit2 */
    VBAR_WATCHDOG_TYPE_BEGIN = VBAR_WATCHDOG_TYPE_SOFTWARE,
    VBAR_WATCHDOG_TYPE_END = VBAR_WATCHDOG_TYPE_HARDWARE + 1,
};

/* 看门狗结构 */
struct vbar_watchdog {
    unsigned int type;
    void (*start)(struct vbar_watchdog *, unsigned int);
    void (*stop)(struct vbar_watchdog *);
    void (*ping)(struct vbar_watchdog *);
    bool (*is_poweron)(struct vbar_watchdog *);
    void (*close)(struct vbar_watchdog *);
    unsigned int enabled_chans;
    unsigned int restarted_chans;
    pthread_t thread;
    pthread_mutex_t mutex;
    void *pdata;
    struct vbar_watchdog *hardware_wdt;
    struct vbar_watchdog *software_wdt;
};

#ifdef	__cplusplus
extern "C" {
#endif

/* 打开看门狗设备 */
VBARLIB_API struct vbar_watchdog *vbar_watchdog_open(int type, unsigned long arg);

/* 判断是否是上电复位 */
VBARLIB_API bool vbar_watchdog_is_poweron(struct vbar_watchdog *wdt);

/* 开启看门狗总定时器 */
VBARLIB_API bool vbar_watchdog_start(struct vbar_watchdog *wdt, int timeout_ms);

/* 关闭看门狗总定时器 */
VBARLIB_API void vbar_watchdog_stop(struct vbar_watchdog *wdt);

/* 控制指定通道开关 */
VBARLIB_API bool vbar_watchdog_enable(struct vbar_watchdog *wdt, unsigned int chan, bool toset);

/* 喂狗指定通道 */
VBARLIB_API bool vbar_watchdog_restart(struct vbar_watchdog *wdt, unsigned int chan);

/* 关闭看门狗设备 */
VBARLIB_API void vbar_watchdog_close(struct vbar_watchdog *wdt);

#ifdef __cplusplus
}
#endif

#endif /* __VBAR_WATCHDOG_H__ */
