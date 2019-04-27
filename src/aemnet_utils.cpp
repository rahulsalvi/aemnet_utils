#include "aemnet_utils.h"
#include "aemnet_definitions.h"

#include "FlexCAN.h"

#include <cstring>

static FlexCAN       canbus(AEMNET_BAUDRATE);
static CAN_message_t msg;

static aemnet_utils::msg_000_t msg_000;
static aemnet_utils::msg_003_t msg_003;
static aemnet_utils::msg_004_t msg_004;

void aemnet_utils::begin() {
    CAN_filter_t mask;
    mask.rtr = 0;
    mask.ext = 1;
    mask.id  = AEMNET_MASK;

    CAN_filter_t filter_000;
    filter_000.rtr = 0;
    filter_000.ext = 1;
    filter_000.id  = AEMNET_FILTER_000;

    CAN_filter_t filter_003;
    filter_003.rtr = 0;
    filter_003.ext = 1;
    filter_003.id  = AEMNET_FILTER_003;

    CAN_filter_t filter_004;
    filter_004.rtr = 0;
    filter_004.ext = 1;
    filter_004.id  = AEMNET_FILTER_004;

    canbus.setFilter(filter_000, 0);
    canbus.setFilter(filter_003, 1);
    canbus.setFilter(filter_004, 2);
    canbus.setFilter(filter_000, 3);
    canbus.setFilter(filter_000, 4);
    canbus.setFilter(filter_000, 5);
    canbus.setFilter(filter_000, 6);
    canbus.setFilter(filter_000, 7);

    msg.timeout = 0;

    canbus.begin(mask);
}

void aemnet_utils::update() {
    int recv_ct = 4;
    while (recv_ct && canbus.read(msg)) {
        switch (msg.id) {
            case AEMNET_FILTER_000:
                std::memcpy((void*)&msg_000, msg.buf, sizeof(msg_000_t));
                break;
            case AEMNET_FILTER_003:
                std::memcpy((void*)&msg_003, msg.buf, sizeof(msg_003_t));
                break;
            case AEMNET_FILTER_004:
                std::memcpy((void*)&msg_004, msg.buf, sizeof(msg_004_t));
                break;
            default:
                break;
        }
        recv_ct--;
    }
}

uint16_t swap_bytes(uint16_t a) {
    return (a >> 8) | (a << 8);
}

uint8_t identity8(uint8_t a) {
    return a;
}

aemnet_utils::fixed_point_t aemnet_utils::rpm() {
    return CONVERT(swap_bytes, msg_000.rpm, RPM_SCALE, RPM_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::thr() {
    return CONVERT(swap_bytes, msg_000.thr, THR_SCALE, THR_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::iat() {
    return CONVERT(identity8, msg_000.iat, IAT_SCALE, IAT_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::clt() {
    return CONVERT(identity8, msg_000.clt, CLT_SCALE, CLT_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::afr() {
    return CONVERT(identity8, msg_003.afr1, AFR_SCALE, AFR_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::bat() {
    return CONVERT(swap_bytes, msg_003.bat, BAT_SCALE, BAT_OFFSET);
}

aemnet_utils::fixed_point_t aemnet_utils::fpr() {
    return CONVERT(identity8, msg_004.fpr, FPR_SCALE, FPR_OFFSET);
}
