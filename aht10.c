#include "aht10.h"

// Comandos do AHT10
const uint8_t CMD_INIT[] = {0xE1, 0x08, 0x00};
const uint8_t CMD_MEASURE[] = {0xAC, 0x33, 0x00};

bool aht10_init(i2c_inst_t* i2c) {
    // Envia o comando de inicialização
    int ret = i2c_write_blocking(i2c, AHT10_ADDR, CMD_INIT, sizeof(CMD_INIT), false);
    if (ret < 0) return false;
    sleep_ms(20); // Espera um pouco após a inicialização
    return true;
}

bool aht10_read_data(i2c_inst_t* i2c, aht10_data_t* data) {
    // 1. Envia o comando para disparar uma medição
    int ret = i2c_write_blocking(i2c, AHT10_ADDR, CMD_MEASURE, sizeof(CMD_MEASURE), false);
    if (ret < 0) return false;

    // 2. Espera o tempo de medição (datasheet diz ~75ms)
    sleep_ms(80);

    // 3. Lê os 6 bytes de dados de resposta
    uint8_t buf[6];
    ret = i2c_read_blocking(i2c, AHT10_ADDR, buf, sizeof(buf), false);
    if (ret < 0) return false;

    // 4. Checa o byte de status para ver se o sensor está calibrado e não está ocupado
    // O bit 7 (status) deve ser 0 (não ocupado) e o bit 3 (calibração) deve ser 1
    if ((buf[0] & 0x88) != 0x08) {
        return false;
    }

    // 5. Calcula os valores de umidade e temperatura com base nas fórmulas do datasheet
    uint32_t raw_humidity = ((uint32_t)buf[1] << 12) | ((uint32_t)buf[2] << 4) | (buf[3] >> 4);
    data->humidity = ((float)raw_humidity / 1048576.0f) * 100.0f;

    uint32_t raw_temp = (((uint32_t)buf[3] & 0x0F) << 16) | ((uint32_t)buf[4] << 8) | buf[5];
    data->temperature = (((float)raw_temp / 1048576.0f) * 200.0f) - 50.0f;

    return true;
}