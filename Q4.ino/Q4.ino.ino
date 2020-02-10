#include "OneWire.h"
#include "DallasTemperature.h"

OneWire oneWire(23);
DallasTemperature tempSensor(&oneWire);
const int ledPin = 19;
const int redLedPin = 18;
const int tempDay = 25;
const int tempNight = 25  ;
const int luminosityDay = 100 ;
int sensorValue;


void setup(void){

  Serial.begin(9600);
  delay(1000);

  pinMode(ledPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  
  tempSensor.begin();
}

void loop(void){
  float t;
  tempSensor.requestTemperaturesByIndex(0);

  t = tempSensor.getTempCByIndex(0);

  Serial.print("Temperature:");
  Serial.print(t);
  Serial.print("C\n");

  sensorValue = analogRead(A0);
  Serial.print("Intensité lumineuse:");
  Serial.print(sensorValue, DEC);

  if(sensorValue>luminosityDay) {
      if(t < tempDay) {
          digitalWrite(redLedPin, HIGH);
          digitalWrite(ledPin, LOW);
      } else {
          digitalWrite(redLedPin, LOW);
          digitalWrite(ledPin, HIGH);
      }
  } else {
      if(t > tempNight) {
          digitalWrite(redLedPin, LOW);
          digitalWrite(ledPin, HIGH);
      } else {
          digitalWrite(redLedPin, HIGH);
          digitalWrite(ledPin, LOW);
      }
  }
  
  delay(1000);
  Serial.print('\n');
}
