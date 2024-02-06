#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5

void zero23(){
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_3, LOW); 
}

void printStates(){
  int states[4];
  states[0] = digitalRead(PIN_2);
  states[1] = digitalRead(PIN_3);
  states[2] = digitalRead(PIN_4);
  states[3] = digitalRead(PIN_5);
  for (int i = 0; i < 4; i++){
    Serial.print(states[i]);
  }
  Serial.println();
  delay(400);
}


void setup() {
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, INPUT_PULLUP);
  pinMode(PIN_5, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(PIN_4) == LOW){
    digitalWrite(PIN_2, LOW);
    digitalWrite(PIN_3, HIGH);
    if (digitalRead(PIN_4) == LOW){
      Serial.println("Нажата кнопка 1");  
      printStates();  
      zero23(); 
    }
    digitalWrite(PIN_3, LOW);
    digitalWrite(PIN_2, HIGH);
    if (digitalRead(PIN_4) == LOW){
      Serial.println("Нажата кнопка 3");  
      printStates();    
      zero23(); 
    }
    zero23();
  }


  if (digitalRead(PIN_5) == LOW){
    digitalWrite(PIN_2, LOW);
    digitalWrite(PIN_3, HIGH);
    if (digitalRead(PIN_5) == LOW){
      Serial.println("Нажата кнопка 2"); 
      printStates();     
      zero23();
    }
    digitalWrite(PIN_3, LOW);
    digitalWrite(PIN_2, HIGH);
    if (digitalRead(PIN_5) == LOW){
      Serial.println("Нажата кнопка 4");   
      printStates();   
      zero23(); 
    }
    zero23();
  }


  delay(500); 
  Serial.println("____________________________");
}
