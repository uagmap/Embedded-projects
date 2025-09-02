/* 

    ECET 329 Final Project 

    Fall Detector 

    Uses public libraries for SD card and ADXL345 

*/ 

#include "mbed.h" 
#include "SDFileSystem.h" 
#include "ADXL345_I2C.h" 

//Define output ports for LED/ Buzzer 
BusOut LD(PA_2, PA_3, PB_3); 
DigitalOut Buzz(D2); 

//Initalize SD card 
SDFileSystem sd(D11, D12, D13, D10, "sd"); 
// MOSI, MISO, SCLK, CS 

//accelerometer set up 
ADXL345_I2C acc(D14, D15); 
//sda, scl  

char buffer[6];                  // raw data array type char 
int16_t data[3];                 // 16 bit data array 
float x, y, z;                   // floating point data, to be displayed on-screen 
int8_t right,left,front,back,falls = 0; //Number of falls in each direction 
float xpre, ypre = 0;           //x and y previous values 

int main() { 
//accelerometer readings 
    int readings[3] = {0, 0, 0}; 

//accelerometer set up 
    //Stand by mode and Device initalize 
    acc.setPowerControl(0x00); 
    //Full resolution, +/-16g, 4mg/LSB. 
    acc.setDataFormatControl(0x0B); 
    //3.2kHz data rate. 
    acc.setDataRate(ADXL345_3200HZ); 
    //Measurement mode. 
    acc.setPowerControl(0x08); 

  while (1) {                  // infinite loop 
    wait(1);        //delay for readings 

    //combine data 
    acc.getOutput(readings); 
    data[0] = readings[0]; 
    data[1] = readings[1]; 
    data[2] = readings[2]; 

    //turn x float into integer 
    x=0.004*data[0]; 
    int xint = (int)x; 
    int xdec = (int)((x-xint) * 100); 

    //turn y float into integer 
    y=0.004*data[1]; 
    int yint = (int)y; 
    int ydec = (int)((y-yint) * 100); 

    //turn z float into integer 
    z=0.004*data[2]; 
    int zint = (int)z; 
    int zdec = (int)((z-zint) * 100); 

    // Format and display data serially 
    printf( "\nAngle is: %i.%02d, %i.%02i\n\rFalls is : %d\n\r", xint, xdec, yint, ydec, falls); 
        //If the device has fallen right count up 
        if ((x>0.75) && (xpre<0.7)) 
        { 
           //setting directory for sd card 
            mkdir("/sd/mydir", 0777); 
 
            FILE *fp = fopen("/sd/mydir/sdtest.txt", "w"); 
            if(fp == NULL) { 
              error("Could not open file for write\n"); 
            } 

            //turn on LEDs and buzzer 
            LD= 0xFF; 
            Buzz = 0; 

            //inciment falls 
            falls = falls + 1; 
            right = right + 1; 

            //save data 
            fprintf(fp,"Falls (R,L,F,B): %i,%i,%i,%i",right,left,front,back);   
            // write data 
            fclose(fp); 
        } 

        //If the device has fallen left count up 
        if ((x<-0.75) && (xpre>-0.7)) 
        { 
            //setting directory for sd card 
            mkdir("/sd/mydir", 0777); 

            FILE *fp = fopen("/sd/mydir/sdtest.txt", "w"); 
            if(fp == NULL) { 
            error("Could not open file for write\n"); 
            } 

            //turn on LEDs and buzzer 
            LD= 0xFF; 
            Buzz = 0; 

            //increment falls 
            falls = falls + 1; 
            left = left + 1; 

            //save data 
            fprintf(fp,"Falls (R,L,F,B): %i,%i,%i,%i", right,left,front,back);   // write data 
            fclose(fp); 
        } 

        //If the device has fallen front count up 
        if ((y>0.75) && (ypre<0.7)) 
        { 
            //setting directory for sd card 
            mkdir("/sd/mydir", 0777); 

            FILE *fp = fopen("/sd/mydir/sdtest.txt", "w"); 
            if(fp == NULL) { 
            error("Could not open file for write\n"); 
            } 

            //turn on LEDs and buzzer 
            LD= 0xFF; 
            Buzz = 0; 

            //increment falls 
            falls = falls + 1; 
            front = front +1; 

            //save data 
            fprintf(fp,"Falls (R,L,F,B): %i,%i,%i,%i", right,left,front,back);   // write data 
            fclose(fp); 
        } 
              
        //If the device has fallen back count up 
        if ((y<-0.75) && (ypre>-0.7)) 
        { 
            //setting directory for sd card 
            mkdir("/sd/mydir", 0777); 

            FILE *fp = fopen("/sd/mydir/sdtest.txt", "w"); 
            if(fp == NULL) { 
            error("Could not open file for write\n"); 
            } 

            //turn on LEDs and buzzer 
            LD= 0xFF; 
            Buzz = 0; 

            //incriment falls 
            falls = falls + 1; 
            back = back + 1; 

            //save data 
            fprintf(fp,"Falls (R,L,F,B): %i,%i,%i,%i", right,left,front,back);   // write data 
            fclose(fp); 
        } 
        xpre = x;   //store previous x value 
        ypre = y;   //store previous y value 
        //turn off LEDs and buzzer if normal position 
        if((x<0.5 && x>-0.5) && (y<0.5 && y>-0.5)){ 
            LD = 0x00; 
            Buzz = 1; 
        } 
  } 
} 
