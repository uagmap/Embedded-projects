#include "mbed.h"

SPI acc(D11, D12, D13); // set up SPI interface on pins 11,12,13
DigitalOut cs(D10); // use pin D10 as chip select
Serial pc(USBTX, USBRX); // serial communication for terminal

char buffer[6]; // data to be printed
int16_t data[3]; // array to hold readings
float x, y, z; // float to be displayed

int main() {
    cs=1; // initially ADXL345 is not activated
    acc.format(8,3); // 8 bit data, Mode 3
    acc.frequency(2000000); // 2MHz clock rate

    cs=0; // select the device
    acc.write(0x31); // select data format register
    acc.write(0x0B); // format +/-16g, 0.004g/LSB
    cs=1; // end of transmission

    cs=0; // start a new transmission
    acc.write(0x2D); // select power control register
    acc.write(0x08); // set measure mode bit
    cs=1; // end of transmission

    while (1) { // infinite loop
        wait(0.2);
        cs=0; // start a transmission
        acc.write(0x80 | 0x40 | 0x32); // RW bit high, MB bit high, plus address
        
        for (int i = 0;i<=5;i++) {
            buffer[i]=acc.write(0x00); // read back 6 data bytes
        }

        cs=1; // end of transmission
        data[0] = buffer[1]<<8 | buffer[0]; // combine MSB and LSB
        data[1] = buffer[3]<<8 | buffer[2];
        data[2] = buffer[5]<<8 | buffer[4];
        
        x=0.004*data[0]; 
        y=0.004*data[1]; 
        z=0.004*data[2]; // convert to float,
        // actual g value
        pc.printf("x = %+1.2fg\t y = %+1.2fg\t z = %+1.2fg\n\r", x, y,z); // print
    }
}