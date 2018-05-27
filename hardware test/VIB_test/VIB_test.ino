// Vibration sensor on port A9

void setup() {
  Serial.begin(9600);
}

void loop() {
   if(analogRead(9)<1022){
     Serial.println("bang");
   }
}
