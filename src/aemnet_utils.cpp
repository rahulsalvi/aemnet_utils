#include "aemnet_utils.h"
#include "aemnet_definitions.h"

#include "FlexCAN.h"

#include <string.h>

using aemnet_utils::fixed_point_t;
using aemnet_utils::msg_00_t;
using aemnet_utils::msg_03_t;
using aemnet_utils::msg_04_t;
using aemnet_utils::msg_08_t;
using aemnet_utils::msg_09_t;
using aemnet_utils::msg_t;

static FlexCAN       canbus(AEMNET_BAUDRATE);
static CAN_message_t recv_msg;

static msg_t           msg_buf[10];
static msg_00_t* const msg_00 = (msg_00_t*)msg_buf + 0x00;
static msg_03_t* const msg_03 = (msg_03_t*)msg_buf + 0x03;
static msg_04_t* const msg_04 = (msg_04_t*)msg_buf + 0x04;
static msg_08_t* const msg_08 = (msg_08_t*)msg_buf + 0x08;
static msg_09_t* const msg_09 = (msg_09_t*)msg_buf + 0x09;

void aemnet_utils::begin() {
    CAN_filter_t mask;
    mask.rtr = 0;
    mask.ext = 1;
    mask.id  = AEMNET_MASK;

    CAN_filter_t filter_00;
    filter_00.rtr = 0;
    filter_00.ext = 1;
    filter_00.id  = AEMNET_MSG_ID(0x00);

    CAN_filter_t filter_03;
    filter_03.rtr = 0;
    filter_03.ext = 1;
    filter_03.id  = AEMNET_MSG_ID(0x03);

    CAN_filter_t filter_04;
    filter_04.rtr = 0;
    filter_04.ext = 1;
    filter_04.id  = AEMNET_MSG_ID(0x04);

    CAN_filter_t filter_08;
    filter_08.rtr = 0;
    filter_08.ext = 1;
    filter_08.id  = AEMNET_MSG_ID(0x08);

    CAN_filter_t filter_09;
    filter_09.rtr = 0;
    filter_09.ext = 1;
    filter_09.id  = AEMNET_MSG_ID(0x09);

    canbus.setFilter(filter_00, 0);
    canbus.setFilter(filter_03, 1);
    canbus.setFilter(filter_04, 2);
    canbus.setFilter(filter_08, 3);
    canbus.setFilter(filter_09, 4);
    canbus.setFilter(filter_00, 5);
    canbus.setFilter(filter_00, 6);
    canbus.setFilter(filter_00, 7);

    recv_msg.timeout = 0;

    canbus.begin(mask);
}

uint8_t aemnet_utils::update() {
    uint8_t recv_ct;
    for (recv_ct = AEMNET_MSG_PER_UPDATE; recv_ct && canbus.read(recv_msg); recv_ct--) {
        memcpy(&msg_buf[recv_msg.id & 0xFF], recv_msg.buf, sizeof(msg_t));
    }
    return AEMNET_MSG_PER_UPDATE - recv_ct;
}

inline uint16_t swap_bytes(uint16_t a) {
    return (a >> 8) | (a << 8);
}

inline uint8_t identity8(uint8_t a) {
    return a;
}

fixed_point_t aemnet_utils::rpm() {
    return CONVERT(swap_bytes, msg_00->rpm, RPM_SCALE, RPM_OFFSET);
}

fixed_point_t aemnet_utils::throttle() {
    return CONVERT(swap_bytes, msg_00->throttle, THROTTLE_SCALE, THROTTLE_OFFSET);
}

fixed_point_t aemnet_utils::intake_temp_c() {
    return CONVERT(identity8, msg_00->intake_temp, INTAKE_TEMP_C_SCALE, INTAKE_TEMP_C_OFFSET);
}

fixed_point_t aemnet_utils::coolant_temp_c() {
    return CONVERT(identity8, msg_00->coolant_temp, COOLANT_TEMP_C_SCALE, COOLANT_TEMP_C_OFFSET);
}

fixed_point_t aemnet_utils::afr() {
    return CONVERT(identity8, msg_03->afr1, AFR_SCALE, AFR_OFFSET);
}

fixed_point_t aemnet_utils::battery_voltage() {
    return CONVERT(
        swap_bytes, msg_03->battery_voltage, BATTERY_VOLTAGE_SCALE, BATTERY_VOLTAGE_OFFSET);
}

fixed_point_t aemnet_utils::fuel_pressure() {
    return CONVERT(identity8, msg_04->fuel_pressure, FUEL_PRESSURE_SCALE, FUEL_PRESSURE_OFFSET);
}

fixed_point_t aemnet_utils::manifold_pressure() {
    return CONVERT(
        swap_bytes, msg_04->manifold_pressure, MANIFOLD_PRESSURE_SCALE, MANIFOLD_PRESSURE_OFFSET);
}

bool aemnet_utils::fuel_pump_on() {
    return msg_04->bitmap0 & FUEL_PUMP_ON_MASK;
}

bool aemnet_utils::coolant_fan_on() {
    return msg_04->bitmap0 & FAN_ON_MASK;
}
