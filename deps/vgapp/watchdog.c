#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "watchdog.h"

struct vbar_watchdog watdog;

/* 打开看门狗设备 */
struct vbar_watchdog *vbar_watchdog_open(int type, unsigned long arg)
{
    printf("vbar_watchdog_open\n");
    return &watdog;
}

/* 判断是否是上电复位 */
bool vbar_watchdog_is_poweron(struct vbar_watchdog *wdt)
{
    printf("vbar_watchdog_is_poweron\n");
    return 1;
}

/* 开启看门狗总定时器 */
bool vbar_watchdog_start(struct vbar_watchdog *wdt, int timeout_ms)
{
    printf("vbar_watchdog_start\n");
    return 1;
}

/* 关闭看门狗总定时器 */
void vbar_watchdog_stop(struct vbar_watchdog *wdt)
{
    printf("vbar_watchdog_stop\n");
}

/* 控制指定通道开关 */
bool vbar_watchdog_enable(struct vbar_watchdog *wdt, unsigned int chan, bool toset)
{
    printf("vbar_watchdog_enable\n");
    return 1;
}

/* 喂狗指定通道 */
bool vbar_watchdog_restart(struct vbar_watchdog *wdt, unsigned int chan)
{
    printf("vbar_watchdog_restart\n");
    return 1;
}

/* 关闭看门狗设备 */
void vbar_watchdog_close(struct vbar_watchdog *wdt)
{
    printf("vbar_watchdog_close\n");
}