// Tilt button on port A8

void setup() {
  Serial.begin(9600);
}

void loop() {
   Serial.println(analogRead(8));
}
