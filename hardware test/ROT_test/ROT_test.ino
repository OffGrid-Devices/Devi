#define ROT1 37
#define ROT2 36
#define ROT3 35
#define ROT4 34
#define ROT5 33
#define ROT6 32
#define ROT7 31
#define ROT8 30
#define ROT9 21
#define ROT10 20
#define ROT11 19
#define ROT12 18 //

void setup() {
  Serial.begin(9600);
  pinMode(ROT1, INPUT);
  pinMode(ROT2, INPUT);
  pinMode(ROT3, INPUT);
  pinMode(ROT4, INPUT);
  pinMode(ROT5, INPUT);
  pinMode(ROT6, INPUT);
  pinMode(ROT7, INPUT);
  pinMode(ROT8, INPUT);
  pinMode(ROT9, INPUT);
  pinMode(ROT10, INPUT);
  pinMode(ROT11, INPUT);
  pinMode(ROT12, INPUT);
}

void loop() {
  Serial.print(digitalRead(ROT1));
  Serial.print(" ");
  Serial.print(digitalRead(ROT2));
  Serial.print(" ");
  Serial.print(digitalRead(ROT3));
  Serial.print(" ");
  Serial.print(digitalRead(ROT4));
  Serial.print(" ");
  Serial.print(digitalRead(ROT5));
  Serial.print(" ");
  Serial.print(digitalRead(ROT6));
  Serial.print(" ");
  Serial.print(digitalRead(ROT7));
  Serial.print(" ");
  Serial.print(digitalRead(ROT8));
  Serial.print(" ");
  Serial.print(digitalRead(ROT9));
  Serial.print(" ");
  Serial.print(digitalRead(ROT10));
  Serial.print(" ");
  Serial.print(digitalRead(ROT11));
  Serial.print(" ");
  Serial.println(digitalRead(ROT12));
}
