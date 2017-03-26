int RGBIndex=0;
int   turnIndex=0;
bool LEDoff=false;
void rainbowLED() {
  LEDoff=false;
  strip.WS2812SetRGB(LEDpos, RGBIndex, 0, 0);
  strip.WS2812Send();
  RGBIndex++;
  
  delay(20);
  LEDpos = (LEDpos + 1) % LED_NUM;
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
