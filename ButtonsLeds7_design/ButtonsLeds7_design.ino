#define BUTTON_PIN 2 
#define LED_PIN 9
#define BOUNCE_TIME 50
#define PRESSED HIGH

// Latch pin (ST_CP) of 74HC595 to pin 5
int latchPin = 5;      
// Latch pin (SH_CP) of 74HC595 to pin 6
int clockPin = 3;
// Data pin (DS of 74HC595 to pin 6
int dataPin = 7;       
// Make sure MR is HIGH (connect ot Vcc)

int count_of_unit = 0;

int previous = 0;
volatile long int press_time = 0;
volatile bool pressed_candidate = false;
volatile long int hold_time = 0;
volatile int press_count = 0;
bool button_pressed = false;
bool led_is_glowing = false;
int lumenocity = 255;
bool direction_up = true;

// 2 3 4 5 6 7 8 9 
// A B . C D E G F
bool digits[10][8] = {
  {1,1,0,1,1,1,0,1},  // 0
  {0,1,0,1,0,0,0,0},  // 1
  {1,1,0,0,1,1,1,0},  // 2
  {1,1,0,1,1,0,1,0},  // 3
  {0,1,0,1,0,0,1,1},  // 4
  {1,0,0,1,1,0,1,1},  // 5
  {1,0,1,1,1,1,1,1},  // 6
  {1,1,0,1,0,0,0,0},  // 7
  {1,1,0,1,1,1,1,1},  // 8
  {1,1,1,1,1,0,1,1}   // 9
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);

  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, process_button_click, RISING);
  show_number(0);
}

void show_number(int digit) {
  digitalWrite(latchPin, LOW);
  for(int i = 7; i >=0; i--) {
    shift_and_set(digits[digit][i]);
  }
  digitalWrite(latchPin, HIGH);
}

void loop() {

  int val = digitalRead(BUTTON_PIN);
  if(pressed_candidate == true and 
     millis() - press_time > BOUNCE_TIME) {
    if(digitalRead(BUTTON_PIN) == PRESSED){
      button_pressed = true;
    } else {
      pressed_candidate = false;
    }
  }

  // hold time counter
  if(button_pressed == true) {    
  	hold_time = millis() - press_time;
    Serial.print("Button is hold ");
    Serial.println(hold_time);

    if(hold_time > 180 && led_is_glowing){
      if (lumenocity < 255 and lumenocity > 0 and direction_up){
        lumenocity++;
      }
      else if (lumenocity < 255 and lumenocity > 0 and !direction_up){
        lumenocity--;
      }
      else if (lumenocity == 0){
        lumenocity++;
        direction_up = true;
      }
      else if (lumenocity == 255){
        lumenocity--;
        direction_up = false;
      }

      count_of_unit = hold_time / 3000;
      int digit = (int)(count_of_unit % 10);
      
      show_number(digit);

      analogWrite(LED_PIN, lumenocity);
    }
    
  } 
  // released event
  if(button_pressed == true and
     previous == PRESSED and
     val != PRESSED) {
    Serial.print("Button is released ");
    button_pressed = false;
    pressed_candidate = false;
    
    
    if(hold_time <= 180){
      Serial.println("Click!");
      if (led_is_glowing) {
        digitalWrite(LED_PIN, LOW);
        lumenocity = 255;
      } else {
        digitalWrite(LED_PIN, HIGH);
      }

      led_is_glowing = !led_is_glowing;
    }
    // else if (hold_time > 180){
    //   analogWrite(LED_PIN, lumenocity);
    // }
  }
  previous = val;
}

void process_button_click() {
  if (pressed_candidate == false) {
    press_time = millis();
    pressed_candidate = true;
    // button_pressed = true;
    press_count++;
    hold_time = 0;
  }
}

void shift_and_set(bool val) {
  digitalWrite(dataPin, val);
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);
}