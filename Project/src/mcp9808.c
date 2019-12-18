#include "mcp9808.h"

void read_resolution(void)
{
uint8_t data1;

if (~i2c_start(MCP9808_I2CADDR_DEFAULT<<1 | 0)) // if there is device, write frame to this device
{
    i2c_write(MCP9808_REG_RESOLUTION); // write frame with resolution
    i2c_stop();

    i2c_start(MCP9808_I2CADDR_DEFAULT<<1 | 1); // read frame from device, first send address
    data1 = i2c_read_nack();
    i2c_stop();

    // convert received data and send via uart
    if ((data1 & 0b11) & 0b11)
    {
        printf("resolution 0.0625\r\n");
    }
    else if ((data1 & 0b11) & 0b10)
    {
        printf("resolution 0.125oC\r\n");
    }
    else if ((data1 & 0b11) & 0b01)
    {
        printf("resolution 0.25oC\r\n");
    }
    else if ((data1 & 0b11) & 0b00)
    {
        printf("resolution 0.5oC\r\n");
    }
}
}

void read_temperature_C(void)
{

    uint8_t data1 = 0xff;
    uint8_t data2 = 0xff;
    uint8_t temp_most_sign;
    uint16_t temp_least_sign;

    if (~i2c_start(MCP9808_I2CADDR_DEFAULT<<1)) // if there is device, write frame
    {
        i2c_write(MCP9808_REG_AMBIENT_TEMP); // frame
        i2c_stop();

        i2c_start(MCP9808_I2CADDR_DEFAULT<<1 | 1); // read two frames from device
        data1 = i2c_read_ack(); // first frame with acknowledge
        data2 = i2c_read_nack(); // second frame without acknowledge
        i2c_stop();

        // convert temperature
        temp_most_sign = ((data1 & 0b1111)<<4) | (data2 & 0b11110000)>>4;
        temp_least_sign = (((data2 & 0b1000)>0)*5000) + (((data2 & 0b100)>0)*2500) + (((data2 & 0b10)>0)*1250) + (((data2 & 0b1)>0)*625);
  
        // send via uart
        printf("temperature = %u.%04u\r\n",temp_most_sign,temp_least_sign);
    }
}