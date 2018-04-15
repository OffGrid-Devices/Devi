// Potententiometers 1~6 on ports 0~5
// Potentiometer 7 on port 6
// Potentiometer 8 on port 7

#define P1 0
#define P2 1
#define P3 2
#define P4 3
#define P5 4
#define P6 5
#define P7 6
#define P8 7

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(P1));
  Serial.print(" ");
  Serial.print(analogRead(P2));
  Serial.print(" ");
  Serial.print(analogRead(P3));
  Serial.print(" ");
  Serial.print(analogRead(P4));
  Serial.print(" ");
  Serial.print(analogRead(P5));
  Serial.print(" ");
  Serial.print(analogRead(P6));
  Serial.print(" ");
  Serial.print(analogRead(P7));
  Serial.print(" ");
  Serial.print(analogRead(P8));
  Serial.print(" ");

  Serial.println();
  delay(50);
}
