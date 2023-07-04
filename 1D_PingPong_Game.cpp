// Registers for Port 0

#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)
#define FIO0SET (*(volatile unsigned int *)0x2009c018)
#define FIO0CLR (*(volatile unsigned int *)0x2009c01C)

// Registers for Port 1

#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)
#define FIO1SET (*(volatile unsigned int *)0x2009c038)
#define FIO1CLR (*(volatile unsigned int *)0x2009c03C)

// Registers for Port 2

#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define FIO2SET (*(volatile unsigned int *)0x2009c058)
#define FIO2CLR (*(volatile unsigned int *)0x2009c05C)

// Define PINMODE

#define PINMODE0 (*(volatile unsigned int *)0x4002c040)
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)




volatile int delay = 0;

void wait(float seconds)
{

    volatile int count = seconds*21.33e6;

    while(count > 0) {

        count --;



    }

}

void initializePorts()
{

    // Port 0 + Port 2 LED 25,26,27,28

// Port 0 Switch 9, 10

// Built-in Port 1, bit 18,20,21,23

    FIO1DIR |= (1<<18); // Built-in LED 1 p1.18
    FIO1DIR |= (1<<20); // Built-in LED 2 p1.20
    FIO1DIR |= (1<<21); // Built-in LED 3 p1.21
    FIO1DIR |= (1<<23); // Built-in LED 4 p1.23
    FIO2DIR |= (1<<1); // First Green LED P25 p2.1
    FIO2DIR |= (1<<0); // Second Green LED p26 p2.0
    FIO0DIR |= (1<<11); // First RED LED P27 p0.11
    FIO0DIR |= (1<<10); // Second RED LED P 28 p0.10
// Switch 1 pin 10 Switch 2 pin 11
    FIO0DIR&=~(1<<1); // First Switch P10 p0.1
    FIO0DIR&=~(1<<18); // Second Switch P11 p0.18
    PINMODE1 |= (1<<4) | (1<<5);
    PINMODE0 |= (1<<2) | (1<<3);

    wait(1);




}

int readSwitch1(void)
{
    return ((FIO0PIN >> 1) & 1);
}

int readSwitch2(void)
{
    return ((FIO0PIN >> 18) & 1);
}

void writeRED1(int state)
{

    if(state)
        FIO0PIN |= (1<<11);
    else
        FIO0PIN &= ~(1<<11);


}

void writeRED2(int state)
{

    if(state)
        FIO0PIN |= (1<<10);
    else
        FIO0PIN &= ~(1<<10);


}

void writeGreen1(int state)
{

    if(state)
        FIO2PIN |= (1<<1);
    else
        FIO2PIN &= ~(1<<1);


}

void writeGreen2(int state)
{

    if(state)
        FIO2PIN |= (1<<0);
    else
        FIO2PIN &= ~(1<<0);


}

void writeLED1(int state)
{

    if(state)
        FIO1PIN |= (1<<18);
    else
        FIO1PIN &= ~(1<<18);



}

void writeLED2(int state)
{

    if(state)
        FIO1PIN |= (1<<20);
    else
        FIO1PIN &= ~(1<<20);



}

void writeLED3(int state)
{

    if(state)
        FIO1PIN |= (1<<21);
    else
        FIO1PIN &= ~(1<<21);



}


void writeLED4(int state)
{

    if(state)
        FIO1PIN |= (1<<23);
    else
        FIO1PIN &= ~(1<<23);



}

void BallDirection(int state)
{

    if(state) {

        writeLED1(1);

        wait(0.5);

        writeLED1(0);

        wait(0.001);

        writeLED2(1);

        wait(0.5);

        writeLED2(0);

        wait(0.001);

        writeLED3(1);

        wait(0.5);

        writeLED3(0);

         wait(0.001);

        writeLED4(1);
        
        wait(0.1);

         for(int i=0; i<10; i++) {
            if (readSwitch2())
                break;
            wait(0.1);
        }

        writeLED4(0);
        
        wait(0.001);

       



    }

    else {

        writeLED4(1);

        wait(0.5);

        writeLED4(0);

        wait(0.001);

        writeLED3(1);

        wait(0.5);

        writeLED3(0);

        wait(0.001);

        writeLED2(1);

        wait(0.5);

        writeLED2(0);

         wait(0.001);

        writeLED1(1);
        
        wait(0.1);

        for(int i=0; i<10; i++) {
            if (readSwitch1())
                break;
            wait(0.1);
        }

        writeLED1(0);
        
        wait(0.001);

        

    }



}

void BallDirection1(int state)
{

    if(state) {

        writeLED2(1);

        wait(0.5);

        writeLED2(0);

        wait(0.001);

        writeLED3(1);

        wait(0.5);

        writeLED3(0);

         wait(0.001);

        writeLED4(1);
        
        wait(0.1);

        for(int i=0; i<10; i++) {
            if (readSwitch2())
                break;
            wait(0.1);
        }

        writeLED4(0);
        
        wait(0.001);

        



    }

    else {

        writeLED3(1);

        wait(0.5);

        writeLED3(0);

        wait(0.001);

        writeLED2(1);

        wait(0.5);

        writeLED2(0);

        wait(0.001);

        writeLED1(1);
        
        wait(0.1);

        for(int i=0; i<10; i++) {
            if (readSwitch1())
                break;
            wait(0.1);
        }

        writeLED1(0);
        
        wait(0.001);

        


    }



}




void updateGreen(int greencount)
{

    greencount++;

    if(greencount == 1)
        writeGreen1(1);
    if(greencount ==2)
        writeGreen2(1);

}

void updateRed(int redcount)
{

    redcount++;

    if(redcount == 1)
        writeRED1(1);
    if(redcount ==2)
        writeRED2(1);

}

enum {player1serve, player2swPressed, player2misses, player1swPressed, player1misses, player2serve, restart};

int state;


int greencount = 0;

int redcount = 0;

void statemachine(void)
{


    switch(state) {

        case player1serve:



            if(readSwitch1()) {
                BallDirection(1);


                if(readSwitch2()) {

                    state = player2swPressed;

                }

                else {

                    state = player2misses;

                }

            }

            break;

        case player2swPressed:

            BallDirection1(0);

            if(readSwitch1()) {

                state = player1swPressed;


            }

            else {

                state = player1misses;

            }

            break;

        case player2misses:

            wait(1);

            greencount = greencount + 1;

            writeGreen1(1);
            if(greencount == 2) {

                writeGreen2(1);

                state = restart;

            }

            else {

                state = player2serve;
            }
            break;

        case player1swPressed:

            BallDirection1(1);

            if(readSwitch2()) {

                state = player2swPressed;

            }

            else {

                state = player2misses;

            }

            break;

        case player1misses:

            wait(1);

            redcount = redcount + 1;

            writeRED1(1);

            if(redcount == 2) {

                writeRED2(1);

                state = restart;

            }

            else {

                state = player1serve;

            }

            break;

        case player2serve:



            if(readSwitch2()) {

                BallDirection(0);

                if(readSwitch1()) {

                    state = player1swPressed;

                }

                else {

                    state = player1misses;

                }

            }

            break;

        case restart:

            wait(5);

            writeRED1(0);

            wait(0.001);

            writeRED2(0);
            wait(0.001);

            writeGreen1(0);
            wait(0.001);
            writeGreen2(0);
            wait(0.001);
            redcount = 0;

            greencount = 0;

            state = player1serve;

            break;





    }


}


int main()
{

    initializePorts();

    wait(0.010); // Wait 10ms for pull-down to take effect

    while(1) {


        statemachine();



    }
}
