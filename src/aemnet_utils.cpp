#include "aemnet_utils.h"
#include "aemnet_definitions.h"

#include "FlexCAN.h"

#include <cstring>

using aemnet_utils::msg_00_t;
using aemnet_utils::msg_03_t;
using aemnet_utils::msg_04_t;
using aemnet_utils::msg_t;

static FlexCAN       canbus(AEMNET_BAUDRATE);
static CAN_message_t recv_msg;

static msg_t           msg_buf[5];
static msg_00_t* const msg_00 = (msg_00_t*)msg_buf + 0x00;
static msg_03_t* const msg_03 = (msg_03_t*)msg_buf + 0x03;
static msg_04_t* const msg_04 = (msg_04_t*)msg_buf + 0x04;

void aemnet_utils::begin() {
    CAN_filter_t mask;
    mask.rtr = 0;
    mask.ext = 1;
    mask.id  = AEMNET_MASK;

    CAN_filter_t filter_000;
    filter_000.rtr = 0;
    filter_000.ext = 1;
    filter_000.id  = AEMNET_MSG_ID(0x00);

    CAN_filter_t filter_003;
    filter_003.rtr = 0;
    filter_003.ext = 1;
    filter_003.id  = AEMNET_MSG_ID(0x03);

    CAN_filter_t filter_004;
    filter_004.rtr = 0;
    filter_004.ext = 1;
    filter_004.id  = AEMNET_MSG_ID(0x04);

    canbus.setFilter(filter_000, 0);
    canbus.setFilter(filter_003, 1);
    canbus.setFilter(filter_004, 2);
    canbus.setFilter(filter_000, 3);
    canbus.setFilter(filter_000, 4);
    canbus.setFilter(filter_000, 5);
    canbus.setFilter(filter_000, 6);
    canbus.setFilter(filter_000, 7);

    recv_msg.timeout = 0;

    canbus.begin(mask);
}

void aemnet_utils::update() {
    int recv_ct = AEMNET_MSG_PER_UPDATE;
    while (recv_ct && canbus.read(recv_msg)) {
        std::memcpy(&msg_buf[recv_msg.id & 0xFF], recv_msg.buf, sizeof(msg_t));
        recv_ct--;
    }
}

inline uint16_t swap_bytes(uint16_t a) {
    return (a >> 8) | (a << 8);
}

inline uint8_t identity8(uint8_t a) {
    return a;
}

aemnet_utils::fixed_point_t aemnet_utils::rpm() {
    return CONVERT(swap_bytes, msg_00->rpm, RPM_SCALE, RPM_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::thr() {
    return CONVERT(swap_bytes, msg_00->thr, THR_SCALE, THR_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::iat() {
    return CONVERT(identity8, msg_00->iat, IAT_SCALE, IAT_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::clt() {
    return CONVERT(identity8, msg_00->clt, CLT_SCALE, CLT_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::afr() {
    return CONVERT(identity8, msg_03->afr1, AFR_SCALE, AFR_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::bat() {
    return CONVERT(swap_bytes, msg_03->bat, BAT_SCALE, BAT_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::fpr() {
    return CONVERT(identity8, msg_04->fpr, FPR_SCALE, FPR_OFFSET);
}
