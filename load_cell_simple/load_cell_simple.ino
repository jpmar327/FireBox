
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
// constants won't change. They're used here to set pin numbers:
const int buttonPin5 = 5;     // the number of the pushbutton pin
const int buttonPin6 = 6; 
//const int ledPin =  13;      // the number of the LED pin
long weight = 0;
long tar = 0;
// variables will change:
int buttonState5 = 0;         // variable for reading the pushbutton status
int buttonState6 = 0;         // variable for reading the pushbutton status
long reading;
HX711 scale;

void setup() {
   // initialize the LED pin as an output:
//  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare();
}

void loop() {
  scale.tare();
  // read the state of the pushbutton value:
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  if (buttonState5 == HIGH) {
//        reading = scale.read();
        tar = -(scale.read());
        Serial.print("HX711 TARE reading: ");
        weight = 0;
        Serial.println(weight);
//        weight = 0;
        // turn LED on:
      } 
      else if (buttonState6 == HIGH) {
        reading = scale.read();
        weight = (tar+reading)/100;
        Serial.print("HX711 reading: ");
        Serial.println(weight);
      }
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//  if (buttonState == HIGH) {
//    long tar = scale.read();
//    // turn LED on:
//    digitalWrite(ledPin, HIGH);
//  } else {
//    // turn LED off:
//    digitalWrite(ledPin, LOW);
//  }
//  if (scale.wait_ready_timeout(10000)) {
//      if (buttonState5 == HIGH) {
////        reading = scale.read();
//        tar = -(scale.read());
//        Serial.print("HX711 TARE reading: ");
//        weight = 0;
//        Serial.println(weight);
////        weight = 0;
//        // turn LED on:
//      } 
//      else if (buttonState6 == HIGH) {
//        reading = scale.read();
//        weight = tar+reading;
//        Serial.print("HX711 reading: ");
//        Serial.println(weight);
//      }
//    
//
//  } else {
//    Serial.println("HX711 not found.");
//  }

//  delay(500);
  
}
