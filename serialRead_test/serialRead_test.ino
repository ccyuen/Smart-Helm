#include <SoftwareSerial.h>
//#include <avr/interrupt.h>

const int RX_PIN = 2;
const int TX_PIN = 3;
SoftwareSerial serial(RX_PIN, TX_PIN);
char commandChar;

void setup ()
{
  serial.begin (9600);
  randomSeed(analogRead(0));
}

void loop ()
{
  if(serial.available())
  {
    commandChar = serial.read();
    switch(commandChar)
    {
      case '*':
      serial.print(random(1000) + "#");
      break;
    }
  }
}

