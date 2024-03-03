#include <elapsedMillis.h>

const int lm35Pin = A0;     
const int ledPin = 13;     

const int lowTempThreshold = 30;  
const int highTempThreshold = 30; 

elapsedMillis elapsedMillisSinceBlink;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int temperature = readTemperature();
  if (temperature < lowTempThreshold) {
    blinkLED(250);
  } else if (temperature > highTempThreshold) {
    blinkLED(500);
  } else {
    // Temperature within the desired range, turn off LED
    digitalWrite(ledPin, LOW);
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

int readTemperature() {
  int sensorValue = analogRead(lm35Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  int temperature = (voltage - 0.5) * 100;

  return temperature;
}

void blinkLED(int interval) {
  if (elapsedMillisSinceBlink >= interval) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    elapsedMillisSinceBlink = 0; // Reset elapsed time
  }
}
