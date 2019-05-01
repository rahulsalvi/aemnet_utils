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
    Serial.println(fixed_to_float(aemnet_utils::throttle()));
    Serial.print("IAT: ");
    Serial.println(fixed_to_float(aemnet_utils::intake_temp_c()));
    Serial.print("CLT: ");
    Serial.println(fixed_to_float(aemnet_utils::coolant_temp_c()));
    Serial.print("AFR: ");
    Serial.println(fixed_to_float(aemnet_utils::afr()));
    Serial.print("BAT: ");
    Serial.println(fixed_to_float(aemnet_utils::battery_voltage()));
    Serial.print("FPR: ");
    Serial.println(fixed_to_float(aemnet_utils::fuel_pressure()));
    Serial.println("------------------------------");

    delay(100);
}

inline float fixed_to_float(fixed_point_t a) {
    return a / 65536.0;
}

extern "C" int main(void) {
    setup();
    while (1) { loop(); }
}
