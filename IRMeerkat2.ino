//enslaved meerkat
int receiver = 5;
//int receiver = 2;
int IRLED = 9;
int rEye = 6;
int gEye = 5;
int bEye = 3;

int rHeart = 10;
int bHeart = 11;
int gHeart = 13;

int trigger = 3;
int war_button = 0;
boolean shooting = false;

float heartFade = 11;
float heartFade2=249;
float heartAdd = 1;
float heartAdd2=20;

int value = 0;
int hit_value;
float hit_time;
int hit_time_out;
boolean war_toggle;


int count;
int lives;

void setupIR(){
  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12)|_BV(CS10);
  OCR1A = 210;
}

void pinSetup() {
  pinMode(IRLED, OUTPUT);    // IR LED pin 9
  pinMode(rEye, OUTPUT);
  pinMode(gEye, OUTPUT);
  pinMode(bEye, OUTPUT);
  pinMode(trigger, INPUT);
  pinMode(war_toggle, INPUT);
}

void setup() {
  pinSetup(); // this sets up the pins
  setupIR();
  hit_value = 500;
  hit_time_out = 10000;

  count = 0;
  lives = 5;
  
  Serial.begin(9600);
  
  while (analogRead(trigger) < 900) {
   // digitalWrite(bHeart, HIGH);
   // digitalWrite(bEye, HIGH);
   warmthMode();
   delay(5);
  }
  digitalWrite(bHeart, LOW);
  digitalWrite(bEye, LOW);
}

void loop() {
  //Serial.println(analogRead(war_button));
  //war_toggle = analogRead(war_button) > 900;
  
  war_toggle = true;
  if (war_toggle)
    warMode();
  else
    warmthMode();
  delay(5);
}

void warMode() {
  digitalWrite(rEye, HIGH);
  //Serial.println("war mode");
  int flashperiod=80;
  if (heartFade2==250){
        digitalWrite(rEye, LOW);
        analogWrite(rHeart,250);
        digitalWrite(bHeart,LOW);
        for (int j=0; j<10; j++){
          digitalWrite(rHeart,HIGH);
          //analogWrite(bHeart,heartFade2);
          digitalWrite(rEye,LOW);
          digitalWrite(gEye, HIGH);
          delay(flashperiod);
          digitalWrite(gEye, LOW);
          digitalWrite(bEye, HIGH);
          delay(flashperiod);
          digitalWrite(bEye, LOW);
          digitalWrite(rEye, HIGH);
          delay(flashperiod);
          digitalWrite(rEye, LOW);
          heartFade2-=1;
        }
     digitalWrite(rHeart,LOW);
     analogWrite(bHeart,heartFade2);   
    }
   analogWrite(bHeart,heartFade2);
  if (analogRead(trigger) >= 900){             // firing a shot
       OCR1A=210;       // change IR frequency 
       digitalWrite(rEye, LOW);
       digitalWrite(gEye, LOW);
       digitalWrite(bEye, HIGH);
       shooting = true;
       Serial.println("trigger");

    }
  else {                                      // Not shooting
      OCR1A = 0;
      digitalWrite(bEye, LOW);
      value = analogRead(receiver);
    
      if (value < hit_value && !shooting) {                // Get hit
        digitalWrite(gEye, HIGH);
        digitalWrite(rEye, LOW);
        delay(100);
        if (heartFade2>0){
          heartFade2-=heartAdd2;
        }
        else{
          heartFade2=250;
        }
        
        Serial.println("HIT");
      }
        
      else {
        digitalWrite(gEye, LOW);
      }
      shooting = false;
  }    
}

void warmthMode() {
    //Serial.println("warmth");
    digitalWrite(gEye, LOW);
    digitalWrite(rEye,LOW);
    digitalWrite(rHeart,LOW);
    int DISPLAY_TIME = 100;
    int greenIntensity, blueIntensity, redIntensity;
    
    OCR1A=0;
    if (heartFade >= 250 || heartFade < 10)
      heartAdd *= -1;
    
    heartFade += heartAdd;

    analogWrite(bHeart, heartFade);
    analogWrite(bEye, 250);
   // analogWrite(rEye, 100);
    
}

