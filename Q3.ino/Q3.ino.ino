#include "OneWire.h"
#include "DallasTemperature.h"

OneWire oneWire(23);
DallasTemperature tempSensor(&oneWire);
const int ledPin = 19;
const int redLedPin = 18;
int sensorValue;

void setup(void){



  Serial.begin(9600);

  delay(2*1000);

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

  Serial.print('\n');
  delay(1000);

  digitalWrite(ledPin, HIGH);
  delay(1*1000);
  digitalWrite(ledPin, LOW);

  digitalWrite(redLedPin, HIGH);
  delay(1*1000);
  digitalWrite(redLedPin, LOW);

  
}
