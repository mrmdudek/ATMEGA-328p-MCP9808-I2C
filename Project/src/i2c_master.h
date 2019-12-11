#include <inttypes.h>
#include <stdint.h>

#ifndef I2C_MASTER_H
#define I2C_MASTER_H

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
void i2c_stop(void);

#endif // I2C_MASTER_H
