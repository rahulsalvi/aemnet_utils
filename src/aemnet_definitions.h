#ifndef AEMNET_DEFINITIONS_H
#define AEMNET_DEFINITIONS_H

#include <cstdint>

// scaling factors in 0.16 format
#define RPM_SCALE 0x00006400
#define THR_SCALE 0x00000064
#define BAT_SCALE 0x00000010
#define MAP_SCALE 0x000003B6

// scaling factors in 8.16 format
#define IAT_SCALE 0x00010000
#define CLT_SCALE 0x00010000
#define AFR_SCALE 0x00000EA6
#define FPR_SCALE 0x00009484

// offsets in 16.16 format
#define RPM_OFFSET 0x00000000
#define THR_OFFSET 0x00000000
#define BAT_OFFSET 0x00000000
#define IAT_OFFSET 0x00000000
#define CLT_OFFSET 0x00000000
#define AFR_OFFSET 0x00075333
#define MAP_OFFSET 0xFFF14DD2
#define FPR_OFFSET 0x00000000

#define CONVERT(f, x, y, z) (f(x) * y + z)

#define AEMNET_BAUDRATE 500000 // kbps
#define AEMNET_MSG_SIZE 8      // bytes
#define AEMNET_MASK 0x1FFFFFFF
#define AEMNET_MSG_ID_BASE 0x01F0A000
#define AEMNET_MSG_ID(x) (AEMNET_MSG_ID_BASE + x)
#define AEMNET_MSG_PER_UPDATE 4

namespace aemnet_utils {

    typedef struct __attribute__((__packed__)) msg_t {
        uint8_t pad[AEMNET_MSG_SIZE];
    } msg_t;

    typedef struct __attribute__((__packed__)) msg_00_t {
        uint16_t rpm;
        uint16_t load;
        uint16_t thr;
        int8_t   iat;
        int8_t   clt;
    } msg_00_t;

    typedef struct __attribute__((__packed__)) msg_03_t {
        uint8_t  afr1;
        uint8_t  afr2;
        uint16_t vss;
        uint8_t  gear;
        uint8_t  ign;
        uint16_t bat;
    } msg_03_t;

    typedef struct __attribute__((__packed__)) msg_04_t {
        uint16_t map;
        uint8_t  ve;
        uint8_t  fpr;
        uint8_t  opr;
        uint8_t  afr_tgt;
        uint16_t bitmap;
    } msg_04_t;

} // namespace aemnet_utils

#endif // AEMNET_DEFINITIONS_H
