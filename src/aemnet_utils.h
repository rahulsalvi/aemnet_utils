#ifndef AEMNET_UTILS_H
#define AEMNET_UTILS_H

#include <cstdint>

namespace aemnet_utils {

    typedef int32_t fixed_point_t; // 16.16 format

    void begin();
    void update();

    fixed_point_t rpm();
    fixed_point_t throttle();
    fixed_point_t intake_temp_c();
    fixed_point_t coolant_temp_c();
    fixed_point_t afr();
    fixed_point_t battery_voltage();
    fixed_point_t fuel_pressure();
    fixed_point_t manifold_pressure();

} // namespace aemnet_utils

#endif // AEMNET_UTILS_H
