// Ali Toyserkani

#include <Wire.h>
#include <ADXL345.h> // courtesy of Seeed
#include "Seeed_QTouch.h"
#include "Seeed_ws2812.h"

// Global Definitions
#define SIG_PIN 12 
#define LED_NUM 5
#define trigPin 10
#define echoPin 13
#define vibPin 11


//GLOBAL VARIABLES
// --------------------------
ADXL345 adxl;
double ax, ay, az; // acceleration variables
char bData; //bluetooth data string

int maxR = 200, minR = 0; // Ultrasound boundaries
long duration, dist; // UltraS consts

int LEDpos = 0; falseTick = 0;

// ------------------

//VIBRATION MOTOR FUNCTIONS
// ---------//
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
// --------------------
// ACCELOROMETER/GYRO FUNCTIONALITY
// -----------------
void initializeAccel() {
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
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
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
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
void updateAccelerationData() {
  int x, y, z;
  adxl.readXYZ(&x, &y, &z);
  double xyz[3];
  adxl.getAcceleration(xyz);
  ax = xyz[0]; ay = xyz[1]; az = xyz[2]; //update globals
}
// ------------------------------------------------
// TOUCH SENSOR
// -------------
int getTouchNum() {
  return QTouch.touchNum();
}
// -------------------

// LED STRIP
// Depends on accel data, google maps api data, etc

// -------------
void setLEDConfig() {

}

// ------------

// ULTRASONIC
// ===================
void triggerUltraSound() {
  // US pulse signals
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calc dist (cm)
  distance = duration / 58.2;
}

// ===================

//BLUETOOTH
// --------------
void initializeBluetooth() {
  Serial1.begin(9600); // ble def. baud
  Serial1.print("AT+CLEAR"); // clear
  Serial1.print("AT+ROLE0"); //edison as slave
  Serial.print("AT+SAVE1"); // proper connection ensurance
}
void listenForBleData() { // updates bluetooth string
  if (Serial.available()) {
    bData = Serial.read();
    // Serial1.print(bData);
  }

  if (Serial1.available()) {
    bData = Serial1.read();
    // Serial.print(bData);
  }
}
// ---------------------

//INITIALIZATION
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  initializeAccel();
  initializeBluetooth();
  vibroInit();
  strip.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, OUTPUT);
  pinMode(vibPin, OUTPUT);
}


void loop() {

  updateAccelerationData();
  listenForBleData();
  triggerUltraSound();
  setLEDConfig();

}



