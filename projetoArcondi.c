//equipe: josé joélio e Lázaro santos
//16/05/25

#include <DHT.h>

// Define o pino do sensor DHT
#define DHTPIN 2     // Pino digital onde o sensor está conectado
#define DHTTYPE DHT22   // Pode ser DHT11 ou DHT22

// Inicializa o sensor
DHT dht(DHTPIN, DHTTYPE);

// Define o pino do relé
#define RELAY_PIN 7

// Temperaturas limite
#define TEMP_LIGAR 25.0
#define TEMP_DESLIGAR 23.0

// Variável de estado do ar-condicionado
bool arCondicionadoLigado = false;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Garante que o relé esteja desligado
}

void loop() {
  float temperatura = dht.readTemperature(); // Lê temperatura em °C

  if (isnan(temperatura)) {
    Serial.println("Erro ao ler a temperatura!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (temperatura >= TEMP_LIGAR && !arCondicionadoLigado) {
    digitalWrite(RELAY_PIN, HIGH); // Liga o relé (ajuste se seu relé for ativo em LOW)
    arCondicionadoLigado = true;
    Serial.println("Ar-condicionado LIGADO");
  }

  if (temperatura <= TEMP_DESLIGAR && arCondicionadoLigado) {
    digitalWrite(RELAY_PIN, LOW); // Desliga o relé
    arCondicionadoLigado = false;
    Serial.println("Ar-condicionado DESLIGADO");
  }

  delay(2000); // Espera 2 segundos antes de ler novamente
}
