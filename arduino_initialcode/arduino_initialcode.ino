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

long startTime;
long timeLimit; // milliseonds of what equals 100%. 

long debounceDelay = 50;


// reset button globals
const int resetButton = 10; // some pin for the reset button. 
int resetButtonState;
int resetLastButtonState = LOW;
long resetDebounceTime = 0;

// snooze button globals
const int snoozeButton = 9; // some pin for the reset button. 
int snoozeButtonState;
int snoozeLastButtonState = LOW;
long snoozeDebounceTime = 0;

int timePassed;



/*
* We're at 100% Trigger their inner Marley, get up, stand up!
*/
void reachedMax() {
  // do some flashy stuff
}

/*
* function that sets the light bar. Unsure of parameters yet. Guessing we take in color and percentage?
* this function handles this specific lighting setup, so different hardware would presumably need a new version of this function
*/
void setLighting(int percent) {
  int x = 0;
  // do something
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
  setLighting(timePassed);  
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
  if(resetRead != resetLastButtonState) resetDebounceTime = millis(); // reset debounce timer
  if((millis() - resetDebounceTime) > debounceDelay) {
    // Holy crap, it's not just noise anymore. OH LAWD! WE MUST ACT!
    if(resetRead != resetButtonState) resetButtonState = resetRead; // set what the button is
    if(resetButtonState = HIGH) resetTime(); // reset if HIGH
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
int getTimePassed() {
  long diff = millis() - startTime; // gives us the difference
  return (int) (diff * 100) / timeLimit;
}

// resets to 0%
void resetTime() {
  startTime = millis();
}



// Main setup function!
void setup() {
  startTime = millis();
  timeLimit = 30 * 60 * 1000; // 30 minutes. 30 minutes * 60 seconds * 1000 milli.
}


/* Main loop function!
* - Checks for reset button push.
* - check if at 100%. Call reachedMaxed
*/
void loop() {
  readResetButton(digitalRead(resetButton));
  timePassed = getTimePassed();
  if(timePassed >= 100) {
    reachedMax();
    return;
  }
  // less than 100%
  else {
    updateBar(timePassed);
  }
}
