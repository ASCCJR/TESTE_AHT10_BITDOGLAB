# 🌡️ Teste do Sensor de Umidade e Temperatura AHT10 no Raspberry Pi Pico

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20Pico-purple.svg)
![Sensor](https://img.shields.io/badge/Sensor-AHT10-9cf.svg)

Este repositório contém um código teste para o sensor de umidade e temperatura AHT10, utilizando a BitDogLab e o SDK oficial em C/C++.

O projeto foi estruturado de forma modular, com um driver específico para o sensor (`aht10.c` e `aht10.h`), facilitando a reutilização do código em projetos mais complexos.

## ✨ Funcionalidades

* **Leitura de Dados:** Coleta dados de Temperatura (em Graus Celsius) e Umidade Relativa (em %).
* **Driver Modular:** A lógica de comunicação com o sensor AHT10 é encapsulada, seguindo as especificações do datasheet.
* **Configuração Flexível:** Permite alternar facilmente entre os barramentos I2C 0 e I2C 1 da placa através de comentários no código.
* **Saída Serial:** Exibe os dados lidos de forma clara e contínua no monitor serial.

## 🛠️ Hardware e Software Necessários

### Hardware
* Placa com Raspberry Pi Pico (neste projeto, foi usada a **BitDogLab**)
* Sensor de Umidade e Temperatura I2C **AHT10**

### Software
* [Raspberry Pi Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk)
* Ambiente de compilação C/C++ (GCC para ARM, CMake)
* Um programa para monitor serial (ex: o integrado no VS Code, PuTTY, etc.)

## Configurar a Porta I2C
* Por padrão, o projeto está configurado para usar o conector I2C 1 (Esquerda) da BitDogLab.
* Para trocar para o conector I2C 0 (Direita), edite o arquivo main.c
* Comente o bloco de configuração do I2C 1.
* Descomente o bloco de configuração do I2C 0.

## Exemplo para usar a porta I2C 0:

```bash
// --- Configuração da Porta I2C 1 da BitDogLab (Comentado) ---
// #define I2C_PORT i2c1
// const uint I2C_SDA_PIN = 2;
// const uint I2C_SCL_PIN = 3;

// --- Configuração da Porta I2C 0 da BitDogLab (Ativo) ---
#define I2C_PORT i2c0
const uint I2C_SDA_PIN = 0;
const uint I2C_SCL_PIN = 1;
```

## Visualizar a Saída
* Conecte o sensor AHT10 na porta I2C configurada
* Abra um monitor serial conectado à porta COM do seu Pico.
* Você verá a seguinte saída, atualizada a cada 2 segundos:
```bash
--- Iniciando Sensor de Umidade e Temperatura AHT10 ---
Sensor inicializado. Coletando dados...
Temperatura: 27.50 C  |  Umidade Relativa: 62.34 %
Temperatura: 27.51 C  |  Umidade Relativa: 62.38 %
```
