#include <Arduino.h>

class day {
  public:
  /*This is a relative temp increase. So if you called increaseBy(3) and the envirment temp was 24C,
   *the controller will increase the enviroment temp until it reaches 27C.
   */
      
    void increaseBy(int increaseAmount) {
    }
  private:
    const int dayLength = 86400;
    int daysPassed;
};
class fan {
  public:
    int fanPin;
    fan(int f) {
      fanPin = f; 
      pinMode(fanPin, OUTPUT);
    }
    void fanOn(int duration, int fanSpeed) {
      analogWrite(fanPin, fanSpeed);
    }
    void fanOff() {
      analogWrite(fanPin, 0);
    }
};
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
heatLamp lamp1(13);
int currTemp;
  int potOutput;

void setup() {
  Serial.begin(115200);
  pinMode(7, OUTPUT);

}

void loop() {
}