#include "mbed.h"
#include "LPS35_I2C.h"

Serial pc(USBTX, USBRX);
LPS35_I2C lps35(D14, D15, LPS35_I2C_SA0_HIGH);


int main() {
	pc.printf("LPS35HW Test Program.\r\n");
	
	if(lps35.isAvailable())
		pc.printf("LPS35HW is available!\r\n");
	else
		pc.printf("LPS35HW is unavailable!\r\n");
	
	lps35.setDataRate(LPS35_I2C_DATARATE_10HZ);
	lps35.setActive(true);
	
	pc.printf("LPS35HW Register map.\r\n");

	for(int i = 0; i < 8; i++){
		pc.printf("%02x: ", i);
		for(int j = 0; j < 16; j++) {
			char value = lps35._read(j | i << 4);
			pc.printf("%02x ", value);
		}
		pc.printf("\r\n");
	}
	
	pc.printf("LPS35HW Register map(multibyte read test).\r\n");
	
	for(int i = 0; i < 8; i++){
		char data[16];
		lps35._read_multibyte(i << 4, data, 16);
		pc.printf("%02x: ", i);
		for(int j = 0; j < 16; j++)
			pc.printf("%02x ", data[j]);
		pc.printf("\r\n");
	}
	
	wait(2.0);
	
	while(true){
		float pres, temp;
		
		pres = lps35.getPressure();
		temp = lps35.getTemperature();
		
		pc.printf("%f,%f\r\n", pres, temp);
		
		wait(1/7.0);
	}
}
