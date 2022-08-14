#include <Arduino.h>

//Main class for a temperature control device. All temperatures are in Degrees Celcius (°C).
class tempController {
  public:
    int lampPin;
    int fanPin;
    int themistorPin;
    int thermistorPin;
    int volts;
    float temp;
    int fanSpeed;

    int startTemp;
    int endTemp;
    int daysAmount;
    unsigned long decreasePeriodMillis;
    unsigned long millisPassed;
    const int dayLength = 86400;
    tempController(int a, int b, int c, int d, int e, int f) {
        lampPin = a;
        fanPin = b;
        themistorPin = c;
        startTemp = d;
        endTemp = e;
        daysAmount = f;
        decreasePeriodMillis = daysAmount * 86400 * 1000;
        pinMode(fanPin, OUTPUT);
        pinMode(thermistorPin, INPUT);
        pinMode(lampPin, OUTPUT);
        
    }
    //Turns the lamp on until lampOff() is called.
    void heaterOn() {
      digitalWrite(lampPin, HIGH);
    }
    //Turns off the lamp.
    void heaterOff() {
      digitalWrite(lampPin, LOW);
    }
    //Turns the fan on until fanOff() is called.
    void fanOn(int duration, int fanSpeed) {
      analogWrite(fanPin, fanSpeed);
    }
    //Turns the fan off.
    void fanOff() {
      analogWrite(fanPin, 0);
    }
    //Reads then returns the current temperature that the thermistor is reading.
    int readTemp() {
        volts = analogRead(thermistorPin);
        temp = 200 - 68 * log10(1000-volts);
        return round(temp);
    }
    int targetTemp(int currtime) {
      float outputTemp = startTemp-endTemp*(currtime/decreasePeriodMillis);
      return round(outputTemp);
    }
    /*Increase the temp by a relative amount. Example: If you called increaseBy(3) and the envirment temp was 24C,
   *the controller will increase the enviroment temp until it reaches 27C. */
    void increaseTempBy(int increaseAmount) {
      int targetTemp = this->readTemp() + increaseAmount;
      while(targetTemp < this->readTemp()) {
        this->heaterOn();
      }
      this->heaterOff();
    }
};

tempController enviroment(13, 7, A0, 40, 20, 5);
void setup() {

}

void loop() {
  int targTemp = enviroment.targetTemp(millis());
  if (enviroment.readTemp() < targTemp){
    enviroment.increaseTempBy(targTemp - enviroment.readTemp());
  }

}