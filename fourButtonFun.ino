/* Learn to use pushbutton (button switch) with Arduino - Tutorial
   More info and circuit schematic: http://www.ardumotive.com/arduino-tutorials/category/button
   Dev: Michalis Vasilakis / Date: 19/10/2014  
   UPDATED 2/6/2016 - LED to Arduino pin 3 and button to Arduino pin 4*/


//Constants
const int buttonPinRed   = 7;     
const int buttonPinGreen = 8;
const int buttonPinWhite = 9;
const int buttonPinBlue  = 10;

const int fadeSpeed = 1;

#include <Adafruit_NeoPixel.h>
#define PIN 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

//Variables
//int buttonState = 0;
int lastStateRed   = 0;
int lastStateGreen = 0;
int lastStateWhite = 0;
int lastStateBlue = 0;
// int buttonStateRed   = 0;
// int buttonStateGreen = 0;
// int buttonStateWhite = 0;
// int buttonStateBlue  = 0;

//RGB stuff
int baseR;
int baseG;
int baseB;
int red = 0;
int green = 0;
int blue = 0 ;
int r;
int g;
int b;
int heldTimeRed = 0;
int sinAmp    = 1;
float period1 = .1;

uint8_t baseColors[][3] = {{232, 50, 255},   // purple
                        {250, 100, 20},   // yellow 
                        {30, 30, 255},   // blue
                        {237,159,176},    // pink
                        {255, 0, 0},      // red
                        {70, 87,229},     // Dark blue
                        {50,255,50},
                        {0,255,0},
                        {255,0,0},
                        {0,0,255},
                        {255,0,220},
                                  };     // Lt Green
#define chosenColor sizeof(baseColors) / 3


void setup() {
  //Input or output?
  pinMode(buttonPinRed,   INPUT);
  pinMode(buttonPinGreen, INPUT);
  pinMode(buttonPinWhite, INPUT);
  pinMode(buttonPinBlue,  INPUT);
  Serial.begin(9600);
  delay(500);
  baseR = 0;
  baseG = 0;
  baseB = 0;
  r = 0;
  g = 0;
  b = 0;
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
  //delay(1000);

}

void loop(){
  // delay(10);
  

  //Read button state (pressed or not pressed?)

  int buttonStateRed   = digitalRead(buttonPinRed);
  int buttonStateGreen = digitalRead(buttonPinGreen);
  int buttonStateWhite = digitalRead(buttonPinWhite);
  int buttonStateBlue  = digitalRead(buttonPinBlue);
  
  
  // Red Button
  // For sin wave flashing
  int indy = random(chosenColor);
  int red = baseColors[indy][0];
  int green = baseColors[indy][1];
  int blue = baseColors[indy][2];
  
  
  if (buttonStateRed == 1) {
    heldTimeRed++;}
  else {
    heldTimeRed = 0;
  }
  
  if (heldTimeRed == 0){
    r -= fadeSpeed;
    g -= fadeSpeed;
    b -= fadeSpeed;
  }

  //When thresh is exceeded, light up  
  else if (heldTimeRed == 1 ){
    baseR = red;
    baseG = green;
    baseB = blue;
    r = map(red,   0, 255, 0, baseR);
    g = map(green, 0, 255, 0, baseG);
    b = map(blue,  0, 255, 0, baseB);

  }
  
  
  else if (heldTimeRed > 200 ){// && heldTime < 400){
    
    r =  (baseR-20) + (sin(period1 *  heldTimeRed)*(sinAmp*baseR));
    g =  (baseG-20) + (sin(period1 *  heldTimeRed)*(sinAmp*baseG));
    b =  (baseB-20) + (sin(period1 *  heldTimeRed)*(sinAmp*baseB));
    

  }
  
  Serial.print(r);
  Serial.print("\t");  
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print("\n");
  
  if (r <= 0){ r = 0;}
  if (r >= 255){ r = 255;}
  if (g <= 0){g = 0;}
  if (g >= 255){ g = 255;}
  if (b <= 0){b = 0;}
  if (b >= 255){ b = 255;}
  
  
  
  
  // If Green Button Gets Pressed
  
  // If White Button Gets Pressed
  
  // If Blue Button Gets Pressed

  

  
  lastStateRed   = buttonStateRed;
  lastStateGreen = buttonStateGreen;
  lastStateWhite = buttonStateWhite;
  lastStateBlue  = buttonStateBlue;
  
    

  // Serial.println(heldTimeRed);
  
  lightUp(strip.Color(r, g, b));

}

void lightUp(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}