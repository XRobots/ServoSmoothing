#include <Servo.h>

int pot1;
int pot2;
int pot3;
int pot4;
int pot5;
int pot6;

float pot1Scaled;
float pot2Scaled;
float pot3Scaled;
float pot4Scaled;
float pot4aScaled;
float pot5Scaled;
float pot6Scaled;

float pot1Smoothed;
float pot2Smoothed;
float pot3Smoothed;
float pot4Smoothed;
float pot4aSmoothed;
float pot5Smoothed;
float pot6Smoothed;

float pot1SmoothedPrev;
float pot2SmoothedPrev;
float pot3SmoothedPrev;
float pot4SmoothedPrev;
float pot4aSmoothedPrev;
float pot5SmoothedPrev;
float pot6SmoothedPrev;

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

  pot1 = analogRead(A0);
  pot2 = analogRead(A1);
  pot3 = analogRead(A2);
  pot4 = analogRead(A3);
  pot5 = analogRead(A4);
  pot6 = analogRead(A5);

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
  
  pot1Smoothed = (pot1Scaled * 0.02) + (pot1SmoothedPrev * 0.98);
  pot2Smoothed = (pot2Scaled * 0.02) + (pot2SmoothedPrev * 0.98);
  pot3Smoothed = (pot3Scaled * 0.02) + (pot3SmoothedPrev * 0.98);
  pot4Smoothed = (pot4Scaled * 0.05) + (pot4SmoothedPrev * 0.95);
  pot4aSmoothed = (pot4aScaled * 0.05) + (pot4aSmoothedPrev * 0.95);
  pot5Smoothed = (pot5Scaled * 0.02) + (pot5SmoothedPrev * 0.98);
  pot6Smoothed = (pot6Scaled * 0.02) + (pot6SmoothedPrev * 0.98);  

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

  servo1.writeMicroseconds(pot1Smoothed);
  servo2.writeMicroseconds(pot6Smoothed - pot5Smoothed);
  servo3.writeMicroseconds(pot6Smoothed + pot5Smoothed);

  servo5.writeMicroseconds(pot2Smoothed);
  servo7.writeMicroseconds(pot2Smoothed);

  servo4.writeMicroseconds(pot4Smoothed);
  servo6.writeMicroseconds(pot4aSmoothed);

  

  delay(5);                      // run loop 200 times/second

}
