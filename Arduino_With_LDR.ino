#include <ArduinoLowPower.h>

#define LDRpin A1
int LDRValue = 0;
int LedPin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW); 
}

void loop()
{
  LDRValue = analogRead(LDRpin);
  Serial.println(LDRValue);
  delay(200);
  // LowPower.deepSleep(200);

  if (LDRValue > 300)
  {
    digitalWrite(LedPin, LOW); 
  }
  else
  {
    digitalWrite(LedPin, HIGH);
  }
}