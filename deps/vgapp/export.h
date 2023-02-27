#ifndef __VBAR_EXPORT_H__
#define __VBAR_EXPORT_H__

/* bool类型支持 */
#include <stdbool.h>

/* 动态导出函数的声明宏 */
#ifdef VBAR_BUILD_AS_DLL
#   if defined(_WIN32) || defined(_WIN64)
#       ifdef VBAR_LIB
#           define VBARLIB_API __declspec(dllexport)
#       else
#           define VBARLIB_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__) && defined(__linux__)
#       ifdef VBAR_LIB
#           define VBARLIB_API __attribute__((visibility("default")))
#       else
#           define VBARLIB_API
#       endif
#   else
#       error "不支持的操作系统"
#   endif
#else
#define VBARLIB_API
#endif /* VBAR_BUILD_AS_DLL */

#ifdef __GNUC__
#define DECLARE_DEPRECATED_ATTR __attribute__((deprecated))
#elif defined(_WIN32) || defined(_WIN64)
#define DECLARE_DEPRECATED_ATTR __declspec(deprecated)
#else
#define DECLARE_DEPRECATED_ATTR
#endif
#endif /* __VBAR_EXPORT_H__ */
