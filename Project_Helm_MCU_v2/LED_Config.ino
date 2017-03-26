int RGBIndex=0;
int   turnIndex=0;
bool LEDoff=false;


// The value will quickly become too large for an int to store
unsigned long previousMillisLN = 0;        // will store last time LED was updated
int ledStateLN = LOW; 
// constants won't change :
const long intervalLN = 100;           // interval at which to blink (milliseconds)
const long intervalLNoff = 50;           // interval at which to blink (milliseconds)

void  LED_Normal() {
  unsigned long currentMillisLN = millis();
  if ((ledStateLN&&currentMillisLN - previousMillisLN >= intervalLN)||(!ledStateLN&&currentMillisLN - previousMillisLN >= intervalLNoff)) {
    // save the last time you blinked the LED
    previousMillisLN = currentMillisLN;

    // if the LED is off turn it on and vice-versa:
    if (ledStateLN == LOW) {
      ledStateLN = HIGH;
    } else {
      ledStateLN = LOW;
    }

    if (ledStateLN) {
        LEDoff=false;//foo bar
        for (int i = 0; i < 5; i++) {
          LED(4-i, 255 * (i == LEDpos), 0, 0);
          LED(5+i, 255 * (i == LEDpos), 0, 0);
      }

    } else {
        LEDpos = (LEDpos + 1) % (LED_NUM-4);
    }
  }
}


unsigned long previousMillisRB = 0;        // will store last time LED was updated
int ledStateRB = LOW; 
// constants won't change :
const long intervalRB = 20;           // interval at which to blink (milliseconds)
const long intervalRBoff = 20;           // interval at which to blink (milliseconds)
bool increase=true;
void rainbowLED() {
  unsigned long currentMillisRB = millis();
  if ((ledStateRB&&currentMillisRB - previousMillisRB >= intervalRB)||(!ledStateRB&&currentMillisRB - previousMillisRB >= intervalRBoff)) {
    // save the last time you blinked the LED
    previousMillisRB = currentMillisRB;

    // if the LED is off turn it on and vice-versa:
    if (ledStateRB == LOW) {
      ledStateRB = HIGH;
    } else {
      ledStateRB = LOW;
    }

    if (ledStateRB) {
        LEDoff=false;//foo bar
        for (int i = 0; i < 10; i++) {
            strip.WS2812SetRGB(i, 255*sin(RGBIndex*30), 255*sin(RGBIndex*60), 255*sin(RGBIndex*90));
            strip.WS2812Send();
            if(increase)
            RGBIndex++;
            else
              RGBIndex--;
            if(RGBIndex>=255){
              increase=false;
            }else if(RGBIndex<=0){
              increase=true;
            }
      }

    } else {
        LEDpos = (LEDpos + 1) % (LED_NUM);
    }
  }

}

void nightMode() { // spliting pattern
  LEDoff=false;
  for (int i = 0; i < 5; i++) {
      LED(4-i, 255 * (i == LEDpos), 0, 0);
      LED(5+i, 255 * (i == LEDpos), 0, 0);
  }
  delay(20);
  LEDpos = (LEDpos + 1) % LED_NUM;
}

void turningLeft() {
  LEDoff=false;
  for (int i = 4; i < 5 + turnIndex; i++) {
      strip.WS2812SetRGB(i, 226, 88, 34); // flaming orange
      strip.WS2812Send(); 
  }
  if (turnIndex > 5) {
    turnIndex = 0;
    turnLEDsOff();
    delay(800);
  }
  turnIndex++; // make sure to 0 turnIndex properly
  delay(40);

}

void turningRight() {
  LEDoff=false;
  for (int i = 5; i > 4 - turnIndex; i--) {
      LED(i, 226, 88, 34); // flaming orange 
  }
  if (turnIndex == 5) {
    turnIndex = 0;
    delay(800);
    turnLEDsOff();
    
  }
  turnIndex++; // make sure to 0 turnIndex properly
  delay(40);
  
}

void stopping() {
  LEDoff=false;
  for (int i = 0; i < LED_NUM; i++) {
      LED(i, 255, 0, 0);
  }
}

void normalDriving() {
  LEDoff=false;
  for (int i = 0; i < LED_NUM; i++) // could have used a function called power all LEDs
    LED(i, 0, 255, 0);      // could change to green colour as well
}

void turnLEDsOff() {
  if(!LEDoff){
  for (int i = 0; i < LED_NUM; i++) {
      LED(i, 0,0,0);
  }
  }
  LEDoff=true;
}

void LED(int index, int r, int g, int b) {
  strip.WS2812SetRGB(index,r,g,b);
  strip.WS2812Send();
}
