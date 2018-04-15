//Display LED digit 1 on ports: 34 ~ 41
// Display LED digit 2 on ports: 42 ~ 49

int i = 34; 
void setup() {
  for(int j = 34; j<50; j++){
    pinMode(j, OUTPUT);
  }
}

void loop() {
  digitalWrite(i, HIGH);
  for(int g = 34; g< 50; g++){
    if (g!= i){
      digitalWrite(g, LOW);
    }
  }
  delay(500);
  if(i < 50) { i++; }
  else{ i = 34; }
}
