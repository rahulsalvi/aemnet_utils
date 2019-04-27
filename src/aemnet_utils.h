#ifndef AEMNET_UTILS_H
#define AEMNET_UTILS_H

#include <cstdint>

namespace aemnet_utils {

    typedef int32_t fixed_point_t; // 16.16 format

    void begin();
    void update();

    fixed_point_t rpm();
    fixed_point_t thr();
    fixed_point_t iat();
    fixed_point_t clt();
    fixed_point_t afr();
    fixed_point_t bat();
    fixed_point_t fpr();

} // namespace aemnet_utils

#endif // AEMNET_UTILS_H
