 #include "mbed.h"
 #include <cstdio> // For sprintf
 BufferedSerial MyPC(USBTX, USBRX);
 AnalogIn ain(PA_0);
 // Clear the screen
 //
void clrscr()
{
    char clrscr[]={0x1B, '[', '2', 'J', 0};
    MyPC.write(clrscr, sizeof(clrscr) -1);
}

//Home the cursor
void homescr()
{
    char homescr[] = {0x1B, '[', 'H', 0};
    MyPC.write(homescr, sizeof(homescr) -1); //need to ensure null terminator is not sent
}
 //
 // Goto specified line and column
 //
void gotoscr(int line, int column) {
    // Construct the escape sequence string dynamically
    char scr[12]; // Buffer size is arbitrary, ensure it's large enough
    sprintf(scr, "\033[%d;%dH", line, column);
    MyPC.write(scr, strlen(scr));
}

void initDisplay() {
    clrscr(); // Clear the screen
    homescr(); // Home the cursor
    // Display static text
    char header[] = "DIGITAL THERMOMETER\n\r==========================\n\r";
    MyPC.write(header, sizeof(header) - 1);
}

int main() {
   initDisplay(); // Initialize display with static content

    double mV, T;
    char buffer[64]; // Ensure buffer is large enough for the string

    while(1) { // Infinite loop
        mV = 3300.0f * ain.read(); // Read analog value, simulate voltage in mV
        T = mV / 10.0f; // Calculate temperature
        
        int intPart = (int)T;
        int decimalPart = (int)((T - intPart) * 100); // Assuming two decimal places

        // Move cursor to where temperature will be displayed
        gotoscr(4, 0); // Assuming row 4 is where the temperature should be displayed

        // Format and display temperature
        sprintf(buffer, "Temperature = %d.%02d°F\n\r", intPart, decimalPart);
        MyPC.write(buffer, strlen(buffer));

        ThisThread::sleep_for(1s); // Sleep for 1 second
    }
}