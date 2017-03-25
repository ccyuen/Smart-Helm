#include <Wire.h>
#include "Seeed_QTouch.h"



void vibroInit() {
  pinMode(11, OUTPUT);
  pinMode(10, HIGH);
}

void vibroOn() {
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
}

void vibroOff() {
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  vibroInit();
  vibroOn();
  delay(100);
  vibroOff();
}

void loop()
{
  int tn = QTouch.touchNum();
  if (tn>=0)
  {
    Serial.print("KEY");
    Serial.print(tn);
    Serial.println(" touched");
    vibroOn();
  }
  else vibroOff();

  
}

