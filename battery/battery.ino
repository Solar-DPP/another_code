#include <DS_raw.h>
#include <microDS18B20.h>
#include <microOneWire.h>

#include <microDS18B20.h>

#define BAT_TEMP_PIN 1
#define BAT_HEATER_PIN 2

MicroDS18B20<BAT_TEMP_PIN> battery_temp_sensor;

void setup() {
  pinMode(BAT_HEATER_PIN, OUTPUT);  
}

void loop() {
  static unsigned long tmr = 0;

  if (millis() - tmr > 1000) {
    tmr = millis();

    float battery_temp = battery_temp_sensor.getTemp();

  }
}