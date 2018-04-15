// using rotarySwitch=1 to pin 8 and rotarySwitch=2 to pin 9


int rotSwitch = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 22; i < 34; i++){
    pinMode(i, INPUT);
  }
}

void loop() {
  for (int i = 22; i < 34; i++) {
    if (digitalRead(i) > 0) {
      rotSwitch = i-21;
      //rotSwitch = rotSwitch;
    }
  }
  Serial.println(rotSwitch);
}
