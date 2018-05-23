#define BUTTON1 22 // PA0
#define BUTTON2 23 // PA1
#define BUTTON3 24 // PA2
#define BUTTON4 25 // PA3
#define BUTTON5 26 // PA4
#define BUTTON6 27 // PA5
#define BUTTON7 28 // PA6
#define BUTTON8 29 // PA7

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  pinMode(BUTTON5, INPUT);
  pinMode(BUTTON6, INPUT);
  pinMode(BUTTON7, INPUT);
  pinMode(BUTTON8, INPUT);
}

void loop() {
  Serial.print(digitalRead(BUTTON1));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON2));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON3));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON4));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON5));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON6));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON7));
  Serial.print(" ");
  Serial.print(digitalRead(BUTTON8));
  Serial.print(" ");

  Serial.println();
  delay(10);
}
