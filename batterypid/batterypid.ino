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

    int output = computePID(battery_temp, 15, 2, 0.5, 2, 1, LOW, HIGH);

    digitalWrite(BAT_HEATER_PIN, output);

    battery_temp_sensor.requestTemp();
  }
}

int computePID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
  float err = setpoint - input;
  static float integral = 0, prevErr = 0;
  integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr) / dt;
  prevErr = err;
  return constrain(err * kp + integral + D * kd, minOut, maxOut);
}