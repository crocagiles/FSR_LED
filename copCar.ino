/*

*/
#include <Adafruit_NeoPixel.h>
#define PIN 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);



int analogPin = 0;     // pin for connection with fsr
                       // outside leads to ground and +5V
int val = 0;

int fadeSpeed = 2;
int hitValue  = 100;  // as soon as sfr thresh is hit, one color goes to this val
int fsrThresh = 500;

#define PIN 4
int r;
int g;
int b;
int heldTime;
int charger;
int sinAmp;
int slowFlash;
int fastFlash;
float period1;
float period2;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(150);
  strip.show(); // Initialize all pixels to 'off'
  //delay(1000);
  r,g,b     = 0,0,0;
  heldTime  = 0;
  sinAmp    = 100;
  slowFlash = 100;
  fastFlash = 175;
  period1 = .7; // lower is slower. good rand is .1 - 1
  period2 = .7;
  
}

void loop() {
  

  //delay(150);
  
  val = analogRead(analogPin);     // read the input pin
  //Serial.println(val);           // debug value
  
  // This is the main clock in this function. It iterates while pressure thresh is exceeded. Otherwise is 0
  if (val > fsrThresh){
    heldTime++;}
  else {
    heldTime = 0;}
  
  if (heldTime > 130 ){
    heldTime = 2;
  }
  //Serial.println(r);
  
  //When thresh is exceeded, light up  
  if (heldTime > 30 && heldTime  < 80 ){
    r = map(255, 0, 255, 0, 255-sinAmp);
    g = 0;
    b = 0;
    r =  r + (sin(period1 *  heldTime)*(sinAmp/2));
  }

  else if (heldTime > 1){
    r =0 ;
    g =0 ;
    b = map(255,   0, 255, 0, 255-sinAmp);
    b =  b + (sin(period1 *  heldTime)*(sinAmp/2));
  }
  
    

  if (heldTime == 0){
    
    r -= fadeSpeed;
    g -= fadeSpeed;
    b -= fadeSpeed;
  }
  
  if (r < 0){ r = 0;}
  if (r > 255){ r = 255;}
  if (g < 0){g = 0;}
  if (g > 255){ g = 255;}
  if (b < 0){b = 0;}
  if (b > 255){ b = 255;}
  
  if (heldTime == 1) {
    Serial.println("siren!");
  }
 lightUp(strip.Color(r, g, b));
   //strip.show();
}


static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      //delay(25);
  }
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

