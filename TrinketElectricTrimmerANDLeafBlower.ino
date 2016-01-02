/*------------------------------------------------------------------------------------------------------
                              Author : Evan Richinson aka MrRetupmoc42
               
Trinket Based Trimmer / Blower ESC Controller
  Press n' Hold a Button within a Certain Time to Turn on the Trimmer,
  Press Button Again to Shutdown the ESC
  
Summer 2015 : Created, Tuned and Uploaded...
                   
-------------------------------------------------------------------------------------------------------*/

#include <Adafruit_SoftServo.h> 

#define SERVO1PIN 0
Adafruit_SoftServo myServo1;
   
void setup() {
  // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)
  
  myServo1.attach(SERVO1PIN);
  //myServo1.write(90);           // Tell servo to go to position per quirk
  //delay(15);                    // Wait 15ms for the servo to reach the position
  
  myServo1.write(0);
  delay(3000);
  
  // Tell ESC Max Speed Output
  for(int servospeed = 90; servospeed <= 180; servospeed++) {
      myServo1.write(servospeed); 
      delay(5);
  }
  
  // Reset ESC Speed Softly
  for(int servospeed = 180; servospeed >= 90; servospeed--) {
      myServo1.write(servospeed); 
      delay(5);
  }
  
  // Give it a Break
  delay(2500);
  
  // Ramp up for Use
  for(int servospeed = 90; servospeed <= 120; servospeed++) {
      myServo1.write(servospeed); 
      delay(75);
  }
}

void loop()  {
  delay(1000);
}

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
  }
}
