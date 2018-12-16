// Temperature and humidity meter DHT 22

#include "DHT.h"
#define DHTpin 4
#define DHTtype DHT22

DHT dht22(DHTpin, DHTtype);

void setup() {
  Serial.begin(115200);
  dht22.begin();
}

void loop() {
  float temperature = dht22.readTemperature();
  float humidity = dht22.readHumidity();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degree Celsius, ");
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(4000);
}
