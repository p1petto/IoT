int states[][2][4] = {
  {{1, 0, 0, 1}, {0, 0, 0, 0}}, // 1
  {{1, 0, 1, 0}, {0, 0, 0, 0}}, // 2
  {{0, 1, 0, 1}, {0, 0, 0, 0}}, // 3
  {{0, 1, 1, 0}, {0, 0, 0, 0}}, // 4
  {{1, 0, 0, 0}, {0, 0, 0, 0}}, // 1,2
  {{0, 1, 0, 0}, {0, 0, 0, 0}}, // 3,4
  {{1, 1, 0, 1}, {0, 0, 0, 0}}, // 1,3
  {{1, 1, 1, 0}, {0, 0, 0, 0}}, // 2,4
  {{1, 0, 0, 1}, {0, 1, 1, 0}}, // 1,4
  {{1, 0, 1, 0}, {0, 1, 0, 1}}, // 2,3
  {{1, 0, 0, 0}, {0, 1, 0, 1}}, // 1,2,3
  {{1, 0, 1, 0}, {0, 1, 0, 0}}, // 2,3,4
  {{1, 0, 0, 1}, {0, 1, 0, 0}}, // 3,4,1
  {{1, 0, 0, 0}, {0, 1, 1, 0}}, // 4,1,2
  {{1, 0, 0, 0}, {0, 1, 0, 0}}, // 1,2,3,4
  {{0, 0, 0, 0}, {0, 0, 0, 0}}  // nothing
};

void pinSwitch(int a, int b, int c, int d) {
  digitalWrite(2, a);
  digitalWrite(3, b);
  digitalWrite(12, c);
  digitalWrite(13, d);
}

void lowerp() {
  pinSwitch(0, 0, 0, 0);
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++) {
    for (int j = 0; j < 400; j++) {
      pinSwitch(states[i][0][0], states[i][0][1], states[i][0][2], states[i][0][3]);
      delay(1);
      lowerp();
      pinSwitch(states[i][1][0], states[i][1][1], states[i][1][2], states[i][1][3]);
      delay(1);
      lowerp();
    }
  }
}
