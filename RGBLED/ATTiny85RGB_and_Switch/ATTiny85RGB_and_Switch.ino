#include <Adafruit_NeoPixel.h>


// Board Configuration
//#define ARDUINO
#define ATTINY

// IN AND OUTS
#ifdef ARDUINO
  #define STRIPFRONT 8
  #define STRIPBACK 10
  #define INRC1 2
  #define INRC2 3
  #define SWITCH 4
#endif

#ifdef ATTINY
  #define STRIPFRONT 2
  #define STRIPBACK 3
  #define INRC1 0
  #define INRC2 1
  #define SWITCH 4
#endif

// PWM CONFIGURATION
#define PULSE 20000
#define RCMIN 1000
#define RCMAX 1950

// LED CONFIGURATION

#define NUM_LEDS_FRONT 3
#define NUM_LEDS_BACK 3

unsigned long switch1;
unsigned long switch2;
int dir = 1;
int pos = 0;
int fpos = 0;

// Create an instance of the Adafruit_NeoPixel class called "strip".
Adafruit_NeoPixel stripFront = Adafruit_NeoPixel(NUM_LEDS_FRONT, STRIPFRONT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripBack = Adafruit_NeoPixel(NUM_LEDS_BACK, STRIPBACK, NEO_GRB + NEO_KHZ800);

void setColor( Adafruit_NeoPixel* strip, uint32_t color, int num) {
  for( int i = 0; i < num; ++i) { 
    strip->setPixelColor( i, color);
  }
}

void setup()
{
  //Serial.begin( 9600);
  pinMode(INRC1, INPUT);
  pinMode(INRC2, INPUT);
  pinMode(SWITCH, OUTPUT);
  stripFront.begin();
  stripBack.begin();
}

void loop()
{
  switch1 = pulseIn(INRC1, HIGH, PULSE);
  switch2 = pulseIn(INRC2, HIGH, PULSE);
  if(switch2 >= 1750){
    digitalWrite(SWITCH, HIGH);
    }
  else{
    digitalWrite(SWITCH, LOW);
    }

  int colorModes = map(switch1, RCMIN, RCMAX, 0, 8);

  switch (colorModes) {
  case 0:    
     setColor( &stripFront, stripFront.Color( 0, 0, 0), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 0, 0, 0), NUM_LEDS_BACK);
    break;
 

   case 1:
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 255, 0, 0), NUM_LEDS_BACK);
    break;
     
   case 2:    
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 0, 255, 0), NUM_LEDS_BACK);
    break;
    
   case 3:    
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 0, 0, 255), NUM_LEDS_BACK);
    break;
    
   case 4:    
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 255, 255, 0), NUM_LEDS_BACK);
    break;
    
  case 5:    
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 255, 0, 255), NUM_LEDS_BACK);
    break;
    
  case 6:    
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 0, 255, 255), NUM_LEDS_BACK);
    break;

   case 7:    
     setColor( &stripFront, stripFront.Color( 255, 0, 0), NUM_LEDS_FRONT);
     
     setColor( &stripBack, stripFront.Color( 0, 0, 0), NUM_LEDS_BACK);
     pos = pos + dir;
     if( pos < -1) {
       dir = 1;
     } else if( pos == NUM_LEDS_BACK) {
       dir = -1;
     }
     stripBack.setPixelColor( pos-1, stripBack.Color(32, 0, 0));
     stripBack.setPixelColor( pos, stripBack.Color(124, 5, 0));
     stripBack.setPixelColor( pos+1, stripBack.Color(255, 10, 0));
     stripBack.setPixelColor( pos+2, stripBack.Color(124, 5, 0));
     stripBack.setPixelColor( pos+3, stripBack.Color(32, 0, 0));
     stripBack.show();
    break;

  case 8:
     
     setColor( &stripFront, stripFront.Color( 0, 0, 0), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color( 0, 0, 0), NUM_LEDS_BACK);
     stripFront.show();
     stripBack.show();
     delay( 100);
     setColor( &stripFront, stripFront.Color(97, 196, 25), NUM_LEDS_FRONT);
     setColor( &stripBack, stripFront.Color(255, 0, 0), NUM_LEDS_BACK);
    break;
   

  } 
  stripFront.show();
  stripBack.show();
}

 
    
    
    


  
   
  
  

