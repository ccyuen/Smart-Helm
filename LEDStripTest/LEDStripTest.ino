#include <Wire.h>
#include "Seeed_ws2812.h"

#define SIG_PIN 12   //LED strip signal pin
#define LED_NUM 5  //LED strip led number

WS2812 strip = WS2812(LED_NUM, SIG_PIN);

void setup() 
{
  strip.begin();
  Serial.begin(9600);
}

int pos = 0;

void loop() {

  strip.WS2812SetRGB(pos,255,0,0);
  strip.WS2812Send();
  delay(100);

  strip.WS2812SetRGB(pos,0,0,0);
  strip.WS2812Send();
  delay(100);

  pos = (pos+1) % LED_NUM;
  
}




