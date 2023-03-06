#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "sysinfo.h"



/**
* @brief vbar_sysinfo_get_uptime 获取系统启动的运行时间
*
* @return 成功：运行时间， 失败：-1
*/

long vbar_sysinfo_get_uptime(void)
{
    printf("vbar_sysinfo_get_uptime\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_totalmem 获取系统的总内存
 *
 * @return 成功：内存byte数， 失败：-1
 */
long vbar_sysinfo_get_totalmem(void)
{
    printf("vbar_sysinfo_get_totalmem\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_freemem 获取系统剩余内存
 *
 * @return 成功：内存byte数， 失败：-1
 */
long vbar_sysinfo_get_freemem(void)
{
    printf("vbar_sysinfo_get_freemem\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_totaldisk 获取系统可用磁盘总量
 *
 * @param path 挂载点路径，默认："/"
 *
 * @return 成功：磁盘BYTE总数，失败：-1
 */
long vbar_sysinfo_get_totaldisk(const char *path)
{
    printf("vbar_sysinfo_get_totaldisk\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_freedisk 获取系统磁盘剩余可用量
 *
 * @param path 载点路径，默认："/"
 *
 * @return 成功：磁盘剩余BYTE总数，失败：-1
 */
long vbar_sysinfo_get_freedisk(const char *path)
{
    printf("vbar_sysinfo_get_freedisk\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_uuid 获取设备uuid（字符串）
 *
 * @param uuid 存储uuid buffer
 * @param len  buffer大小，最小为17byte
 *
 * @return 成功：uuid字符串长度，失败：-1
 */
int vbar_sysinfo_get_uuid(char *uuid, uint32_t len)
{
    printf("vbar_sysinfo_get_uuid\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_uuid2mac 获取通过uuid计算的mac地址
 *
 * @param mac 存储mac buffer
 * @param len buffer大小，最小为17byte
 *
 * @return 成功：mac字符串长度，失败：-1
 */
int vbar_sysinfo_get_uuid2mac(char *mac, uint32_t len)
{
    printf("vbar_sysinfo_get_uuid2mac\n");
    return 1;
}

/**
 * @brief vbar_sysinfo_get_freecpu 获取cpu占用率
 *
 * @return 成功 占用百分比      失败 -1
 */
int vbar_sysinfo_get_freecpu(void)
{
    printf("vbar_sysinfo_get_freecpu\n");
    return 1;
}