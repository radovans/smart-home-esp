#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "UPC7265954";
const char* password = "***";

WiFiServer server(80);
String header;

#include "DHT.h"
#define DHTpin 4
#define DHTtype DHT22

DHT dht22(DHTpin, DHTtype);

void setup() {
  Serial.begin(115200);
  dht22.begin();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:application/json");
            client.println("Connection: close");
            client.println();

            float temperature = dht22.readTemperature();
            float humidity = dht22.readHumidity();
            client.print("{");
            client.print("\"temperature\":\"");
            client.print(temperature);
            client.print("\",");
            client.print("\"humidity\":\"");
            client.print(humidity);
            client.print("\"}");
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
