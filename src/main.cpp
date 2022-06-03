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
class heatLamp {
  public:
    int lampPin;
    heatLamp(int c) {
        c = lampPin;
        pinMode(lampPin, INPUT);
    }
    void on() {
      digitalWrite(lampPin, HIGH);
    }
    void off() {
      digitalWrite(lampPin, LOW);
    }
};
thermistor thermistor1(A0);
heatLamp lamp1(8);
int currTemp;

void setup() {
  Serial.begin(115200);
}

void loop() {
  currTemp = thermistor1.readTemp();
  Serial.println(currTemp);
  lamp1.on();
  delay(1000);
  lamp1.off();
  delay(1000);
}