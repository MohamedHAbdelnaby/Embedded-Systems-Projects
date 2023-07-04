#include "mbed.h"
SPI spi(p11,p12,p13); // Declaring SPI
DigitalOut input(p15); // Declaring DigitalOut input
DigitalOut output(p14); // Declaring DigitalOut output
I2C i2c(p9,p10); // Declaring i2c
DigitalIn check(p20); // Declaring pin20 to select the modes.


/*

          SegConverter methods takes a parameter that represents a character or an integer and it returns a binary representation

          That binary representation is for the display to show these numbers of letters, as this method return a binary representation

          that either turns on or off certain segments of the display, hence, displaying certain letters or numbers.

          Input: Integer representing a digit

          Output: Integer containing a binary representation





*/


int SegConverter(int digit)
{

    switch(digit) {

        case 'A':
            return 0b11101110; // Displaying A
        case 'B':
            return 0b11111110; // Displaying B
        case 'C':
            return 0b10011100; // Displaying C
        case 'D':
            return 0b11111100; // Displaying D
        case 'U':
            return 0b01111100; // Displaying U
        case 'L':
            return 0b00011100; // Displaying L
        default:
            return 0; // Default is 0

    }

}

int main()
{

    spi.frequency(10000000); // Declaring the frequency of the SPI

    int CountButton = 0; // A variable to count how many times a button has been pressed

    int button = 0; // A variable to keep track of buttons if pressed

    int code = 0; // A variable storing the code that the user entered

    while(1) {

        // Blinks All Segments

        spi.format(8,0); // Start spi format, 8 bits, mode 0

        output = 0; // Attach

        spi.write(0b00000000);

        output = 1; // Deattach

        // Get the input

        spi.format(8,2);

        input = 1; //Attach

        button = spi.write(0);

        input = 0; //Deattach

        if(button != 0) { // If we pressed a button

            spi.format(8,0);

            if(button == 0b00000001) { // If Button Representing A is pressed

                CountButton = CountButton + 1; // Increment the CountButton variable

                code = code *4 + 0; // The code representing the letter A

                output = 0; // attach

                spi.write(SegConverter('A')); // Display that the letter A has been entered

                output = 1; // deattach

                wait(0.5); // Wait for 0.5 seconds

            }

            if(button == 0b00000010) { // If Button Representing B is pressed

                CountButton = CountButton + 1; // Increment the CountButton variable

                code = code*4 +  1; // The code representing the letter B

                output = 0; // attach

                spi.write(SegConverter('B')); // Display the letter B

                output = 1; //deattach

                wait(0.5); // Wait 0.5 seconds



            }

            if(button == 0b00000100) { // If Button Representing C is pressed

                CountButton = CountButton + 1; // Increment the CountButton variable

                code = code * 4 + 2; // The code representing the letter C

                output = 0; // attach

                spi.write(SegConverter('C')); // Display the letter C

                output = 1; //deattach

                wait(0.5); // Wait 0.5 seconds

            }

            if(button == 0b00001000) { // If Button Representing D is pressed

                CountButton = CountButton + 1; // Increment the CountButton variable

                code = code *4 + 3; // The code representing the letter D

                output = 0; // attach

                spi.write(SegConverter('D')); // Display the letter D

                output = 1; //deattach

                wait(0.5); // Wait for 0.5 seconds

            }

        }

        if(CountButton == 4) { // We need to make sure that the button has been pressed 4 times, check if the CountButto variable is 4

            if(check == 1) { // If Pin20 is connected to VCC, then it's program mode and we store the code the user entered

                spi.format(8,0);

                i2c.start(); // Starting I2c

                i2c.write(0b10100000); // Control Byte, last 3 bits are don't care

                i2c.write(0b00000000); // Writing the address 0 or 0b00000000

                i2c.write(code); // Writing the code variable to this address

                i2c.stop(); // Stop I2c

            }

            else { // Pin20 is connected to ground and it's user mode and the user will enter the 4 letters code to check if it matches with the stored code

                i2c.start(); // Start I2c

                i2c.write(0b10100000); // control byte, last 3 bits are don't care

                i2c.write(0b00000000); // The word address

                i2c.start(); // Start I2c

                i2c.write(0b10100001); // Control byte with 1 to denote acknowledge and read

                int data = i2c.read(0); // Read data stored at address 0 or 0b00000000 and store that data in a variable named data

                i2c.stop(); // Stop I2c

                if(data == code) { // If data retrived from the memory chip is equal to the code that we have stored

                    output = 0;

                    spi.write(SegConverter('U')); // Display U to indicate that it's unlocked

                    output = 1;

                    wait(0.5);

                }

                else {


                    output = 0;

                    spi.write(SegConverter('L')); // Display L to indicate that it's locked

                    output = 1;

                    wait(0.5);

                }



            }

            CountButton = 0; // Reset CountButton to start over when other 4 letters are entered

            code = 0; // Reset the code variable to allow a new code to be written.


        }

    }
}