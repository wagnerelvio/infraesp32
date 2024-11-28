#include <DHT.h>

// Definições dos sensores
#define DHTPIN 4        // Pino do DHT11
#define DHTTYPE DHT11   // Tipo do sensor DHT

const int ldrPin = 35;     // Pino do LDR
const int mq135Pin = 34;   // Pino do MQ-135

// Inicialização do DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicialização do monitor serial
  Serial.begin(115200);
  
  // Inicialização do DHT11
  dht.begin();

  // Mensagem de inicialização
  Serial.println("Inicializando leitura dos sensores...");
}

void loop() {
  // Leitura do DHT11
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  // Verificação de erro no DHT11
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler o sensor DHT11!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");
  }

  // Leitura do LDR
  int ldrValor = analogRead(ldrPin);
  Serial.print("Luminosidade (LDR): ");
  Serial.println(ldrValor);

  // Leitura do MQ-135
  int mq135Valor = analogRead(mq135Pin);
  Serial.print("Qualidade do ar (MQ-135): ");
  Serial.println(mq135Valor);

  // Separador para facilitar a leitura no monitor serial
  Serial.println("---------------------------");

  // Intervalo entre leituras
  delay(2000); // 2 segundos
}
