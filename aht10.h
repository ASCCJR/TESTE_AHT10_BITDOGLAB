#ifndef AHT10_H
#define AHT10_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define AHT10_ADDR 0x38

// Estrutura para armazenar os dados finais do sensor
typedef struct {
    float temperature; // Temperatura em Graus Celsius
    float humidity;    // Umidade Relativa em %
} aht10_data_t;

// Funções públicas
bool aht10_init(i2c_inst_t* i2c_port);
bool aht10_read_data(i2c_inst_t* i2c_port, aht10_data_t* data);

#endif