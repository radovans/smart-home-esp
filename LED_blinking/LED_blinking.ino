// Blinking LED on ESP32
#define LED 2

bool state = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, state);
  state = !state;
  delay(500);
}
