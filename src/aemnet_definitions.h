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
#define AEMNET_MSG_PER_UPDATE 8

namespace aemnet_utils {

    typedef struct __attribute__((__packed__)) msg_t {
        uint8_t pad[AEMNET_MSG_SIZE];
    } msg_t;

    typedef struct __attribute__((__packed__)) msg_00_t {
        uint16_t rpm;          // RPM
        uint16_t load;         // deprecated
        uint16_t throttle;     // percent
        int8_t   intake_temp;  // degrees C
        int8_t   coolant_temp; // degrees C
    } msg_00_t;

    typedef struct __attribute__((__packed__)) msg_03_t {
        uint8_t  afr1;            // AFR
        uint8_t  afr2;            // AFR
        uint16_t vehicle_speed;   // MPH
        uint8_t  gear;            // gear
        uint8_t  ign_timing;      // degrees
        uint16_t battery_voltage; // Volts
    } msg_03_t;

    typedef struct __attribute__((__packed__)) msg_04_t {
        uint16_t manifold_pressure; // PSI
        uint8_t  ve;                // VE
        uint8_t  fuel_pressure;     // PSIg
        uint8_t  oil_pressure;      // PSIg
        uint8_t  afr_target;        // AFR
        uint16_t bitmap;
    } msg_04_t;

    typedef struct __attribute__((__packed__)) msg_08_t {
        uint8_t  trans_temp;            // degrees C
        uint16_t spark_cut;             // RPM
        uint16_t fuel_cut;              // RPM
        uint8_t  two_step_target_fuel;  // RPM
        uint8_t  two_step_target_spark; // RPM
        uint8_t  bitmap;
    } msg_08_t;

    typedef struct __attribute__((__packed__)) msg_09_t {
        uint16_t brake_pressure;      // PSIg
        uint16_t steering_angle;      // degrees
        uint16_t launch_boost_target; // PSI
        uint8_t  pad[2];
    } msg_09_t;

} // namespace aemnet_utils

#endif // AEMNET_DEFINITIONS_H
