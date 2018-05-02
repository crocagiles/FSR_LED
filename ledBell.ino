/*

Program will detect frequency of the bell and light up LEDs if "bell factor" is above the user specified level

Software requirements:
 - neoPixel library
 - elm-chan's ffft library for Arduino
*/

// IMPORTANT: FFT_N should be #defined as 128 in ffft.h.

#include <avr/pgmspace.h>
#include <ffft.h>
#include <math.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>


// Microphone connects to Analog Pin 0.  Corresponding ADC channel number
// varies among boards...it's ADC0 on Uno and Mega, ADC7 on Leonardo.
// Other boards may require different settings; refer to datasheet.

#define ADC_CHANNEL 0

int16_t       capture[FFT_N];    // Audio capture buffer
complex_t     bfly_buff[FFT_N];  // FFT "butterfly" buffer
uint16_t      spectrum[FFT_N/2]; // Spectrum output buffer
volatile byte samplePos = 0;     // Buffer position counter

//Init LEDs
#define PIN 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
  int r;
  int g;
  int b;

void setup() {
  Serial.begin(9600);
  // Init ADC free-run mode; f = ( 16MHz/prescaler ) / 13 cycles/conversion 
  ADMUX  = _BV(REFS0) | (ADC_CHANNEL & 0x07); // Channel sel, right-adj, use AREF pin
  //ADMUX  = ADC_CHANNEL; // Channel sel, right-adj, use AREF pin
  ADCSRA = _BV(ADEN)  | // ADC enable
           _BV(ADSC)  | // ADC start
           _BV(ADATE) | // Auto trigger
           _BV(ADIE)  | // Interrupt enable
           _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // 128:1 / 13 = 9615 Hz
  ADCSRB = 0;                // Free run mode, no high MUX bit
  DIDR0  = 1 << ADC_CHANNEL; // Turn off digital input for ADC pin
  TIMSK0 = 0;                // Timer0 off

  sei(); // Enable interrupts
  
  // LED Stuff
  strip.begin();
  strip.setBrightness(200); // one time use, sets max brightness of pixels
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  while(ADCSRA & _BV(ADIE)); // Wait for audio sampling to finish - wait until interrupts are off

  fft_input(capture, bfly_buff);   // Samples -> complex #s
  samplePos = 0;                   // Reset sample counter
  ADCSRA |= _BV(ADIE);             // Resume sampling interrupt - are interrupts back on?
  fft_execute(bfly_buff);          // Process complex data
  fft_output(bfly_buff, spectrum); // Complex -> spectrum
  
  float sumSpectrum = 0;
  for (int i=20; (i<FFT_N/2) ; i++){
    Serial.print(spectrum[i]);
    Serial.println();
    sumSpectrum = sumSpectrum + spectrum[i];
  }
  

  
  
  // Don't mess with this
  float avSpectrum = sumSpectrum/236;
  int bellFreq = spectrum[27] + spectrum[28] + spectrum[29];
  int bellFactor = bellFreq/avSpectrum;
  int randColor = random(1, 4);
  
  if (bellFactor > 55){
  Serial.println(bellFactor);
  }
  
  // Mess with this
  int bellThresh = 55;      //sensitivity to bell frequency
  int fadeFactor = 3;       //How fast lights will fade after bell thresh is passed
  int coolThresh = 40;      //cooldown thresh. can't reactivate lights until they fade past this

   
  // for (i=0;i<FFT_N/2;i++){
  //   Serial.print(spectrum[i]);
  //   Serial.print(" ");
  // }
  // Serial.print("\n");


  //lights dimming, cooldown period
  if (r > coolThresh || g > coolThresh || b > coolThresh) {
    if (r != 0){
      r -= fadeFactor;}
    if (g != 0){
      g -= fadeFactor;}
    if (b != 0){
      b -= fadeFactor;}
  }
  
 //lights dimming, bell not present
  else if (bellFactor < bellThresh){ 
    if (r != 0){
      r -= fadeFactor;}
    if (g != 0){
      g -= fadeFactor;}
    if (b != 0){
      b -= fadeFactor;}
  }
  
  //lights cooled down or off, will light up if bellfactor exceeds bellthresh
  else if ((r < coolThresh && g < coolThresh && b < coolThresh) && bellFactor > bellThresh)
  { 
     if (randColor == 1){
     r = 255;}
     if (randColor == 2){
     g = 255;}
     if (randColor == 3){
     b = 255;}
  }
  
  else {
    r,g,b = 0,0,0;
  }
    
   lightUp(strip.Color(r, g, b));
   //strip.show();
   

}

// light up entire strip
void lightUp(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();

}



ISR(ADC_vect) { // Audio-sampling interrupt
  static const int16_t noiseThreshold = 4;
  int16_t              sample         = ADC; // 0-1023


  if ((sample > (512-noiseThreshold)) && (sample < (512+noiseThreshold))) {
    sample = 0;
  } else {
    // Sign-convert for FFT; -512 to +511
    sample -= 512; 
  }

  capture[samplePos] = sample;
   
  if(++samplePos >= FFT_N) ADCSRA &= ~_BV(ADIE); // Buffer full, interrupt off
}

