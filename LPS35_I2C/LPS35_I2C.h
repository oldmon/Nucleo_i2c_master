/*
 *  I2C/SPI digital pressure sensor "LPS35HW" library for I2C mode.
 *  http://www.st.com/resource/en/datasheet/lps35hw.pdf
 *  Released under the MIT License: http://mbed.org/license/mit
 */

#ifndef LPS35_I2C_H
#define LPS35_I2C_H

#include "mbed.h"

// SA0 status configuration values.
#define LPS35_I2C_SA0_HIGH	true
#define LPS35_I2C_SA0_LOW	false

// Data Rate   								Pressure / Temperature 
#define LPS35_I2C_DATARATE_ONESHOT	0x00	// OneShot	OneShot
#define LPS35_I2C_DATARATE_1HZ		0x01	// 1Hz		1Hz
#define LPS35_I2C_DATARATE_10HZ		0x02	// 10Hz		10Hz
#define LPS35_I2C_DATARATE_25HZ		0x03	// 25Hz		25Hz
#define LPS35_I2C_DATARATE_50HZ		0x04	// 50Hz		50Hz
#define LPS35_I2C_DATARATE_75HZ		0x05	// 75Hz		75Hz

// I2C Address.
#define LPS35_I2C_ADDRESS_SA0_HIGH 0xba
#define LPS35_I2C_ADDRESS_SA0_LOW  0xb8

class LPS35_I2C
{
public:
	LPS35_I2C(PinName sda, PinName scl, bool sa0);
	~LPS35_I2C();

	char whoami();
	bool isAvailable();
	
	void setActive(bool is_active);
	void setDataRate(char datarate);

	double getPressure();
	double getTemperature();

	void _write(char subaddress, char data);
	char _read(char subaddress);
	void _read_multibyte(char startsubaddress, char* data, char count);

private:
	I2C _i2c;
	char _address;
	char _ctrlreg1;
};

#endif /* LPS35_I2C_H */
