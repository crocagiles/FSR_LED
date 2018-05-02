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

//Color for random flashing charge up
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                          R   G   B
// uint8_t myColors[][3] = {{232, 100, 255},   // purple
//                         {200, 200, 20},   // yellow 
//                         {30, 200, 200},   // blue
//                         {237,159,176},    // pink
//                         {255, 0, 0},      // red
//                         {108, 87,229},     // Dark blue
//                         {162,211,172},     // Lt Green
//                         {0, 0, 0},   // yellow 
//                         {0, 0, 0},   // blue
//                         {0,0,0},    // pink
//                         {0, 0, 0},      // red
//                         {0, 0,0},     // Dark blue
//                         {0,0,0}, 
//                         {0, 0, 0},   // yellow 
//                         {0, 0, 0},   // blue
//                         {0,0,0},    // pink
//                         {0, 0, 0},      // red
//                         {0, 0,0},     // Dark blue
//                         {0,0,0},                        // Lt Green
//                           };
                               
// #define FAVCOLORS sizeof(myColors) / 3

uint8_t myColors[][3] = {{255, 0, 0},   // purple
                        {0, 255, 0},   // yellow 
                        {0, 0, 255},   // blue

                        {0, 0, 0},   // yellow 
                        {0, 0, 0},   // blue
                        {0,0,0},    // pink
                        {0, 0, 0},      // red
                        {0, 0,0},     // Dark blue
                        {0,0,0},                        // Lt Green
                          };
                               
#define FAVCOLORS sizeof(myColors) / 3


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

int analogPin = 0;     // pin for connection with fsr
                       // outside leads to ground and +5V
int val = 0;

int fadeSpeed = 0;
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
int baseR;
int baseG;
int baseB;

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
  period1 = .5; // lower is slower. good rand is .1 - 1
  period2 = .7;
  baseR = 0;
  baseG = 0;
  baseB = 0;
  
}

void loop() {
  
  //int randColor = random(1, 5);
  
  int indy = random(chosenColor);
  int red = baseColors[indy][0];
  int green = baseColors[indy][1];
  int blue = baseColors[indy][2];
  
  val = analogRead(analogPin);     // read the input pin
  //Serial.println(val);           // debug value
  
  // This is the main clock in this function. It iterates while pressure thresh is exceeded. Otherwise is 0
  if (val > fsrThresh){
    heldTime++;}
  else {
    heldTime = 0;
  }
  
  //Fade if trigger is not being held
  if (heldTime == 0){
    
    r -= fadeSpeed;
    g -= fadeSpeed;
    b -= fadeSpeed;
  }
  
  //When thresh is exceeded, light up  
  else if (heldTime == 1 ){
  baseR = red;
  baseG = green;
  baseB = blue;
  r = map(red,   0, 255, 0, baseR);
  g = map(green, 0, 255, 0, baseG);
  b = map(blue,  0, 255, 0, baseB);
  // Serial.println("Bewww!");
  }
  
  // //stay lit up, but don't fade
  // else if (heldTime < 50){// && heldTime < 400){
    
  //   r =  baseR-sinAmp + (sin(period2 *  heldTime)*(sinAmp));
  //   g =  baseG-sinAmp + (sin(period2 *  heldTime)*(sinAmp));
  //   b =  baseB-sinAmp + (sin(period2 *  heldTime)*(sinAmp));
  // }
  
  else if (heldTime > 6 ){// && heldTime < 400){
    
    r =  baseR-sinAmp + (sin(period2 *  heldTime)*(sinAmp));
    g =  baseG-sinAmp + (sin(period2 *  heldTime)*(sinAmp));
    b =  baseB-sinAmp + (sin(period2 *  heldTime)*(sinAmp));
  }
  


  
  if (r < 0){ r = 0;}
  if (r > 255){ r = 255;}
  if (g < 0){g = 0;}
  if (g > 255){ g = 255;}
  if (b < 0){b = 0;}
  if (b > 255){ b = 255;}
  
  Serial.print(r);
  Serial.print("\t");  
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print("\n");

 r = 30;
 g = 0;
 b = 0;
 
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

void flashRandom(int wait, uint8_t howmany) {
 
  for(uint16_t i=0; i<howmany; i++) {
    // pick a random favorite color!
    int c = random(FAVCOLORS);
    int red = myColors[c][0];
    int green = myColors[c][1];
    int blue = myColors[c][2]; 
    
    strip.setPixelColor(i, strip.Color(red, green, blue));
      //strip.show();
      //delay(wait);
  }
  strip.show();
  delay(wait);
  
  // LEDs will be off when done (they are faded to 0)
}

