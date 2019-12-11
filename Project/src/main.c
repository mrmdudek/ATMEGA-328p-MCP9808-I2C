#include <avr/io.h>
#include <inttypes.h>
#include <stdint.h>
#include <util/delay.h>
#include "mcp9808.h"

int main(void){
	
	printf_init();
	i2c_init();
	// every data from temperature sensor are read and send via uart
	read_resolution();

	while(1)
	{
		_delay_ms(2000);
		read_temperature_C();
	}
}