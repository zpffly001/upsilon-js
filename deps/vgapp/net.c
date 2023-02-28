#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "net.h"



/**
 * @brief vbar_net_init 网络模块初始化
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_init(void)
{
    printf("vbar_net_init\n");
    return 1;
}

/**
 * @brief vbar_net_exit 清理网络模块资源
 *
 * @return 无
 */
VBARLIB_API void vbar_net_exit(void)
{
    printf("vbar_net_exit\n");
}

/**
 * @brief vbar_net_card_enable 使能网卡，并添加到网络管理模块
 *
 * @param type   网络类型
 * @param on     开启/关闭
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_card_enable(uint8_t type, bool on)
{
    printf("vbar_net_card_enable\n");
    return 1;
}

/**
 * @brief vbar_net_status_callback_register 注册网络状态回调函数
 *
 * @param func  回调函数
 * @param pdata 私有数据
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_status_callback_register(vbar_net_status_cb func, void *pdata)
{
    printf("vbar_net_status_callback_register\n");
    return 1;
}

/**
 * @brief vbar_net_set_mode_by_card 设置指定网卡的模式及对应参数网络参数
 *
 * @param type   网卡类型
 * @param mode   网络模式
 * @param param  网络参数
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_set_mode_by_card(uint8_t type, enum net_mode mode, struct net_static_param *param)
{
    printf("vbar_net_set_mode_by_card\n");
    return 1;
}


/**
 * @brief vbar_net_get_mode_by_card 获取指定网卡的模式及对应参数网络参数
 *
 * @param type     网卡类型
 * @param param    网络参数缓存，传NULL则只返回模式
 *
 * @return >0：成功,具体的网络模式，<0 失败
 */
VBARLIB_API int vbar_net_get_mode_by_card(uint8_t type, struct net_static_param *param)
{
    printf("vbar_net_get_mode_by_card\n");
    return 1;
}

/**
 * @brief vbar_net_set_master_card 设置主网卡，应用程序网络状态由次网卡决定
 *
 * @param type  网卡类型
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_set_master_card(uint8_t type)
{
    printf("vbar_net_set_master_card\n");
    return 1;
}

/**
 * @brief vbar_net_get_master_card 获取主网卡
 *
 * @return >0：成功 主网卡类型，<0 失败
 */
VBARLIB_API int vbar_net_get_master_card(void)
{
    printf("vbar_net_get_master_card\n");
    return 1;
}


/**
 * @brief vbar_net_get_status 获取网络状态
 *
 * @return 网络状态
 */
VBARLIB_API enum net_status vbar_net_get_status(void)
{
    printf("vbar_net_get_status\n");
    enum net_status status = VBAR_NET_STATUS_DOWN;
    return status;
}

/**
 * @brief vbar_net_set_status 设置网络状态
 *
 * @param status  网络状态
 *
 * @return 无
 */
VBARLIB_API void vbar_net_set_status(enum net_status status)
{
    printf("vbar_net_set_status\n");
}


/**
 * @brief vbar_net_get_wifi_ssid_list 获取wifi热点列表
 *
 * @param list  WIFI热点列表
 * @param timeout_ms  超时时间
 *
 * @return >=0 成功 热点总数，<0 失败
 */
VBARLIB_API int vbar_net_get_wifi_ssid_list(struct vbar_ssid_scan_list *list, uint32_t timeout_ms, uint32_t interval_ms)
{
    printf("vbar_net_get_wifi_ssid_list\n");
    return 1;
}

/**
 * @brief vbar_net_connect_wifi_ssid 连接到wifi热点
 *
 * @param ssid
 * @param psk
 * @param params
 *
 * @return >=0 成功 网络编号，<0 失败
 */
VBARLIB_API int vbar_net_connect_wifi_ssid(const char *ssid, const char *psk, const char *params)
{
    printf("vbar_net_connect_wifi_ssid\n");
    return 1;
}

/**
 * @brief vbar_net_get_wifi_saved_list 获取已保存的热点列表
 *
 * @param list  已保存的列表
 *
 * @return >=0 成功 热点总数，<0 失败
 */
VBARLIB_API int vbar_net_get_wifi_saved_list(struct vbar_wifi_save_list *list)
{
    printf("vbar_net_get_wifi_saved_list\n");
    return 1;
}

/**
 * @brief vbar_net_get_current_wifi_info 获取当前热点的信息
 *
 * @param info  热点信息
 * @param timeout_ms  超时时间
 *
 * @return 0 成功，<0 失败
 */
VBARLIB_API int vbar_net_get_current_wifi_info(struct vbar_wpa_wifi_info *info, uint32_t timeout_ms)
{
    printf("vbar_net_get_current_wifi_info\n");
    return 1;
}

/**
 * @brief vbar_net_connect_saved_wifi 连接到已保存的wifi热点
 *
 * @param id  网络编号
 *
 * @return 0 成功，<0 失败
 */
VBARLIB_API int vbar_net_connect_saved_wifi(uint16_t id)
{
    printf("vbar_net_connect_saved_wifi\n");
    return 1;
}

/**
 * @brief vbar_net_disconnet_wifi 断开当前连接的wifi热点
 *
 * @return 无
 */
VBARLIB_API void vbar_net_disconnet_wifi()
{
    printf("vbar_net_disconnet_wifi\n");
}