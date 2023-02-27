#include <stdio.h>
#include "gpio.h"


/**
 * @brief vbar_gpio_init gpio 初始化
 *
 * @return 0：成功， -1：失败
 */
VBARLIB_API int vbar_gpio_init(void)
{
    printf("vbar_gpio_init\n");
    return 1;
}

/**
 * @brief vbar_gpio_exit 释放gpio资源
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_exit(void)
{
    printf("vbar_gpio_exit\n");
}
/**
 * @brief vbar_gpio_request 申请gpio
 *
 * @param gpio gpio值
 *
 * @return 0：成功，<0：失败
 */
VBARLIB_API int vbar_gpio_request(uint32_t gpio)
{
    printf("vbar_gpio_request\n");
    return 1;
}

/**
 * @brief vbar_gpio_free 释放指定gpio
 *
 * @param gpio gpio值
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_free(uint32_t gpio)
{
    printf("vbar_gpio_free\n");
}

/**
 * @brief vbar_gpio_set_func 设置指定gpio功能
 *
 * @param gpio  gpio值
 * @param func  功能类型
 *
 * @return 无
 */
void vbar_gpio_set_func(uint32_t gpio, enum gpio_function func)
{
    printf("vbar_gpio_set_func\n");
}

/**
 * @brief vbar_gpio_set_pull 设置指定gpio上拉状态
 *
 * @param gpio  gpio值
 * @param state 上拉状态
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_pull_state(uint32_t gpio, uint32_t state)
{
    printf("vbar_gpio_set_pull_state\n");
}

/**
 * @brief vbar_gpio_get_pull 获取指定gpio上拉状态
 *
 * @param gpio
 *
 * @return <0：失败，>=0 成功
 */
VBARLIB_API int vbar_gpio_get_pull_state(uint32_t gpio)
{
    printf("vbar_gpio_get_pull_state\n");
    return 1;
}

/**
 * @brief vbar_gpio_set_value 设置指定gpio的值
 *
 * @param gpio    gpio值
 * @param value   要设置的值0或1
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_value(uint32_t gpio, uint8_t value)
{
    printf("vbar_gpio_set_value\n");
}

/**
 * @brief vbar_gpio_get_value 获取指定gpio值
 *
 * @param gpio   gpio值
 *
 * @return <0：失败，>=0：成功
 */
VBARLIB_API int vbar_gpio_get_value(uint32_t gpio)
{
    printf("vbar_gpio_get_value\n");
    return 1;
}

/**
 * @brief vbar_gpio_set_drive_strength 设置指定gpio的驱动能力
 *
 * @param gpio     gpio值
 * @param strength 驱动能力值
 *
 * @return 无
 */
VBARLIB_API void vbar_gpio_set_drive_strength(uint32_t gpio, uint16_t strength)
{
    printf("vbar_gpio_set_drive_strength\n");
}

/**
 * @brief vbar_gpio_get_drive_strength 获取指定gpio的驱动能力
 *
 * @param gpio    gpio值
 *
 * @return 0：失败， >0 成功
 */
VBARLIB_API uint16_t vbar_gpio_get_drive_strength(uint32_t gpio)
{
    printf("vbar_gpio_get_drive_strength\n");
    return 1;
}