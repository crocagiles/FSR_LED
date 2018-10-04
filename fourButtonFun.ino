/* Learn to use pushbutton (button switch) with Arduino - Tutorial
   More info and circuit schematic: http://www.ardumotive.com/arduino-tutorials/category/button
   Dev: Michalis Vasilakis / Date: 19/10/2014  
   UPDATED 2/6/2016 - LED to Arduino pin 3 and button to Arduino pin 4*/


//Constants
const int buttonPinRed   = 4;     
const int buttonPinGreen = 5;
const int buttonPinWhite = 6;
const int buttonPinBlue  = 7;

const int fadeSpeed = 1;

#include <Adafruit_NeoPixel.h>
#define PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);

//Variables
//int buttonState = 0;
int lastStateRed   = 0;
int lastStateGreen = 0;
int lastStateWhite = 0;
int lastStateBlue = 0;
// int red_button_state   = 0;
// int green_button_state = 0;
// int blue_button_state = 0;
// int white_button_state  = 0;

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
int red_held_time = 0;
int green_hold_time = 0;
int blue_hold_time = 0;
int white_hold_time = 0;
int sinAmp    = 1;
float period1 = 1;

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

  int red_button_state   = digitalRead(buttonPinRed);
  int green_button_state = digitalRead(buttonPinGreen);
  int blue_button_state = digitalRead(buttonPinWhite);
  int white_button_state  = digitalRead(buttonPinBlue);
  
  
  // Red Button
  // For sin wave flashing
  int indy = random(chosenColor);
  int red = baseColors[indy][0];
  int green = baseColors[indy][1];
  int blue = baseColors[indy][2];
  
  
  if (red_button_state == 0) {
    red_held_time++;}
  else {
    red_held_time = 0;
  }

  //When thresh is exceeded, light up  
  if (red_held_time == 1 ){
    Serial.println("red_button");
    baseR = red;
    baseG = green;
    baseB = blue;
    r = map(red,   0, 255, 0, baseR);
    g = map(green, 0, 255, 0, baseG);
    b = map(blue,  0, 255, 0, baseB);
  }
  if (red_held_time > 10 ){// && heldTime < 400){
    r =  (baseR-20) + (sin(period1 *  red_held_time)*(sinAmp*baseR));
    g =  (baseG-20) + (sin(period1 *  red_held_time)*(sinAmp*baseG));
    b =  (baseB-20) + (sin(period1 *  red_held_time)*(sinAmp*baseB));
  }
  
  // Serial.print(r);
  // Serial.print("\t");  
  // Serial.print(g);
  // Serial.print("\t");
  // Serial.print(b);
  // Serial.print("\t");
  // Serial.print("\n");
  

  
  
  // If Green Button Gets Pressed
  if (green_button_state == 0) {
    green_hold_time++;}
  else {
    green_hold_time = 0;
  }
  
  if (green_hold_time == 1){
    Serial.println("green_button");
    baseR = red;
    baseG = green;
    baseB = blue;
    r = map(red,   0, 255, 0, baseR);
    g = map(green, 0, 255, 0, baseG);
    b = map(blue,  0, 255, 0, baseB);
  }
  if (green_hold_time > 10 ){// && heldTime < 400){
    r =  (baseR-20) + (sin(period1 *  green_hold_time)*(sinAmp*baseR));
    g =  (baseG-20) + (sin(period1 *  green_hold_time)*(sinAmp*baseG));
    b =  (baseB-20) + (sin(period1 *  green_hold_time)*(sinAmp*baseB));
  }
 
  //Serial.println(green_hold_time);  

  // else if (green_hold_time == 0){
    
  //   r -= fadeSpeed;
  //   g -= fadeSpeed;
  //   b -= fadeSpeed;
  // }
  
  
  if (blue_button_state == 0) {
    blue_hold_time++;}
  else {
    blue_hold_time = 0;
  }  
  
  if  (blue_hold_time == 25 ){
    Serial.println("blue_button");
    r = baseR;
    g = baseG;
    b = baseB;
    lightUp(strip.Color(r, g, b));
    return 0;
  }
  // else {
  //   r = 0;
  //   g -= 1;
  //   b = 0;
  // }  
  
  
    // If white Button Gets Pressed
  if (white_button_state == 0) {
    white_hold_time++;}
  else {
    white_hold_time = 0;
  }
  
  if (white_hold_time == 1){
    Serial.println("white_button");
    r = 255;
    g = 45;
    b = 0;
  }
  if (white_hold_time > 10 ){// && heldTime < 400){
    r =  (r) + (sin(period1 *  white_hold_time)*(sinAmp*255));
    g =  (g) + (sin(period1 *  white_hold_time)*(sinAmp*50));
    b =  (b) + (sin(period1 *  white_hold_time)*(sinAmp));
  }
  
  
  
  
  
  // // If white Button Gets Pressed
  // if (white_button_state == 0) {
  //   green_hold_time++;}
  // else {
  //   green_hold_time = 0;
  // }  
  
  // if  (green_hold_time > 2 ){
  //   //Serial.println("White Button");
  //   r = 255;
  //   g = 45;
  //   b = 0;
  //   lightUp(strip.Color(r, g, b));
    
  // }
  

  
  if (red_held_time == 0 && green_hold_time == 0 && green_hold_time == 0 && blue_hold_time == 0 ){
    r -= fadeSpeed;
    g -= fadeSpeed;
    b -= fadeSpeed;
  }    

  // Serial.println(red_held_time);
  
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
  // Serial.print(red_held_time);
  // Serial.print("\t");  
  // Serial.print("\n");
  
}

void lightUp(uint32_t c) {
  for(uint16_t i=0; i<150; i++) {
      strip.setPixelColor(i, 0);
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}


