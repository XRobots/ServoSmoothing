#include <Servo.h>

int pot1 = 512;
int pot2 = 512;
int pot3 = 512;
int pot4 = 512;
int pot5 = 512;
int pot6 = 512;

float pot1Scaled;
float pot2Scaled;
float pot3Scaled;
float pot4Scaled;
float pot4aScaled;
float pot5Scaled;
float pot6Scaled;

float pot1Smoothed = 512;
float pot2Smoothed = 512;
float pot3Smoothed = 512;
float pot4Smoothed = 512;
float pot4aSmoothed = 512;
float pot5Smoothed = 512;
float pot6Smoothed = 512;

float pot1SmoothedPrev = 512;
float pot2SmoothedPrev = 512;
float pot3SmoothedPrev = 512;
float pot4SmoothedPrev = 512;
float pot4aSmoothedPrev = 512;
float pot5SmoothedPrev = 512;
float pot6SmoothedPrev = 512;

unsigned long currentMillis;
long previousMillis = 0;    // set up timers
long interval = 5;        // time constant for timer

int stepFlag = 0;
long previousStepMillis = 0;

Servo servo1;
Servo servo2;
Servo servo3;

Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;

void setup() {

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Serial.begin(115200);

  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  
  servo4.attach(7);
  servo5.attach(8);
  servo6.attach(9);
  servo7.attach(10);

  servo1.writeMicroseconds(1200);
  servo2.writeMicroseconds(1650);
  servo3.writeMicroseconds(1650);
  
  servo4.writeMicroseconds(1500);
  servo5.writeMicroseconds(1550);
  servo6.writeMicroseconds(1500);
  servo7.writeMicroseconds(1450);

}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {  // start 5ms timed loop  
      previousMillis = currentMillis;

      // step sequencer

      if (stepFlag == 0 && currentMillis - previousStepMillis > 500) {
        pot1 = 512;
        pot6 = 512;
        stepFlag = 1;           
        previousStepMillis = currentMillis;
      }

      else if (stepFlag == 1 && currentMillis - previousStepMillis > 1000) {
        pot1 = 1024;
        pot2 = 1024;
        pot6 = 0;
        stepFlag = 2;           
        previousStepMillis = currentMillis;
      }

      else if (stepFlag == 2 && currentMillis - previousStepMillis > 1500) {
        pot1 = 0;
        pot6 = 1024;
        pot2 = 0;
        stepFlag = 3;           
        previousStepMillis = currentMillis;
      }

      if (stepFlag == 3 && currentMillis - previousStepMillis > 1500) {
        pot5 = 512;
        pot6 = 0;
        pot2 = 512;
        stepFlag = 4;           
        previousStepMillis = currentMillis;
      }

      if (stepFlag == 4 && currentMillis - previousStepMillis > 1500) {
        pot4 = 0;
        stepFlag = 5;           
        previousStepMillis = currentMillis;
      }
      if (stepFlag == 5 && currentMillis - previousStepMillis > 1500) {
        pot4 = 512;
        stepFlag = 1;           
        previousStepMillis = currentMillis;
      }

      // end of step sequencer

      
    
      // scale all pots for the servo microseconds range
    
      pot1Scaled = ((pot1 - 512) * -1.6) + 1200;
      pot2Scaled = (pot2 - 512) + 1500;
      pot3Scaled = (pot3 - 512) + 1500;
      pot4Scaled = ((pot4 - 512) * 1.2) + 1500;
      pot4aScaled = ((pot4 - 512) * -1.2) + 1500;
      pot5Scaled = (pot5 - 512) * 1.5;
      pot6Scaled = (pot6 - 512) + 1650;
    
      pot4Scaled = constrain(pot4Scaled,900,1500);
      pot4aScaled = constrain(pot4aScaled,1500,2100);
    
      // smooth pots
      
      pot1Smoothed = (pot1Scaled * 0.01) + (pot1SmoothedPrev * 0.99);
      pot2Smoothed = (pot2Scaled * 0.01) + (pot2SmoothedPrev * 0.99);
      pot3Smoothed = (pot3Scaled * 0.01) + (pot3SmoothedPrev * 0.99);
      pot4Smoothed = (pot4Scaled * 0.05) + (pot4SmoothedPrev * 0.95);
      pot4aSmoothed = (pot4aScaled * 0.05) + (pot4aSmoothedPrev * 0.95);
      pot5Smoothed = (pot5Scaled * 0.01) + (pot5SmoothedPrev * 0.99);
      pot6Smoothed = (pot6Scaled * 0.01) + (pot6SmoothedPrev * 0.99);  
    
      // bookmark previous values
    
      pot1SmoothedPrev = pot1Smoothed;
      pot2SmoothedPrev = pot2Smoothed;
      pot3SmoothedPrev = pot3Smoothed;
      pot4SmoothedPrev = pot4Smoothed;
      pot4aSmoothedPrev = pot4aSmoothed;
      pot5SmoothedPrev = pot5Smoothed;
      pot6SmoothedPrev = pot6Smoothed;
  
      Serial.print(pot1Smoothed);
      Serial.print(" , ");
      Serial.print(pot2Smoothed);
      Serial.print(" , ");
      Serial.print(pot3Smoothed);
      Serial.print(" , ");
      Serial.print(pot4Smoothed);
      Serial.print(" , ");
      Serial.print(pot5Smoothed);
      Serial.print(" , ");
      Serial.println(pot6Smoothed);

      // write servos

      servo1.writeMicroseconds(pot1Smoothed);                     // neck rotate
      servo2.writeMicroseconds(pot6Smoothed - pot5Smoothed);      // neck side-side
      servo3.writeMicroseconds(pot6Smoothed + pot5Smoothed);      // neck front-back
    
      servo5.writeMicroseconds(pot2Smoothed);                     // eyeballs side-side
      servo7.writeMicroseconds(pot2Smoothed);
    
      servo4.writeMicroseconds(pot4Smoothed);                     // eyelids
      servo6.writeMicroseconds(pot4aSmoothed); 

  } // end of timed loop


} // end if main loop
