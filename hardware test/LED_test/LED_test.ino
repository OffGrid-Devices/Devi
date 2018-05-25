#define LED1 17 // PH0
#define LED2 16 // PH1
#define LED3 6 // PH3
#define LED4 7 // PH4
#define LED5 8 // PH5
#define LED6 9 // PH6
#define LED7 10 // PB4
#define LEDR 5 // PE3
#define LEDG 3 // PE4
#define LEDB 2 // PE5

int dly = 500;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  
}

void loop() { 
  lightLed(LEDB, LED1);
  lightLed(LED1, LED2);
  lightLed(LED2, LED3);
  lightLed(LED3, LED4);
  lightLed(LED4, LED5);
  lightLed(LED5, LED6);
  lightLed(LED6, LED7);
  lightLed(LED7, LEDR);
  lightLed(LEDR, LEDG);
  lightLed(LEDG, LEDB);
  
}

void lightLed(int _p, int p){
  digitalWrite(_p, LOW);
  digitalWrite(p, HIGH);
  delay(dly);
}

