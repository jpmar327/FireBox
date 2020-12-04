
#include "HX711.h"
#include "Servo.h"
// constants won't change. They're used here to set pin numbers:
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2; //Arduino pin connected to button's pin
const int LOADCELL_SCK_PIN = 3; // Arduino pin connected to load cell's pin
//const int BUTTON_PIN = 7; // Arduino pin connected to button's pin
const int SERVO_PIN  = 10; // Arduino pin connected to servo motor's pin

Servo servo; // create servo object to control a servo
HX711 scale; // create scale object to read load cell

// Button circuit wiring
const int buttonPin5 = 5; // the number of the pushbutton pin -- PIN5
const int buttonPin6 = 6; // the number of the pushbutton pin -- PIN6


int angle = 0;        // the current angle of servo motor
int buttonState5 = 0; // variable for reading the pushbutton status for tare
int buttonState6 = 0; // variable for reading the pushbutton status for weight added
long weight = 0;
long tar = 0;         // tare weight
long reading = 0;     // s tarting load cell weight reading
long deck_max = 315;  // how much the deck weighs total
int min = 100;
int max = 190;
int max_weight = random(min,max);

void setup() {
  Serial.begin(57600);          // initialize serial - baudrate
  pinMode(buttonPin5, INPUT);   // initialize the pushbutton pin 5 as an input
  pinMode(buttonPin6, INPUT);   // initialize the pushbutton pin 6 as an input
  servo.attach(SERVO_PIN);      // attaches the servo on pin 10 to the servo object
 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  servo.write(angle);
  randomSeed(analogRead(0));
  
//  scale.tare();
}

void loop() {
  
  //  scale.tare();
  // read the state of the pushbutton value:
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  if (buttonState5 == HIGH) {
    max_weight = random(min,max);
    // reading = scale.read();
    tar = -(scale.read());
    Serial.print("TARE READING: ");
    weight = 0;
    if(angle == 90) {
      angle = 0;
      servo.write(angle);
    }
    
    Serial.println(weight);
    Serial.print("NEW MAX WEIGHT: ");
    Serial.println(max_weight);
    delay(1000);

  }
  else if (buttonState6 == HIGH) {
    reading = scale.read();
    weight = (tar+reading)/100;

    
    if (weight >= max_weight) {
    
      if(angle == 0) {
        angle = 90;
        servo.write(angle);
        Serial.print("MAX WEIGHT HIT: ");
        Serial.println(max_weight);
       }
       Serial.print("WEIGHT READING: ");
       Serial.println(weight);
       delay(1000);

    }
  }
}
