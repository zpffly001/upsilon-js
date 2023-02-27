#ifndef __VBAR_GPIO_H___
#define __VBAR_GPIO_H___

#include <stdint.h>
// #include <vbar/export.h>
// #include <soc/gpio.h>

#include "export.h"
enum gpio_function {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};


#ifdef	__cplusplus
extern "C" {
#endif
#define GPIO_PA(n)  (0*32 + n)
#define GPIO_PB(n)  (1*32 + n)
#define GPIO_PC(n)  (2*32 + n)
#define GPIO_PD(n)  (3*32 + n)
#define GPIO_PE(n)  (4*32 + n)
#define GPIO_PF(n)  (5*32 + n)

struct vbar_gpio {
    int (*request)(uint32_t);
    void (*free)(uint32_t);
    void (*set_func)(enum gpio_function, uint32_t);
    void (*set_pull)(uint32_t, uint32_t);
    int (*get_pull)(uint32_t);
    void (*set_drive_strength)(uint32_t, uint16_t);
    uint16_t (*get_drive_strength)(uint32_t);
    void (*set_value)(uint32_t, uint8_t);
    int (*get_value)(uint32_t);
    void (*set_slew_rate)(uint32_t, bool);
    void (*set_schmitt_enable)(uint32_t, bool);
    void (*set_filter)(uint32_t, uint16_t);
    int (*port_lock)(uint32_t);
    int (*port_unlock)(uint32_t);
    void (*close)(struct vbar_gpio *);
};

/**
 * @brief vbar_gpio_init gpio 初始化
 *
 * @return 0：成功， -1：失败
 */
VBARLIB_API int vbar_gpio_init(void);

/**
 * @brief vbar_gpio_exit 释放gpio资源
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_exit(void);

/**
 * @brief vbar_gpio_request 申请gpio
 *
 * @param gpio gpio值
 *
 * @return 0：成功，<0：失败
 */
VBARLIB_API int vbar_gpio_request(uint32_t gpio);

/**
 * @brief vbar_gpio_free 释放指定gpio
 *
 * @param gpio gpio值
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_free(uint32_t gpio);

/**
 * @brief vbar_gpio_set_func 设置指定gpio功能
 *
 * @param gpio  gpio值
 * @param func  功能类型
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_func(uint32_t gpio, enum gpio_function func);

/**
 * @brief vbar_gpio_set_pull 设置指定gpio上拉状态
 *
 * @param gpio  gpio值
 * @param state 上拉状态
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_pull_state(uint32_t gpio, uint32_t state);

/**
 * @brief vbar_gpio_get_pull 获取指定gpio上拉状态
 *
 * @param gpio
 *
 * @return <0：失败，>=0 成功
 */
VBARLIB_API int vbar_gpio_get_pull_state(uint32_t gpio);

/**
 * @brief vbar_gpio_set_value 设置指定gpio的值
 *
 * @param gpio    gpio值
 * @param value   要设置的值0或1
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_value(uint32_t gpio, uint8_t value);

/**
 * @brief vbar_gpio_get_value 获取指定gpio值
 *
 * @param gpio   gpio值
 *
 * @return <0：失败，>=0：成功
 */
VBARLIB_API int vbar_gpio_get_value(uint32_t gpio);

/**
 * @brief vbar_gpio_set_drive_strength 设置指定gpio的驱动能力
 *
 * @param gpio     gpio值
 * @param strength 驱动能力值
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_drive_strength(uint32_t gpio, uint16_t strength);

/**
 * @brief vbar_gpio_get_drive_strength 获取指定gpio的驱动能力
 *
 * @param gpio    gpio值
 *
 * @return 0：失败， >0 成功
 */
VBARLIB_API uint16_t vbar_gpio_get_drive_strength(uint32_t gpio);

#ifdef	__cplusplus
}
#endif
#endif
