# ATMEGA-328p-MCP9808-I2C
Simple library to MCP9808 over I2C. Implemented 2 functions (read resolution and read temperature).

Synchronous Communication System project for laboratory exercises of Electronic Systems (SELE) course on 
Faculty of Engineering of University of Porto (FEUP).

Written in Visual Studio Code with PIO,
Tested 11.12.2019


# Project wiki
Brief explanation of implemented solution to the task given at the laboratory excercises. 
Firstly, an overview is given, followed by detailed explanation of each module. 
Functionality of each file included in source (src) folder of this repository is explained below.

Generally, the system consists of Arduino UNO board connected via I2C to MCP9808 temperature sensor. 

## System description

**main.c** 
Main module; contains initialization and while(1) loops. Arduino after initialization read MCP9808 resolution, 
later in while loop every 2s arduino read temperature from MCP9808 with printed before resolution.

**serial_printf.c**
Contains functions for initialization, send and receive data via UART.

**mcp9808.c**
Module contain two functions. Function read resolution (read_resolution()) and function read ambient temperature (read_temperature_C()).

Function read resolution:  
- start the communication by send MCP9808 address and 0 (command to write to device), if acknowledge
	- write frame with function to read resolution (0x08) 
	- stop communication
	- start the communication by send MCP9808 address and 1 (command to read from device), if acknowledge
	- read frame without acknowledge (because it's only one frame and last frame don't need to be with acknowledge)
	- stop communication
	- convert received data (meanings of received bits are in MCP9808 datasheet)
	- send data via uart
	
Function read temperature:  
- start the communication by send MCP9808 address and 0 (command to write to device), if acknowledge
	- write frame with function to read ambient temperature (0x05) 
	- stop communication
	- start the communication by send MCP9808 address and 1 (command to read from device), if acknowledge
	- read frame with acknowledge (because it's first frame and there will be more frame(s))
	- read frame without acknowledge (because it's last frame)
	- stop communication
	- convert received data (meanings of received bits are in MCP9808 datasheet)
	- send data via uart

**i2c_master.c**
File contain 6 functions. Each function briefly is described below:

i2c_init:
- set I2C baud

i2c_start:
- reset TWI control register
- transmit START condition
- wait for end of transmission
- check if the start condition was successfully transmitted
- load slave address into data register
- start transmission of address
- wait for end of transmission
- check if the device has acknowledged the READ / WRITE mode

i2c_write:
- load data into data register
- start transmission of data
- wait for end of transmission

i2c_read_ack:
- start TWI module and acknowledge data after reception
- wait for end of transmission
- return received data from TWDR

i2c_read_nack:

- start receiving without acknowledging reception
- wait for end of transmission
- return received data from TWDR

i2c_stop:

- transmit STOP condition

# PCB

https://drive.google.com/open?id=1FrXvOgUvJv1mWZtRX9E2b3NrKS9GoCEU
