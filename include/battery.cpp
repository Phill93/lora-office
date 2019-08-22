#include <Arduino.h>
#include "battery.h"

#define VBATPIN A7

float getBatteryVoltage() {

    float measuredvbat = analogRead(VBATPIN);

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage
    
    return measuredvbat;

}