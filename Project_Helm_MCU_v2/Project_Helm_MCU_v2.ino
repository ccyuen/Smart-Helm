#include <Wire.h> //Edison Lib
#include <ADXL345.h> // Gyro Lib
#include "Seeed_ws2812.h"
#include "Seeed_QTouch.h"

// Def PINS
#define trigPin 10
#define echoPin 13
#define vibPin 11
#define SIG_PIN 12
//Global Defs
#define LED_NUM 10
ADXL345 adxl;
WS2812 strip = WS2812(LED_NUM, SIG_PIN);
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

int LEDpos = 0;
//Status
bool goSleep = false;
int goSleepCount = 0;
const int SLEEPING_THRESHOLD = 4;

bool slowState = false;
int slowTicks = 0;
const int SLOW_TICKS = 4;

int keyT;
bool key0 , key1, key2;

int distWarningTick = 0;
bool  distWarning = false;
const int DIST_WARN_TICK_THRESH = 10;

int ticks = 1;
// --------------------
// SENSOR/LED FUNCTIONALITY
// -----------------
void initializeOTHER() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode( vibPin, OUTPUT);
}

// --------------------
// ACCELOROMETER/GYRO FUNCTIONALITY
// -----------------
void initializeAccel() {
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(30); //62.5mg per increment
  adxl.setInactivityThreshold(10); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?

  //look of activity movement on this axes - 1 == on; 0 == off
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);

  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);

  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(30); //62.5mg per increment
  adxl.setTapDuration(30); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment

  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(40); //(20 - 70) recommended - 5ms per increment

  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );

  //register interrupt actions - 1 == on; 0 == off
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}

void Trigger_Acceleration() {
  //getInterruptSource clears all triggered actions after returning value
  //so do not call again until you need to recheck for triggered actions
  byte interrupts = adxl.getInterruptSource();

  // freefall
  if (adxl.triggered(interrupts, ADXL345_FREE_FALL)) {
    Serial.println("freefall");
    //add code here to do when freefall is sensed

  }

  //inactivity
  if (adxl.triggered(interrupts, ADXL345_INACTIVITY)) {
    Serial.println("inactivity");
    //add code here to do when inactivity is sensed
    goSleepCount++;
    if (goSleepCount >= SLEEPING_THRESHOLD && !goSleep) {
      goSleep = true;
    }
  }

  //activity
  if (adxl.triggered(interrupts, ADXL345_ACTIVITY)) {
    Serial.println("activity");
    //add code here to do when inactivity is sensed
    if (goSleep) {
      goSleepCount = 0;
      goSleep = false;
    }
  }

  //double tap
  if (adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)) {
    Serial.println("double tap");
    slowState = true;
    //add code here to do when a 2X tap is sensed
  }

  //tap
  if (adxl.triggered(interrupts, ADXL345_SINGLE_TAP)) {
    Serial.println("tap");
    //add code here to do when a tap is sensed
  }

}

void Trigger_UltraSound() {
  // US pulse signals
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calc dist (cm)
  distance = duration / 58.2;

  //Action
  if (distance >= maximumRange || distance <= minimumRange) {
    //Serial.println("-1");
    distWarningTick = 0;
  } else {
    // Serial.println(distance);
    distWarningTick++;
  }

  if ( distWarningTick > DIST_WARN_TICK_THRESH) {
    distWarning = true;
  } else {
    distWarning = false;
  }

}



void action() {

  if (distWarning) {
    digitalWrite(trigPin, HIGH);
    digitalWrite(vibPin, HIGH);
    delay(100);
    digitalWrite(trigPin, LOW);
    digitalWrite(vibPin, LOW);
    delay(30);
  }
  if (slowState && !distWarning) {
    //temp
    if (slowTicks > SLOW_TICKS) {
      slowTicks = 0;
      slowState = false;
    } else
      slowTicks++;
      for (int i = 0; i < LED_NUM; i++) {
        strip.WS2812SetRGB(i, 255, 0, 0);
        strip.WS2812Send();
      }
      delay(200);
      for (int i = 0; i < LED_NUM; i++) {
        strip.WS2812SetRGB(i, 0, 0, 0);
        strip.WS2812Send();
      }
      delay(100);
  } else {
         
    //rainbowLED();
    //nightMode();
    //turningLeft();
    //stopping();
    //if (QTouch.touchNum() == 1)
    //  turningRight();
    // normalDriving();
//    turnLEDsOff();
    
    if (key0) turningRight();
    else if (key1) rainbowLED();
    else if (key2) nightMode();
    else  LED_Normal();
  }

}

void checkTouch() {

  keyT = QTouch.touchNum();

  if (keyT == 0) {
    key0 = true;
    key1 = false;
    key2 = false;
  } else if (keyT == 1) {
    key1 = true;
    key0 = false; key2 = false;
  }
  else if (keyT == 2) {
    key2 = true;
    key0 = false; key1 = false;
  }

}

//INITIALIZATION
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initializeAccel();
  initializeOTHER();
  strip.begin();
}

void loop() {

  Trigger_Acceleration();
  if (!goSleep) {
     Serial.println(QTouch.touchNum());
    checkTouch();
    Trigger_UltraSound();
    action();
  } else {
    turnLEDsOff();
  }

}



