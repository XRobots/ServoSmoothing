int switch1;
float switch1Smoothed = 0;

void setup() {

  Serial.begin(115200);

  pinMode(12, INPUT_PULLUP);

}

void loop() {

  switch1 = digitalRead(12);      // read switch
  switch1 = switch1 * 100;        // multiply by 100

  // *** smoothing ***

  switch1Smoothed = (switch1 * 0.05) + (switch1Smoothed * 0.95);

  // *** end of smoothing ***

  Serial.print(switch1);                  // print to serial terminal/plotter
  Serial.print(" , ");   
  Serial.println(switch1Smoothed);

  delay(10);                      // run loop 100 times/second

}
