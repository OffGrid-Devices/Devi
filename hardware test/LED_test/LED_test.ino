// LEDS 1~6 on ports 5 to 10
// LED 7 on port 13
// LED RGB on port 4 (red), 3 (green), 2(blue) 

void setup() {
  // Leds 1~6
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  // Led 7
  pinMode(13, OUTPUT);
  // Led RGB
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() { 
  lightSmallLeds();
  lightBigLeds();
}

void lightSmallLeds(){ // light Leds 1~6
  digitalWrite(10, LOW);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(500);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(500); 
}

void lightBigLeds(){
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}
