

#include <Average.h>
#include <EasyScheduler.h>
#include "HX711.h"
#include <SoftwareSerial.h>

// HX711.DOUT - pin #A1
// HX711.PD_SCK - pin #A0

HX711 scale(A1, A0);  // parameter "gain" is ommited; the default value 128 is used by the library
SoftwareSerial VFD(6,7); // RX, TX

Average<float> ave1(20);

static float f1 = 0;
static char f1f[8];
static float wt1 = 0;
static float wt1avg = 0;
static char wt1f[8];
static float lbs = 0;
static char lbsf[8];
static float raw = 0;
static char rawf[16];

 const int zeroPin = 11;     // the number of the pushbutton pin
 int zeroState = 0;         // variable for reading the pushbutton status
 
int bar;

Schedular Task1;
Schedular Task2;

void setup() {
  Task1.start();
  Task2.start();
 
  pinMode(zeroPin, INPUT);
  
  VFD.begin(57600);
  VFD.write(0x19); 
  VFD.write(0x1B);  
  VFD.write(0xF9);
  
  scale.set_scale(1674640.f);                      // this value is obtained by calibrating the scale with known weights

delay(200);

  scale.tare();            // reset the scale to 0
  scale.tare();            // reset the scale to 0
  scale.tare();            // reset the scale to 0

delay(200);

  scale.tare();            // reset the scale to 0

  VFD.write(0x11);    
  VFD.write(0x08); 
  VFD.write(byte(0x02));          
  VFD.write(0x08); 
  VFD.write(0x3D);
//  Tick 100%    
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(byte(0x02));          
  VFD.write(0x0A); 
  VFD.write(byte(0x02));
//  Tick 90%   
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x08);          
  VFD.write(0x0A); 
  VFD.write(0x08);   
//  Tick 80% 
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x0E);          
  VFD.write(0x0A); 
  VFD.write(0x0E);
//  Tick 70% 
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x14);          
  VFD.write(0x0A); 
  VFD.write(0x14);
//  Tick 60%
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x1A);          
  VFD.write(0x0A); 
  VFD.write(0x1A);
//  Tick 50%
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x20);          
  VFD.write(0x0A); 
  VFD.write(0x20);
//  Tick 40%  
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x26);          
  VFD.write(0x0A); 
  VFD.write(0x26);
//  Tick 30%  
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x2C);          
  VFD.write(0x0A); 
  VFD.write(0x2C);
//  Tick 20%  
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x32);          
  VFD.write(0x0A); 
  VFD.write(0x32);
  //  Tick 10%  
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x38);          
  VFD.write(0x0A); 
  VFD.write(0x38);
    //  Tick 0%  
  VFD.write(0x11);    
  VFD.write(0x07); 
  VFD.write(0x3E);          
  VFD.write(0x0A); 
  VFD.write(0x3E);
}


void loop() {
    Task1.check(funct1,1);
    Task2.check(funct2,10); 
}    

   void funct1(){
  wt1 = scale.get_units() * 1000.000;
  lbs = wt1avg * 0.035274;
  f1 = wt1avg * 9.80665 / 1000.0;   

   
  if (digitalRead(zeroPin) == LOW) {
  VFD.write(0x1B); 
  VFD.write(0x98); 
  VFD.write(0x01);                                            // Set VFD font size (5x7)
  VFD.write(0x10); 
  VFD.write(0x26); 
  VFD.write(0x3F);                                            // Set cursor position
  VFD.print("cell zeroing");  
    scale.tare();
    scale.tare();
    scale.tare();
    scale.tare();
    scale.tare();                                              // reset the scale to 0
  VFD.write(0x10); 
  VFD.write(0x26); 
  VFD.write(0x3F);                                            // Set cursor position
  VFD.print("             ");      
  } 


}


   void funct2(){
//  raw = scale.read();
  ave1.push(wt1);
  wt1avg = ave1.mean();

  
   bar = (wt1avg / 1000.000 * 60);

     if (bar <= 0) {     
  bar = 0;               
  }

     if (bar >= 60) {     
  bar = 60;              
  }
 
  dtostrf(wt1avg,7, 2, wt1f);
  dtostrf(lbs,7, 3, lbsf);  
  dtostrf(f1,7, 3, f1f);
//  dtostrf(raw, 10, 0, rawf);  
  
//  Serial.print("one reading:\t");
//  Serial.println(scale.get_units(), 2);
//  Serial.print("\t| average:\t");
//  Serial.println(scale.get_units(10), 1);

//  scale.power_down();             // put the ADC in sleep mode
//  delay(100);
//  scale.power_up();

// DISPLAY FORCE IN NEWTONS
  VFD.write(0x1B); 
  VFD.write(0x98); 
  VFD.write(0x03);                                            // Set VFD font size (7x15)                                            // Set VFD font size (10x14)
  VFD.write(0x10); 
  VFD.write(0x2A); 
  VFD.write(0x11);          // Set cursor position
  VFD.print("");
  VFD.print(f1f); 
  VFD.print(" ");  
  VFD.print("N");

// DISPLAY WEIGHT IN KG
  VFD.write(0x1B); 
  VFD.write(0x98); 
  VFD.write(0x03);                                            // Set VFD font size (7x15)                                            // Set VFD font size (10x14)
  VFD.write(0x10); 
  VFD.write(0x2A); 
  VFD.write(0x21);          // Set cursor position
  VFD.print("");
  VFD.print(wt1f); 
  VFD.print(" ");  
  VFD.print("g");

// DISPLAY WEIIGHT IN LBS
  VFD.write(0x1B); 
  VFD.write(0x98); 
  VFD.write(0x03);                                            // Set VFD font size (7x15)                                            // Set VFD font size (10x14)
  VFD.write(0x10); 
  VFD.write(0x2A); 
  VFD.write(0x31);          // Set cursor position
  VFD.print("");
  VFD.print(lbsf); 
  VFD.print(" ");
  VFD.print("oz");


/* 
// DISPLAY RAW ADC READING
  VFD.write(0x1C); 
  VFD.write(0x98); 
  VFD.write(0x03);                                            // Set VFD font size (7x15)                                            // Set VFD font size (10x14)
  VFD.write(0x10); 
  VFD.write(0x2A); 
  VFD.write(0x39);          // Set cursor position
  VFD.print("");
  VFD.print(rawf); 
*/


  VFD.write(0x11);    
  VFD.write(byte(0x02)); 
  VFD.write(byte(61-bar));          
  VFD.write(0x05); 
  VFD.write(0x3E);

  VFD.write(0x12);        
  VFD.write(byte(0x00)); 
  VFD.write(byte(0x00));          
  VFD.write(0x05); 
  VFD.write(61-bar);

   }