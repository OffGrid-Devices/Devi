#define ARRSIZE 8 // pin array size


byte d1Pins[] = {37, 36, 35, 38, 41, 40, 39, 34};
byte d2Pins[] = {45, 44, 43, 46, 49, 48, 47, 42};

void setup(){
  for(int j = 34; j<50; j++){
    pinMode(j, OUTPUT);
  }
}

void loop(){
  displayNum(6, d1Pins, true);
  displayNum(6, d2Pins, false);
}

void displayNum(byte num, byte pins[], boolean dot){
  switch(num){
    case 0:
    digitalWrite(pins[0], HIGH);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 1:
    digitalWrite(pins[0], LOW);
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    digitalWrite(pins[4], LOW);
    digitalWrite(pins[5], LOW);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 2:
    digitalWrite(pins[0], HIGH);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], LOW);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 3:
    digitalWrite(pins[0], LOW);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], LOW);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 4:
    digitalWrite(pins[0], LOW);
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], LOW);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 5:
    digitalWrite(pins[0], LOW);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], LOW);
    displayDot(pins, dot);
    break;
    
    case 6:
    digitalWrite(pins[0], HIGH);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], LOW);
    digitalWrite(pins[6], LOW);
    displayDot(pins, dot);
    break;
    
    case 7:
    digitalWrite(pins[0], LOW);
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    digitalWrite(pins[4], LOW);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 8:
    digitalWrite(pins[0], HIGH);
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    case 9:
    digitalWrite(pins[0], LOW);
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], HIGH);
    digitalWrite(pins[6], HIGH);
    displayDot(pins, dot);
    break;
    
    default: // if not a valid number turn display off
      for(int i = 0; i < ARRSIZE; i++){
        digitalWrite(pins[i], LOW);
      }
    break; 
  }
}

void displayDot(byte pins[], boolean dot){
  if(dot) digitalWrite(pins[7], HIGH);
  else digitalWrite(pins[7], LOW);  
}
