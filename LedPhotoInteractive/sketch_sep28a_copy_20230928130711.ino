#define SENSOR_PIN A0
#define PIN2 3

bool streaming = false;
bool handly = false;
bool manual = false;
bool alarm = false;
bool send_one_value = false;
unsigned long previous_send_time = 0;
unsigned long send_count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN2, OUTPUT);
}

void loop() {
  long current_time = millis();
  data_reading();
  if (manual){
    if (handly){
  	digitalWrite(PIN2, HIGH);
  }
    else if (handly == false){
      digitalWrite(PIN2, LOW);
    }
  }
  else if (alarm){
    if (current_time / 100 != send_count){
      
      previous_send_time = previous_send_time + 100;
      send_count = current_time / 100;
      
      if (send_count % 10 == 0) {
      	digitalWrite(PIN2, HIGH); 
      }else{
      	digitalWrite(PIN2, LOW);
      }
    }
  }
  else {
    int val = send_photo_data();
    digitalWrite(PIN2, val < 750 ? HIGH : LOW);
  }
}

int send_photo_data() {
  int val = analogRead(SENSOR_PIN);
  return val;
}

void data_reading() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.println(command);
    if (command == 'o') { // o for Switch off or on
      if (handly){
        handly = false;
      }
      else {
        handly = true;
      }
    } 
    if (command == 'm') { // m for manual mode
      if (manual){
        manual = false;
      }
      else {
        manual = true;
      }
      alarm = false;
    }
    if (command == 'a') { // a for alarm system
      if (alarm){
        alarm = false;
      }
      else {
        alarm = true;
      }
      manual = false;
    }
  }
}
