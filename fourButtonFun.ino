/* Learn to use pushbutton (button switch) with Arduino - Tutorial
   More info and circuit schematic: http://www.ardumotive.com/arduino-tutorials/category/button
   Dev: Michalis Vasilakis / Date: 19/10/2014  
   UPDATED 2/6/2016 - LED to Arduino pin 3 and button to Arduino pin 4*/


//Constants
const int buttonPinRed   = 3;     
const int buttonPinGreen = 7;
const int buttonPinWhite = 6;
const int buttonPinBlue  = 5;

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
int heldTimeGreen = 0;
int heldTimeWhite = 0;
int heldTimeBlue = 0;
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
  
  
  if (buttonStateRed == 0) {
    heldTimeRed++;}
  else {
    heldTimeRed = 0;
  }
  


  //When thresh is exceeded, light up  
  if (heldTimeRed == 1 ){
    baseR = red;
    baseG = green;
    baseB = blue;
    r = map(red,   0, 255, 0, baseR);
    g = map(green, 0, 255, 0, baseG);
    b = map(blue,  0, 255, 0, baseB);
  }
  if (heldTimeRed > 100 ){// && heldTime < 400){
    r =  (baseR-20) + (sin(period1 *  heldTimeRed)*(sinAmp*baseR));
    g =  (baseG-20) + (sin(period1 *  heldTimeRed)*(sinAmp*baseG));
    b =  (baseB-20) + (sin(period1 *  heldTimeRed)*(sinAmp*baseB));
    

  }
  
  // Serial.print(r);
  // Serial.print("\t");  
  // Serial.print(g);
  // Serial.print("\t");
  // Serial.print(b);
  // Serial.print("\t");
  // Serial.print("\n");
  

  
  
  
  
  // If Green Button Gets Pressed
  
  if (buttonStateGreen == 0) {
    heldTimeGreen++;}
  else {
    heldTimeGreen = 0;
  }
  
  if (heldTimeGreen == 1){
    Serial.print("cop");
  }
  
  if (heldTimeGreen > 130 ){
    heldTimeGreen = 2;
  }
  //Serial.println(r);
  
  //When thresh is exceeded, light up  
  if (heldTimeGreen > 30 && heldTimeGreen  < 80 ){
    r = map(255, 0, 255, 0, 255-sinAmp);
    g = 0;
    b = 0;
    r =  r + (sin(period1 *  heldTimeGreen)*(sinAmp/2));
  }

  else if (heldTimeGreen > 1){
    r =0 ;
    g =0 ;
    b = map(255,   0, 255, 0, 255-sinAmp);
    b =  b + (sin(period1 *  heldTimeGreen)*(sinAmp/2));
  }
  
    

  if (heldTimeGreen == 0){
    
    r -= fadeSpeed;
    g -= fadeSpeed;
    b -= fadeSpeed;
  }
  
  
  // If White Button Gets Pressed
  if (buttonStateWhite == 0) {
    heldTimeWhite++;}
  else {
    heldTimeWhite = 0;
  }  
  
  if  (heldTimeWhite == 1 ){
    Serial.println("tieFire");
    r = 0;
    g = 255;
    b = 0;
  }
  // else {
  //   r = 0;
  //   g -= 1;
  //   b = 0;
  // }  
  
  
  
  // If Blue Button Gets Pressed
  if (buttonStateBlue == 0) {
    heldTimeBlue++;}
  else {
    heldTimeBlue = 0;
  }  
  
  if  (heldTimeBlue == 1 ){
    Serial.print("Blaster");
    r = 255;
    g = 0;
    b = 0;
  }
  // else {
  //   r -= 2;
  //   g  = 0;
  //   b  = 0;
  // }  
  
  // lastStateRed   = buttonStateRed;
  // lastStateGreen = buttonStateGreen;
  // lastStateWhite = buttonStateWhite;
  // lastStateBlue  = buttonStateBlue;
  
  
  if (heldTimeRed == 0 && heldTimeGreen == 0 && heldTimeBlue == 0 && heldTimeWhite == 0 ){
    r -= fadeSpeed;
    g -= fadeSpeed;
    b -= fadeSpeed;
  }    

  // Serial.println(heldTimeRed);
  
  if (r <= 0){ r = 0;}
  if (r >= 255){ r = 255;}
  if (g <= 0){g = 0;}
  if (g >= 255){ g = 255;}
  if (b <= 0){b = 0;}
  if (b >= 255){ b = 255;}
  
  lightUp(strip.Color(r, g, b));


  // Serial.print(r);
  // Serial.print("\t");  
  // Serial.print(g);
  // Serial.print("\t");
  // Serial.print(b);
  // Serial.print("\t");
  // Serial.print(heldTimeRed);
  // Serial.print("\t");  
  // Serial.print("\n");
  
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
