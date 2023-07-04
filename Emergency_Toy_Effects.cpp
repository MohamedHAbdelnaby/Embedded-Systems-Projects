#include "mbed.h"

DigitalIn switch1(p19, PullDown); // Initializing the first switch: Connected to VCC, so we need a PullDown resistor
DigitalIn switch2(p20, PullUp); // Initializing the second switch: Connected to ground, so we need a PullUp resistor
PwmOut BlueLED(LED1); // Declaring the built-in LED
PwmOut RedLED(p21); // Declaring the Red LED
PwmOut piezo(p22); // Declaring piezo

int main() {
    
    RedLED = 0; // Initializing the RedLed to 0 (Connected to ground; lights up at 1)
    BlueLED = 0; // Initializing the built-in blue LED
    
    
    while(1) {
        
        /*
        
             Generate a two tone siren effect and repeat the effect until the switch is released.
             
             The red LED and the built-in blue LED1 should alternately flashing on and off.
             
             When the piezo is generating 1140 Hz, the red LED should be on and the blue LED off. 
             
             When the piezo is generating 960 Hz, the red LED should be off and the blue LED on.
        
        */
        
        if(switch1 == 1) { // Press switch 1 to activate the first effect
                
            while(switch1 != 0) { // A while loop to run until the switch is released (per instructions)
                
                
                piezo.period(1.0/1140.0); // Assigning a frequency of 1140 Hz to the piezo initially
                piezo = 0.5; // Duty cycle 50% for the piezo
                BlueLED = 0; // Built-in blue LED is off when frequency is 1140 Hz
                RedLED = 1; // Red Led is on when frequency is 1140 Hz
                wait_ms(1000); // Wait a second
                piezo.period(1.0/960.0); // Changing the frequency of the piezo to 960 Hz
                BlueLED = 1; // Built-in blue LED is on when frequency is 960 Hz
                RedLED = 0; //  Red Led is off when frequency is 960 Hz
                wait_ms(1000); // Wait a second
        
                }
                
                BlueLED = 0; // Turn Off the built-in blue LED in case it's still on after the releasing the switch
                RedLED = 0; // Turn Off the Red LED in case it's still on after the releasing the switch
                piezo = 0; // Duty Cycle of the piezo is 0
                wait_ms(200); // Wait 0.2 seconds due to switch bounce
                
            }
            
            /*
            
                  Generate a warbling siren effect and repeat the effect until the switch is released.
                  
                  Generate ascending frequencies from 900 Hz to 1100 Hz over the span of 0.8 seconds
                  
                  Generate descending frequencies from 1100 Hz to 900 Hz over the span of 0.8 seconds
                  
                  Red LED should smoothly transition from fully off when the piezo is generating 900 Hz
                  to fully on when the piezo is generating 1100 Hz.
            
            
            
             */
                
            if(switch2 == 0) { // Press Switch 2 to activate this effect
                
                while(switch2 != 1) { // A while loop to run until the switch is released (per instructions)
                  
                    for(int i = 900; i < 1100; i = i + 20) { // A for loop for ascending frequency (10 loops in total)
                        
                        piezo.period(1.0/i); // Assigning the frequcy to piezo 900, 920, 940 ... 1100
                        
                        piezo = 0.5; // Duty Cycle for piezo is 50%
                        
                        RedLED.period(1.0/900.0); // LED period when frequncy ascends
                        
                        RedLED = RedLED + 0.10; // The LED's duty cycle will increase by 0.10 each iteration (0.10*10 = 1)
                        
                        wait_ms(800); // Wait 0.8 seconds
                        
                        
                        }
                        
                        for(int j = 1100; j > 900; j = j - 20) { // A for loop for descending frequency (10 loops in total)
                            
                        piezo.period(1.0/j); // Assigning the frequcy to piezo 1100, 1080, 1060 ... 900
                        
                        piezo = 0.5; // Duty Cycle for piezo is 50%
                        
                        RedLED.period(1.0/1100.0); // Period of the Led when frequency descends
                        
                        RedLED = RedLED - 0.10; // Duty cycle of the LED will decrease by 0.10 each iteration (1 - 0.10 * 10 = 0)
                        
                        wait_ms(800); // Wait 0.8 seconds   
                            
                        }
                    
                    }
                    
                    RedLED = 0; // Turn Off the Red LED in case it's still on after the releasing the switch
                    piezo = 0; // Duty Cycle of the piezo is 0
                    wait_ms(200); // Wait 0.2 seconds due to switch bounce
                    
                }
            
    }
}
