#include <Arduino.h>

class thermistor {
  public:
    int thermistorPin;
    int volts;
    int temp;
    thermistor(int i) {
      thermistorPin = i;
      pinMode(thermistorPin, INPUT);

    }
    int readTemp() {
        volts = analogRead(thermistorPin);
        temp = 200 - 68 * log10(1000-volts);
        return temp;
    }
};

void setup() {
  
}

void loop() {
  
}