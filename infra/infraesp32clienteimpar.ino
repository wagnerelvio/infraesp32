//Cliente-03
#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 4        // Pino do DHT11
#define DHTTYPE DHT11   // Tipo do sensor DHT

DHT dht(DHTPIN, DHTTYPE);
const int ldrPin = 35;     // Pino do LDR
const int mq135Pin = 34;   // Pino do MQ-135

const char* ssid = "ESP32_Server";
const char* password = "123456789";
const char* serverIP = "192.168.4.1";  // IP do ESPServer

WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(ldrPin, INPUT);
  pinMode(mq135Pin, INPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to ESPServer");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int ldrValue = analogRead(ldrPin);
  int mq135Value = analogRead(mq135Pin);

  if (client.connect(serverIP, 80)) {
    client.print("ID:Cliente03 T1:" + String(temperature) + " H1:" + String(humidity) +
                 " MQ1:" + String(mq135Value) + " LDR1:" + String(ldrValue) + "\n");
    client.stop();
  }
  delay(20000);
}
