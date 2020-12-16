
#include "HX711.h"
// constants won't change. They're used here to set pin numbers:
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
// Button circuit wiring
const int buttonPin5 = 5; // the number of the pushbutton pin -- PIN5
const int buttonPin6 = 6; // the number of the pushbutton pin -- PIN6

// variables will change:
int buttonState5 = 0; // variable for reading the pushbutton status for tare
int buttonState6 = 0; // variable for reading the pushbutton status for weight added
long weight = 0;
long tar = 0;
long reading = 0;
long deck_max = 315; // how much the deck weighs total
HX711 scale;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  // baudrate
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
//  scale.tare();
}

void loop() {
//  scale.tare();
  // read the state of the pushbutton value:
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  if (buttonState5 == HIGH) {
        // reading = scale.read();
        tar = -(scale.read());
        Serial.print("HX711 TARE reading: ");
        weight = 0;
        Serial.println(weight);
        delay(1000);
        // weight = 0;
        // turn LED on:
      } 
      else if (buttonState6 == HIGH) {
        reading = scale.read();
        weight = (tar+reading)/100;
        Serial.print("HX711 reading: ");
        Serial.println(weight);
        delay(1000);
      }
}
