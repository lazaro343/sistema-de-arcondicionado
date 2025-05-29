Claro! Aqui está um exemplo de **README** em português para o seu projeto com Arduino, sensor de temperatura DHT22 e controle de relé para ar-condicionado:

---

# Controle de Ar-Condicionado com Sensor de Temperatura DHT22

**Equipe:** José Joélio e Lázaro Santos
**Data:** 16/05/2025

## 📋 Descrição

Este projeto utiliza um sensor de temperatura **DHT22** conectado a um **Arduino** para monitorar a temperatura ambiente e controlar automaticamente um **relé**, que pode ser usado para ligar/desligar um **ar-condicionado**.
A lógica emprega um sistema de histerese simples para evitar o acionamento constante do relé.

---

## 🔧 Componentes Utilizados

* 1x Arduino (UNO, Mega, Nano, etc.)
* 1x Sensor de temperatura e umidade **DHT22**
* 1x Módulo Relé
* Jumpers
* Fonte de alimentação compatível

---

## 🔌 Ligações

| Componente   | Pino do Arduino |
| ------------ | --------------- |
| DHT22 - VCC  | 5V              |
| DHT22 - GND  | GND             |
| DHT22 - DATA | D2              |
| Relé - IN    | D7              |
| Relé - VCC   | 5V              |
| Relé - GND   | GND             |

---

## 🧠 Lógica de Funcionamento

* Se a temperatura lida for **igual ou superior a 25°C**, o relé é **acionado** para ligar o ar-condicionado.
* Quando a temperatura cair para **23°C ou menos**, o relé é **desligado**, desligando o ar-condicionado.
* A histerese de 2°C evita que o sistema fique ligando e desligando o tempo todo quando a temperatura está próxima do limite.

---

## 🖥️ Código

```cpp
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define RELAY_PIN 7
#define TEMP_LIGAR 25.0
#define TEMP_DESLIGAR 23.0

bool arCondicionadoLigado = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    Serial.println("Erro ao ler a temperatura!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (temperatura >= TEMP_LIGAR && !arCondicionadoLigado) {
    digitalWrite(RELAY_PIN, HIGH);
    arCondicionadoLigado = true;
    Serial.println("Ar-condicionado LIGADO");
  }

  if (temperatura <= TEMP_DESLIGAR && arCondicionadoLigado) {
    digitalWrite(RELAY_PIN, LOW);
    arCondicionadoLigado = false;
    Serial.println("Ar-condicionado DESLIGADO");
  }

  delay(2000);
}
```

---

## 📦 Bibliotecas Necessárias

Certifique-se de instalar a biblioteca **DHT sensor library** na IDE do Arduino.
Você pode instalá-la em: `Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...` e buscar por `DHT sensor library` (por Adafruit).

---

## ⚠️ Observações

* O relé pode ser **ativo em nível baixo (LOW)**, dependendo do modelo. Ajuste o código se necessário.
* Este projeto não controla a umidade, apenas a **temperatura**.
* Sempre teste o circuito com segurança, especialmente se o relé estiver controlando cargas AC.

---

Se quiser, posso gerar este README também em formato Markdown (`.md`) para você copiar ou usar diretamente em um repositório GitHub. Deseja isso?
