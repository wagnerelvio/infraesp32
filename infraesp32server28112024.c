#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

// Configurações de rede e ThingSpeak
const char* ssid = "ESP32_Server";
const char* password = "123456789";
const char* wifiSSID = "REDE";         // Substitua pelo nome da sua rede Wi-Fi
const char* wifiPassword = "123456789"; // Substitua pela senha da sua rede Wi-Fi

// Chaves dos canais ThingSpeak
const String apiKeyCanal01 = "-----CHAVE-01---";  // Chave para ESP32Cliente01 e ESP32Cliente02
const String apiKeyCanal02 = "-----CHAVE-02---";  // Chave para ESP32Cliente03 e ESP32Cliente04
const String apiKeyCanal03 = "-----CHAVE-03---";  // Chave para ESP32Cliente05 e ESP32Cliente06

WiFiServer server(80);

float temperature1 = 0, humidity1 = 0, mq135Value1 = 0, ldrValue1 = 0;
float temperature2 = 0, humidity2 = 0, mq135Value2 = 0, ldrValue2 = 0;

void setup() {
  Serial.begin(115200);

  // Inicializa a rede interna para os clientes
  //WiFi.softAP(ssid, password);
  WiFi.softAP(ssid, password, 1, 0, 8);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Conecta-se à rede Wi-Fi externa
  WiFi.begin(wifiSSID, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  server.begin();
}

void loop() {
  // Verifica se há clientes conectados
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\n');
    Serial.println("Received data: " + request);

    // Identifica o cliente a partir do ID no pacote de dados
    if (request.startsWith("ID:Cliente01")) {
      sscanf(request.c_str(), "ID:Cliente01 T1:%f H1:%f MQ1:%f LDR1:%f",
             &temperature1, &humidity1, &mq135Value1, &ldrValue1);
      enviarDadosThingSpeak(apiKeyCanal01, temperature1, humidity1, mq135Value1, ldrValue1, 1);
    } else if (request.startsWith("ID:Cliente02")) {
      sscanf(request.c_str(), "ID:Cliente02 T2:%f H2:%f MQ2:%f LDR2:%f",
             &temperature2, &humidity2, &mq135Value2, &ldrValue2);
      enviarDadosThingSpeak(apiKeyCanal01, temperature2, humidity2, mq135Value2, ldrValue2, 2);
    } else if (request.startsWith("ID:Cliente03")) {
      sscanf(request.c_str(), "ID:Cliente03 T1:%f H1:%f MQ1:%f LDR1:%f",
             &temperature1, &humidity1, &mq135Value1, &ldrValue1);
      enviarDadosThingSpeak(apiKeyCanal02, temperature1, humidity1, mq135Value1, ldrValue1, 1);
    } else if (request.startsWith("ID:Cliente04")) {
      sscanf(request.c_str(), "ID:Cliente04 T2:%f H2:%f MQ2:%f LDR2:%f",
             &temperature2, &humidity2, &mq135Value2, &ldrValue2);
      enviarDadosThingSpeak(apiKeyCanal02, temperature2, humidity2, mq135Value2, ldrValue2, 2);
    } else if (request.startsWith("ID:Cliente05")) {
      sscanf(request.c_str(), "ID:Cliente05 T1:%f H1:%f MQ1:%f LDR1:%f",
             &temperature1, &humidity1, &mq135Value1, &ldrValue1);
      enviarDadosThingSpeak(apiKeyCanal03, temperature1, humidity1, mq135Value1, ldrValue1, 1);
    } else if (request.startsWith("ID:Cliente06")) {
      sscanf(request.c_str(), "ID:Cliente06 T2:%f H2:%f MQ2:%f LDR2:%f",
             &temperature2, &humidity2, &mq135Value2, &ldrValue2);
      enviarDadosThingSpeak(apiKeyCanal03, temperature2, humidity2, mq135Value2, ldrValue2, 2);
    } else if (request.startsWith("ID:Cliente07")) {
      sscanf(request.c_str(), "ID:Cliente07 T1:%f H1:%f MQ1:%f LDR1:%f",
             &temperature1, &humidity1, &mq135Value1, &ldrValue1);
      enviarDadosThingSpeak(apiKeyCanal04, temperature1, humidity1, mq135Value1, ldrValue1, 1);
    } else if (request.startsWith("ID:Cliente08")) {
      sscanf(request.c_str(), "ID:Cliente08 T2:%f H2:%f MQ2:%f LDR2:%f",
             &temperature2, &humidity2, &mq135Value2, &ldrValue2);
      enviarDadosThingSpeak(apiKeyCanal04, temperature2, humidity2, mq135Value2, ldrValue2, 2);
    }
    client.stop();
  }
}

// Função para enviar os dados ao ThingSpeak
void enviarDadosThingSpeak(String apiKey, float temp, float hum, float mq, float ldr, int cliente) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + apiKey;
    if (cliente == 1) {
      url += "&field1=" + String(temp) + "&field2=" + String(hum) + "&field3=" + String(mq) + "&field4=" + String(ldr);
    //} else {
    //  url += "&field5=" + String(temp) + "&field6=" + String(hum) + "&field7=" + String(mq) + "&field8=" + String(ldr);
    //}
     } else if (cliente == 2) {
      url += "&field5=" + String(temp) + "&field6=" + String(hum) + "&field7=" + String(mq) + "&field8=" + String(ldr);
     } else if (cliente == 3) {
      url += "&field1=" + String(temp) + "&field2=" + String(hum) + "&field3=" + String(mq) + "&field4=" + String(ldr);
     } else if (cliente == 4) {
      url += "&field5=" + String(temp) + "&field6=" + String(hum) + "&field7=" + String(mq) + "&field8=" + String(ldr);
     } else if (cliente == 5) {
      url += "&field1=" + String(temp) + "&field2=" + String(hum) + "&field3=" + String(mq) + "&field4=" + String(ldr);
     } else if (cliente == 6) {
      url += "&field5=" + String(temp) + "&field6=" + String(hum) + "&field7=" + String(mq) + "&field8=" + String(ldr);
     } else if (cliente == 7) {
      url += "&field1=" + String(temp) + "&field2=" + String(hum) + "&field3=" + String(mq) + "&field4=" + String(ldr);
     } else if (cliente == 8) {
      url += "&field5=" + String(temp) + "&field6=" + String(hum) + "&field7=" + String(mq) + "&field8=" + String(ldr);
    } else {
      Serial.println("Cliente não reconhecido.");
      return;
    }




    http.begin(url); // Inicializa a requisição HTTP
    int httpCode = http.GET(); // Envia a requisição GET

    if (httpCode > 0) {
      Serial.println("Data sent successfully to ThingSpeak");
    } else {
      Serial.println("Error sending data to ThingSpeak");
    }
    http.end(); // Fecha a conexão
  }
}
