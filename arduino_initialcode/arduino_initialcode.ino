#include <Adafruit_NeoPixel.h>

/*
* TEAM AWESOME INF1510 arduino project
* Members:
*   - Halvor Mangseth
*   - Aulon Mujaj
*   - Kirsi Aanstad
*   - Tana Blegen
* 
* Code principles:
* - We base all measurements onwhole per cents. (range 0-100). It shouldn't be necesarry with anything more precise.
* This should make it easy for different functions to know their input.
* No functions should directly use the clock except for debouncing. We use the methods for reading a percentage, and then act accordingly. 
*/

unsigned long startTime;
unsigned long timeLimit; // milliseonds of what equals 100%. 

unsigned long debounceDelay = 50;


// reset button globals
const int resetButton = 4; // some pin for the reset button. 
int resetButtonState;
int resetLastButtonState = LOW;
unsigned long resetDebounceTime = 0;

// snooze button globals
const int snoozeButton = 9; // some pin for the reset button. 
int snoozeButtonState;
int snoozeLastButtonState = LOW;
unsigned long snoozeDebounceTime = 0;

// percentage
int timePassed;


// variables for the LEDstrip
const int stripPIN = 6;
const int stripLEDS = 11;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, stripPIN, NEO_GRB + NEO_KHZ800);



/*
* We're at 100% Trigger their inner Marley, get up, stand up!
*/
void reachedMax() {
  setLighting(100, 100, 0, 0);
  setFirst(100, 0, 0);
  // do some flashy stuff
  
  // debugging
  delay(2000);
  resetTime();
  resetBar();
}

/*
* function that sets the light bar. Unsure of parameters yet. Guessing we take in color and percentage?
* this function handles this specific lighting setup, so different hardware would presumably need a new version of this function
* We always keep the first LED lit. This is done in setup. 
* We use the variables:
* strip = the ledstrip
* stripPIN is 6 if needed
* stripLEDS = number of utilized lEDs
*/
void setLighting(int percent, int red, int blue, int green) {
  int ceiling = (int) (percent * stripLEDS) / 100;
  for(int i = 1; i <= ceiling; i++) {
   strip.setPixelColor(i, strip.Color(red, blue, green));
   //strip.show(); 
  }
  //strip.setPixelColor(ceiling, strip.Color(red, blue, green));
  strip.show();
  // do something
}


// method for setting the first LED that's usually untouched. 
void setFirst(int red, int blue, int green) {
   strip.setPixelColor(0, strip.Color(red, blue, green));
   strip.show(); 
}


/*
* update stuff.
* update led bar with size and maybe color. 
* if logging update time passed to necessary outputs in whatever format we need. 
* 
*/
void updateBar(int timePassed) {
  // update led bar.
  // need to test
  
  setLighting(timePassed, 100, 100, 100); // white
}


/*
* Setup function for the lightbar.
*/
void barSetup() {
 strip.begin(); // ledstrip setup
 for(int i = 1; i <= strip.numPixels(); i++) {
   strip.setPixelColor(i, strip.Color(0, 0, 0));
   strip.show();
 }
 strip.setPixelColor(0, strip.Color(100, 100, 100));
 strip.show();
}


// Triggered when someonepushes the snooze button.
void snoozeTime() {
  // do stuff
}


/*
* Handles the reading of the reset button.
* Uses debounce, while the button is pressed it resets the timer. 
*/
void readResetButton(int resetRead) {
  // reset debounce timer
  if(resetRead != resetLastButtonState) {
    resetLastButtonState = resetRead;
    resetDebounceTime = millis(); 
  }
  Serial.println(millis() - resetDebounceTime);
  if((millis() - resetDebounceTime) > debounceDelay) {
    // Holy crap, it's not just noise anymore. OH LAWD! WE MUST ACT!
    //if(resetRead != resetButtonState) resetButtonState = resetRead; // set what the button is
    resetButtonState = resetRead;
    if(resetButtonState == HIGH) resetTime(); // reset if HIGH
  }
}

void readSnoozeButton(int snoozeRead) {
  if(snoozeRead != snoozeLastButtonState) snoozeDebounceTime = millis(); // reset debounce timer
  if((millis() - snoozeDebounceTime) > debounceDelay) {
    // Holy crap, it's not just noise anymore. OH LAWD! WE MUST ACT!
    if(snoozeRead != snoozeButtonState) snoozeButtonState = snoozeRead; // set what the button is
    if(snoozeButtonState = HIGH) snoozeTime(); // reset if HIGH
  }
}

/*
* returns the percentage time passed compared to now compared to startTime.
* Formula is: (diff * 100) / timeLimit to get percentage. We just round down, no need for extreme precision. 
* return percentage of  time passed since reset. 
*/
unsigned int getTimePassed() {
  unsigned long diff = millis() - startTime; // gives us the difference
  if(diff > timeLimit) return 100;
  
  unsigned long result = diff * 100;
  result /= timeLimit;
  return (int) result;
  //return (unsigned int) (diff * 100) / timeLimit;
}

// resets to 0%
void resetTime() {
  startTime = millis();
}

void resetBar() {
  
  // for now just whipe the bar and set the first one to initial color. 
  barSetup();
}

// Main setup function!
void setup() {
  startTime = millis();
  //timeLimit = 30 * 60 * 1000; // 30 minutes. 30 minutes * 60 seconds * 1000 milli.
  timeLimit = 10 * 1000; // 10 seconds for testing
  barSetup();
  
  
  // debugging
  Serial.begin(9600);
  
}
/* Main loop function!
* - Checks for reset button push.
* - check if at 100%. Call reachedMaxed
*/
void loop() {
  readResetButton(digitalRead(resetButton));
  //Serial.println(millis());
  timePassed = getTimePassed();
  //resetBar();
  //Serial.println(timePassed);
  
  
  if(timePassed >= 100) {
    reachedMax();
  }
  // less than 100%
  else {
    updateBar(timePassed);
  }
  
}
