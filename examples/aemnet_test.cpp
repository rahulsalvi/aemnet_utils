#include "WProgram.h"
#include "aemnet_utils.h"

using aemnet_utils::fixed_point_t;

inline float fixed_to_float(fixed_point_t a);

void setup() {
    Serial.begin(115200);
    aemnet_utils::begin();
}

void loop() {
    aemnet_utils::update();

    Serial.println("------------------------------");
    Serial.print("RPM: ");
    Serial.println(fixed_to_float(aemnet_utils::rpm()));
    Serial.print("THR: ");
    Serial.println(fixed_to_float(aemnet_utils::thr()));
    Serial.print("IAT: ");
    Serial.println(fixed_to_float(aemnet_utils::iat()));
    Serial.print("CLT: ");
    Serial.println(fixed_to_float(aemnet_utils::clt()));
    Serial.print("AFR: ");
    Serial.println(fixed_to_float(aemnet_utils::afr()));
    Serial.print("BAT: ");
    Serial.println(fixed_to_float(aemnet_utils::bat()));
    Serial.print("FPR: ");
    Serial.println(fixed_to_float(aemnet_utils::fpr()));
    Serial.println("------------------------------");

    delay(100);
}

inline float fixed_to_float(fixed_point_t a) {
    return ((float)a / (float)(1 << 16));
}

extern "C" int main(void) {
    setup();
    while (1) { loop(); }
}
