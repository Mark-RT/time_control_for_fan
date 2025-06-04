#define pir     0
#define mosfet  1
#define tumbler 4

bool active1 = 0;
bool active2 = 1;

uint32_t timing1 = 0;
uint32_t timing2 = 0;

int32_t potent = 0;

int32_t val_potent1 = 0;
int32_t val_potent2 = 0;

void setup() {
  pinMode(pir, INPUT_PULLUP);
  pinMode(mosfet, OUTPUT);
  pinMode(tumbler, INPUT);
}

void loop() {
  potent = analogRead(1);
  if (!digitalRead(tumbler)) {

    val_potent1 = potent * 106 + 10000;

    if (digitalRead(pir) && !active1) {
      active1 = 1;
      digitalWrite(mosfet, HIGH);
      timing1 = millis();
      active2 = 1;
    }

    if (active1 && millis() - timing1 > val_potent1) {
      digitalWrite(mosfet, LOW);
      active1 = 0;
    }

  }

  else {
    val_potent2 = potent * 351 + 10000;

    if (active2 && millis() - timing2 > val_potent2 / 1.6) {
      digitalWrite(mosfet, HIGH);
      active2 = 0;
      timing2 = millis();
    }

    else if (!active2 && millis() - timing2 > val_potent2) {
      digitalWrite(mosfet, LOW);
      active2 = 1;
      timing2 = millis();
    }
  }
}
