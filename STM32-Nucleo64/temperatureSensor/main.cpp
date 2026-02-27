#include "mbed.h"

I2C tempsensor(D14, D15); //initialize I2C with D14 and D15 as SDA and SCL
Serial pc(USBTX, USBRX); //initialize serial tx, rx

const int addr = 0x90;
char config_t[3];   //addressing the registers
char temp_read[2];  //for storing temperature reading
float temp;

int main() 
{
    config_t[0] = 0x01; //set pointer reg to ’config register’
    config_t[1] = 0x60; // config data byte1
    config_t[2] = 0xA0; // config data byte2
    
    tempsensor.write(addr, config_t, 3);    // write do the config register
    
    config_t[0] = 0x00; //set pointer reg to ’data register’
    
    tempsensor.write(addr, config_t, 1); //send to pointer ’read temp’
    
    while(1) 
    {
        wait(1);    //delay 1 s
        tempsensor.read(addr, temp_read, 2); //read the two-byte temp data
        temp = 0.0625 * (((temp_read[0] << 8) + temp_read[1]) >> 4); //convert data
        pc.printf("Temp = %.2f degC\n\r", temp);    //print in the terminal
    }
}