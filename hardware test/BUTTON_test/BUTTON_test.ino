// Buttons 1~6 on ports 14~19
// Button 7 on port 20
// Button 8 on port 21
#define B1 14
#define B2 15
#define B3 16
#define B4 17
#define B5 18
#define B6 19
#define B7 20
#define B8 21

void setup() {
  Serial.begin(9600);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);
  pinMode(B7, INPUT);
  pinMode(B8, INPUT);
}

void loop() {
  Serial.print(digitalRead(B1));
  Serial.print(" ");
  Serial.print(digitalRead(B2));
  Serial.print(" ");
  Serial.print(digitalRead(B3));
  Serial.print(" ");
  Serial.print(digitalRead(B4));
  Serial.print(" ");
  Serial.print(digitalRead(B5));
  Serial.print(" ");
  Serial.print(digitalRead(B6));
  Serial.print(" ");
  Serial.print(digitalRead(B7));
  Serial.print(" ");
  Serial.print(digitalRead(B8));
  Serial.print(" ");

  Serial.println();
  delay(10);
}
