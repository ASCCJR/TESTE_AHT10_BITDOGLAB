#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "aht10.h" // Incluindo a nossa biblioteca AHT10

// Pinos do conector I2C 1 da BitDogLab
#define I2C_PORT i2c1
const uint I2C_SDA_PIN = 2;
const uint I2C_SCL_PIN = 3;

int main() {
    stdio_init_all();
    sleep_ms(4000);

    printf("--- Iniciando Sensor de Umidade e Temperatura AHT10 ---\n");

    // Inicializa o I2C
    i2c_init(I2C_PORT, 100 * 1000); // AHT10 usa 100kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    
    // Inicializa o sensor AHT10
    if (!aht10_init(I2C_PORT)) {
        printf("ERRO: Falha ao inicializar o sensor AHT10.\n");
        while (1);
    }
    
    printf("Sensor inicializado. Coletando dados...\n");

    while (1) {
        aht10_data_t sensor_data;
        
        // Lê os dados do sensor
        if (aht10_read_data(I2C_PORT, &sensor_data)) {
            printf("Temperatura: %.2f C  |  ", sensor_data.temperature);
            printf("Umidade Relativa: %.2f %%\n", sensor_data.humidity);
        } else {
            printf("Falha ao ler os dados do sensor.\n");
        }
        
        sleep_ms(2000); // O sensor é um pouco lento, vamos ler a cada 2 segundos
    }
    return 0;
}