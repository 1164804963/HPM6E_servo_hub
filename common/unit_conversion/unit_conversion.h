#ifndef UNIT_CONVERSION_H
#define UNIT_CONVERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define UNIT_CONVERSION_NUM 6
typedef enum
{
    E_POSITION_UNIT = 0,
    E_VELOCITY_UNIT,
    E_ACCELERATION_UNIT,
    E_TORQUE_UNIT,
    E_FORCE_UNIT,

    E_GEAR_RATIO,

    E_UNIT_CONVERSION_MAX = 0xFF

} UNIT_CONVERSION_TYPE;


void set_numerator(uint32_t val, UNIT_CONVERSION_TYPE type);
void set_denominator(uint32_t val, UNIT_CONVERSION_TYPE type);

int conver_num_div_den(int64_t *src, int64_t *dec, UNIT_CONVERSION_TYPE type);
int conver_den_div_num(int64_t *src, int64_t *dec, UNIT_CONVERSION_TYPE type);

#ifdef __cplusplus
}
#endif

#endif //UNIT_CONVERSION_H
