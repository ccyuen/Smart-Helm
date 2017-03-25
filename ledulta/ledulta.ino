#include <Wire.h>
#include "Seeed_ws2812.h"
#define echoPin 10 // Echo Pin
#define trigPin 11 // Trigger Pin

#define SIG_PIN 12   //LED strip signal pin
#define LED_NUM 5  //LED strip led number

WS2812 strip = WS2812(LED_NUM, SIG_PIN);

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
void setup() 
{
  strip.begin();
  Serial.begin(9600);
   pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}

int pos = 0;
int falseTick=0;

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;


  
 if (distance >= maximumRange || distance <= minimumRange){
   falseTick=0;
 }else{
    falseTick++;
 }

  
if(falseTick>4){
    for(int i=0;i<5;i++){
    strip.WS2812SetRGB(i,0,0,255);
    strip.WS2812Send();
    }
    delay(100);
}else{
  strip.WS2812SetRGB(pos,255,0,0);
  strip.WS2812Send();
  delay(100);

  strip.WS2812SetRGB(pos,0,0,0);
  strip.WS2812Send();
  delay(100);
}

  pos = (pos+1) % LED_NUM;
  
}




