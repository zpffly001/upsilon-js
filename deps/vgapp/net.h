#ifndef __VBAR_NET_H__
#define __VBAR_NET_H__

#include <stdint.h>
#include <pthread.h>

// #include <vbar/export.h>
#include "export.h"

#define VBAR_NET_CALLBACK_MAX   10

enum {
    VBAR_NET_TYPE_NONE =  0x00,
    VBAR_NET_TYPE_ETH  =  0x01,
    VBAR_NET_TYPE_WIFI =  0x02,
    VBAR_NET_TYPE_MODEM   =  0x04,
};

enum net_status {
    VBAR_NET_STATUS_NONE             = 0,   /* 未初始态 */
    VBAR_NET_STATUS_DOWN             = 1,   /* 网卡处于关闭状态 */
    VBAR_NET_STATUS_UP               = 2,   /* 网卡处于打开状态 */
    VBAR_NET_STATUS_CONNECTING_ROUTE = 3,   /* 网线已插入或者wifi已连接ssid 但未分配ip */
    VBAR_NET_STATUS_CONNECTED_ROUTE  = 4,   /* 已成功分配ip */
    VBAR_NET_STATUS_CONNECTED_SERVER = 5    /* 已连接指定服务或者通过测试可以连接到广域网 */
};

enum {
    NET_NETLINK_CARD_STATUS_DOWN    = 1,
    NET_NETLINK_CARD_STATUS_UP      = 2,
    NET_NETLINK_CARD_STATUS_RUNNING = 3,
    NET_NETLINK_CARD_STATUS_ROUTE   = 4
};

enum net_mode {
    VBAR_NET_MODE_STATIC     = 1,
    VBAR_NET_MODE_DHCP       = 2,
    VBAR_NET_MODE_WIFI_AP    = 3
};

