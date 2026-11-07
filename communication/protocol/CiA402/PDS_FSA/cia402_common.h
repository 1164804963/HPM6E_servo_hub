#ifndef CIA402_COMMON_H
#define CIA402_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// 总线运行模式
#define kOd6060_ANY (-2)               //任何模式(仅用于状态字检测,无实际意义)
#define kOd6060_NULL (-1)              //无效模式
#define kOd6060_NO_MODE (0)            //空模式
#define kOd6060_PPM (1)                //轮廓位置
#define kOd6060_VL (2)                 //用作速度模式
#define kOd6060_PVM (3)                //轮廓速度  相当于位置速度模式
#define kOd6060_TPM (4)                //轮廓力矩
#define kOd6060_RESERVED (5)           //保留的模式
#define kOd6060_HM (6)                 //回零模式（非总线运行模式）
#define kOd6060_IPM (7)                //插值模式
#define kOd6060_CSP (8)                //周期同步位置
#define kOd6060_CSV (9)                //周期同步速度
#define kOd6060_CST (10)               //周期同步力矩
#define kOd6060_MIT (11)               //MIT模式



#define CIA402_SET_BIT(x, y)     (x) |= (y)          //将x的y位设置为1，示例：CIA402_SET_BIT(x, 0x10)将x的第4位置为1
#define CIA402_CLEAR_BIT(x, y)   (x) &= ~(y)         //将x的y位置置为0，示例：CIA402_CLEAR_BIT(x, 0x80)将x的第7位置为0
#define CIA402_READ_BIT(x, y)    ((x) & (y))
#define CIA402_ABS(x)            (((x) > 0) ? (x) : -(x))

#define CIA402_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#define CIA402_PI (3.14159265358979323846f)

#endif // CIA402_COMMON_H