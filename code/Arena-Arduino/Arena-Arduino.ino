/* 

~~~~~~~ arduivis - MaxMSP ~~~~~~~
~~~~~~~~ model#2: input ~~~~~~~~~

MaxMSP: arduivis_Max7_model2_input.maxpat

This is an example of how to read a slider from 
MaxMSP and write the values to a PWM LED connected
to an Arduino.

This code is in the public domain

written by Christopher Konopka
http://cskonopka.github.io/arduivis/
http://christopherkonopka.com/

*/

 #include <Adafruit_NeoPixel.h>
 
#define PIN      3
#define N_LEDS 72
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup() 
{ 
  //  Create/open serial port
    Serial.begin(9600);   

  // Define LED mode 
  // PWM LED  
  strip.begin();
  strip.setBrightness(255);

}

void loop() 
{

  // Slider from MaxMSP 
    int maxmspSlider1, maxmspSlider2, maxmspSlider3;


  // Parse incoming MaxMSP slider values
  // from MaxMSP, to Arduino   
  if (Serial.parseInt() == -99){ 
    maxmspSlider1 = Serial.parseInt();  
    maxmspSlider2 = Serial.parseInt();  
    maxmspSlider3 = Serial.parseInt();  

    Serial.print(maxmspSlider1);
    Serial.print(maxmspSlider2);
    Serial.println(maxmspSlider3);
    
  
  }


  // Write parsed values to LEDs
  // Fading LED
  // from MaxMSP, to Arduino    
//    analogWrite(13, maxmspSlider);

for(uint16_t i=0; i<strip.numPixels(); i++) {
  strip.setPixelColor(i  , strip.Color(maxmspSlider1, maxmspSlider2, maxmspSlider3)); // Draw new pixel
}
strip.show();

delay(20);

}
