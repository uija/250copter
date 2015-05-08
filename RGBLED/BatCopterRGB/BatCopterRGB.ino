#include <Adafruit_NeoPixel.h>

#define RC 0
#define VL 1
#define VR 2
#define HL 3
#define HR 4

// PWM CONFIGURATION
#define PULSE 20000
#define RCMIN 1000
#define RCMAX 1950

Adafruit_NeoPixel vl = Adafruit_NeoPixel(6, VL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel vr = Adafruit_NeoPixel(6, VR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hl = Adafruit_NeoPixel(6, HL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hr = Adafruit_NeoPixel(6, HR, NEO_GRB + NEO_KHZ800);

unsigned int currentMode = 99;
unsigned long in;

void setColor( Adafruit_NeoPixel* strip, uint32_t color, int num, int offset) {
  for( int i = 0; i < num; ++i) { 
    strip->setPixelColor( i+offset, color);
  }
}
void setColor( Adafruit_NeoPixel* strip, uint32_t color, int num) {
  setColor( strip, color, num, 0);
}

void vlv( uint32_t color) {
  setColor( &vl, color, 3, 3); 
}
void vlh( uint32_t color) {
  setColor( &vl, color, 3, 0); 
}
void vrv( uint32_t color) {
  setColor( &vr, color, 3, 3); 
}
void vrh( uint32_t color) {
  setColor( &vr, color, 3, 0); 
}
void hlv( uint32_t color) {
  setColor( &hl, color, 3, 3); 
}
void hlh( uint32_t color) {
  setColor( &hl, color, 3, 0); 
}
void hrv( uint32_t color) {
  setColor( &hr, color, 3, 3); 
}
void hrh( uint32_t color) {
  setColor( &hr, color, 3, 0); 
}


unsigned int pos = 0;
int d = 1;

void laufLicht( uint32_t color) {
  if( pos == 6) pos = 0;
  setColor( &vl, vl.Color( 0, 0, 0), 6);
  vl.setPixelColor( pos, color);

  setColor( &vr, vl.Color( 0, 0, 0), 6);
  vr.setPixelColor( pos, color);

  setColor( &hl, vl.Color( 0, 0, 0), 6);
  hl.setPixelColor( pos, color);

  setColor( &hr, vl.Color( 0, 0, 0), 6);
  hr.setPixelColor( pos, color);
  
  pos++;

  vl.show();
  vr.show();
  hl.show();
  hr.show();
  
  delay( 100);
}
void blitz( uint32_t color) {
  setColor( &vl, vl.Color( 0, 0, 0), 6);
  setColor( &vr, vl.Color( 0, 0, 0), 6);
  setColor( &hl, vl.Color( 0, 0, 0), 6);
  setColor( &hr, vl.Color( 0, 0, 0), 6);
  setColor( &vl, color, 6);
  setColor( &vr, color, 6);
  setColor( &hl, color, 6);
  setColor( &hr, color, 6);
}

void mode0() {
  setColor( &vl, vl.Color( 0, 0, 0), 6);
  setColor( &vr, vl.Color( 0, 0, 0), 6);
  setColor( &hl, vl.Color( 0, 0, 0), 6);
  setColor( &hr, vl.Color( 0, 0, 0), 6);
  vl.show();
  vr.show();
  hl.show();
  hr.show();
}
void mode1() {
 vlv( vl.Color( 0,255, 0));
 vrv( vl.Color( 0,255, 0));
 
 hlh( vl.Color( 255, 0, 0));
 hrh( vl.Color( 255, 0, 0));
 
 vlh( vl.Color( 255, 255, 255));
 vrh( vl.Color( 255, 255, 255));
 hlv( vl.Color( 255, 255, 255));
 hrv( vl.Color( 255, 255, 255));
 
 vl.show();
 vr.show();
 hl.show();
 hr.show();
}

void mode2() {
  laufLicht( vl.Color( 255, 255, 255));
}
void mode3() {
  laufLicht( vl.Color( 255, 0, 0));
}
void mode4() {
  laufLicht( vl.Color( 0, 255, 0));
}
void mode5() {
  laufLicht( vl.Color( 0, 0, 255));
}
void mode6() {
  blitz( vl.Color( 255, 255, 255)); 
}
void setup() {
 pinMode(RC, INPUT);
 vl.begin();
 vr.begin();
 hl.begin();
 hr.begin(); 

 mode2();
 mode2();
 mode2();
 mode2();
 mode2();
 mode2();
 mode0();
}

void loop() {
  in = pulseIn( RC, HIGH, PULSE);
  unsigned int m = map(in, RCMIN, RCMAX, 0, 5);
  if( m == 0 && currentMode != m) {
    mode0();
  }
  else if( m == 1 && currentMode != m) {
    mode1();
  } 
  else if( m == 2) {
    mode2(); 
  } 
  else if( m == 3) {
    mode3(); 
  } 
  else if( m == 4) {
    mode4(); 
  } 
  else if( m == 5) {
    mode5(); 
  } 
  currentMode = m;
}