#ifdef	__cplusplus
extern "C" {
#endif


typedef void (*vbar_net_status_cb)(uint8_t type, enum net_status status, void *pdata);

struct net_data {
    vbar_net_status_cb func_cb;
    void *pdata;
};

struct net_callback_table {
    unsigned int index;
    unsigned int amount;
    struct net_data *ndatas;
    pthread_mutex_t index_mutex;
};

struct net_param_comm {
    int magic;
    uint8_t type;

    bool ping;
    char ping_ip[20];
    char ip[20];
    char gateway[20];
    char netmask[20];
    char dns0[20];
    char dns1[20];
    char mac[20];
};

struct net_param_4g {
#define NET_OBJECT_MAGIC_4G 0x5856a101
    struct net_param_comm common;
    char apn[20];
    char iccid[30];
};

struct net_param_2g {
#define NET_OBJECT_MAGIC_2G 0x5856a202
    struct net_param_comm common;
};

struct net_param_eth {
#define NET_OBJECT_MAGIC_ETH 0x5856a303
    struct net_param_comm common;
};

struct net_param_wifi {
#define NET_OBJECT_MAGIC_WIFI 0x5856a404
    struct net_param_comm common;
    char ssid[64];
    char passwd[64];
};

struct net_static_param {
    char ip[20];
    char gateway[20];
    char netmask[20];
    char dns0[20];
    char dns1[20];
};

/*wifi扫码周围网络的结果*/
struct vbar_wpa_scan_result {
    uint32_t freq;      /* wifi信道值 */
    int32_t level;   /* 信号强度，值越大信号越强 */
    uint8_t ssid[256];  /* 网络名 */
    uint8_t bssid[24];  /* wifi热点MAC地址 */
    uint8_t flags[256]; /* 加密相关信息 */
};

/*wifi已保存网络的结果*/
struct vbar_wpa_list_network {
    uint16_t id;        /* 网络编号 */
    uint8_t ssid[256];  /* ssid无线网络名 */
    uint8_t bssid[24];  /* wifi热点MAC地址 */
    uint8_t flags[256]; /* 加密相关信息 */
};

/*wifi信息*/
struct vbar_wpa_wifi_info {
    uint16_t id;                 /* 网络编号 */
    uint32_t freq;               /* wifi信道值 */
    int32_t rssi;                /* 无线接收信号强度，值为负数 */
    uint16_t noise;              /* 噪声*/
    uint16_t link_speed;         /* 连接速率 */
    uint16_t wifi_generation;    /* wifi代数, WIFI 4, WIFI 5, WIFI 6 */
    uint8_t wpa_state[64];       /* WPA状态 */
    uint8_t ip[16];              /* 设备IP地址 */
    uint8_t bssid[24];           /* wifi热点MAC地址 */
    uint8_t ssid[256];           /* 网络名 */
    uint8_t mode[32];            /* 网络类型 */
    uint8_t pairwise_cipher[64]; /* 单播加密相关信息 */
    uint8_t group_cipher[64];    /* 组播加密相关信息 */
    uint8_t key_mgmt[64];        /* 密钥管理类型 */
    uint8_t p2p_addr[32];
    uint8_t address[32];
    uint8_t uuid[64];
};

/*wifi扫码周围网络的列表*/
struct vbar_ssid_scan_list {
    int counts;                              /* 扫描wifi总数 */
    struct vbar_wpa_scan_result results[20]; /* 扫描wifi结果 */
};

/*wifi已保存网络的列表*/
struct vbar_wifi_save_list {
    int counts;                               /* 扫描wifi总数 */
    struct vbar_wpa_list_network results[5]; /* 扫描wifi结果 */
};

/**
 * @brief vbar_net_init 网络模块初始化
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_init(void);

/**
 * @brief vbar_net_exit 清理网络模块资源
 *
 * @return 无
 */
VBARLIB_API void vbar_net_exit(void);

/**
 * @brief vbar_net_card_enable 使能网卡，并添加到网络管理模块
 *
 * @param type   网络类型
 * @param on     开启/关闭
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_card_enable(uint8_t type, bool on);

/**
 * @brief vbar_net_status_callback_register 注册网络状态回调函数
 *
 * @param func  回调函数
 * @param pdata 私有数据
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_status_callback_register(vbar_net_status_cb func, void *pdata);

/**
 * @brief vbar_net_set_mode_by_card 设置指定网卡的模式及对应参数网络参数
 *
 * @param type   网卡类型
 * @param mode   网络模式
 * @param param  网络参数
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_set_mode_by_card(uint8_t type, enum net_mode mode, struct net_static_param *param);


/**
 * @brief vbar_net_get_mode_by_card 获取指定网卡的模式及对应参数网络参数
 *
 * @param type     网卡类型
 * @param param    网络参数缓存，传NULL则只返回模式
 *
 * @return >0：成功,具体的网络模式，<0 失败
 */
VBARLIB_API int vbar_net_get_mode_by_card(uint8_t type, struct net_static_param *param);

/**
 * @brief vbar_net_set_master_card 设置主网卡，应用程序网络状态由次网卡决定
 *
 * @param type  网卡类型
 *
 * @return 0：成功，<0 失败
 */
VBARLIB_API int vbar_net_set_master_card(uint8_t type);

/**
 * @brief vbar_net_get_master_card 获取主网卡
 *
 * @return >0：成功 主网卡类型，<0 失败
 */
VBARLIB_API int vbar_net_get_master_card(void);


/**
 * @brief vbar_net_get_status 获取网络状态
 *
 * @return 网络状态
 */
VBARLIB_API enum net_status vbar_net_get_status(void);

/**
 * @brief vbar_net_set_status 设置网络状态
 *
 * @param status  网络状态
 *
 * @return 无
 */
VBARLIB_API void vbar_net_set_status(enum net_status status);


/**
 * @brief vbar_net_get_wifi_ssid_list 获取wifi热点列表
 *
 * @param list  WIFI热点列表
 * @param timeout_ms  超时时间
 *
 * @return >=0 成功 热点总数，<0 失败
 */
VBARLIB_API int vbar_net_get_wifi_ssid_list(struct vbar_ssid_scan_list *list, uint32_t timeout_ms, uint32_t interval_ms);

/**
 * @brief vbar_net_connect_wifi_ssid 连接到wifi热点
 *
 * @param ssid
 * @param psk
 * @param params
 *
 * @return >=0 成功 网络编号，<0 失败
 */
VBARLIB_API int vbar_net_connect_wifi_ssid(const char *ssid, const char *psk, const char *params);

/**
 * @brief vbar_net_get_wifi_saved_list 获取已保存的热点列表
 *
 * @param list  已保存的列表
 *
 * @return >=0 成功 热点总数，<0 失败
 */
VBARLIB_API int vbar_net_get_wifi_saved_list(struct vbar_wifi_save_list *list);

/**
 * @brief vbar_net_get_current_wifi_info 获取当前热点的信息
 *
 * @param info  热点信息
 * @param timeout_ms  超时时间
 *
 * @return 0 成功，<0 失败
 */
VBARLIB_API int vbar_net_get_current_wifi_info(struct vbar_wpa_wifi_info *info, uint32_t timeout_ms);

/**
 * @brief vbar_net_connect_saved_wifi 连接到已保存的wifi热点
 *
 * @param id  网络编号
 *
 * @return 0 成功，<0 失败
 */
VBARLIB_API int vbar_net_connect_saved_wifi(uint16_t id);

/**
 * @brief vbar_net_disconnet_wifi 断开当前连接的wifi热点
 *
 * @return 无
 */
VBARLIB_API void vbar_net_disconnet_wifi();


#ifdef	__cplusplus
}
#endif

#endif
