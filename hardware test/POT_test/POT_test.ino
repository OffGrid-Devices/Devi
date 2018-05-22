#define POT1 0
#define POT2 1
#define POT3 2
#define POT4 3
#define POT5 4
#define POT6 5
#define POT7 6

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(POT1));
  Serial.print(" ");
  Serial.print(analogRead(POT2));
  Serial.print(" ");
  Serial.print(analogRead(POT3));
  Serial.print(" ");
  Serial.print(analogRead(POT4));
  Serial.print(" ");
  Serial.print(analogRead(POT5));
  Serial.print(" ");
  Serial.print(analogRead(POT6));
  Serial.print(" ");
  Serial.print(analogRead(POT7));
  Serial.print(" ");

  Serial.println();
  delay(50);
}
