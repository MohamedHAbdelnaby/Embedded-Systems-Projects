#include "mbed.h"

DigitalOut Red1(p17); // First Red LED
DigitalOut Red2(p18); // Second Red LED
DigitalOut Green1(p24,1); // First Green LED
DigitalOut Green2(p23,1); // Second Green LED

DigitalIn Switch1(p19, PullUp); // First Switch: Turn On Red
DigitalIn Switch2(p20, PullUp); // Second Switch: Turn Off Red
DigitalIn Switch3(p22, PullDown); // Third Switch: Turn On Green
DigitalIn Switch4(p21, PullDown); // Fourth Switch: Turn Off Green

void TurnRedOn() {
    
    if(Red1 == 0) { // If Red1 is turned off
        
        Red1 = 1; // Turn it on
        
    }
        
   else if(Red2 == 0) {  // If Red2 is turned off
         
         Red2 = 1; // Turn it on
         
         }   
    }

void TurnRedOff() { 
    
    if(Red1 == 1) { // If Red1 is turned on
        
        Red1 = 0; // Turn it off
        
        }
    
   else if(Red2 == 1) { // If Red2 is turned on
        
        Red2 = 0; // Turn it off
        
        }
    }
    
void TurnGreenOff() {
    
    if(Green1 == 0) { // If Green1 is turned on
        
        Green1 = 1; // Turn it off
     
        }
    
    else if(Green2 == 0) { // If Green2 is turned on
        
        Green2 = 1; // Turn it off
        
        
        }
    
    }
    
void TurnGreenOn () {
    
    if(Green1 == 1) { // If Green1 is turned off
        
        Green1 = 0; // Turn it on
        
        }
    
    else if(Green2 == 1) { // If Green2 is turned off
        
        Green2 = 0; // Turn it on
        
        }
    
    }
    

int main() {
  
    int oldstatesw1 = 1; // Initializing oldstate for switch 1
    int oldstatesw2 = 1; // Initializing oldstate for switch 2
    int oldstatesw3 = 0; // Initializing oldstate for switch 3
    int oldstatesw4 = 0; // Initializing oldstate for switch 4
    
    while(true) {

    int newstatesw1 = Switch1; // Assigning the value of switch 1 to new state of switch 1
    int newstatesw2 = Switch2; // Assigning the value of switch 2 to new state of switch 2
    int newstatesw3 = Switch3; // Assigning the value of switch 3 to new state of switch 3
    int newstatesw4 = Switch4; // Assigning the value of switch 4 to new state of switch 4
    
    /* Switch 1 configuration for turning on the RED LED*/
    
    if(newstatesw1 == 0 && newstatesw1 != oldstatesw1) { // If the new state for switch is off and the new state is different than the old state
        
        TurnRedOn(); // Turn Red On
        
        wait(0.2);
        
        }
        
    oldstatesw1 = newstatesw1; // Oldstate will be given the value of the new state
    
    /* Switch 2 configuration for turning off the RED LED*/
    
    
    if(newstatesw2 == 0 && newstatesw2 != oldstatesw2) {
        
        TurnRedOff(); // Turn Red Off
        
        wait(0.2);
        
        }
        
    oldstatesw2 = newstatesw2; 
    
    /* Switch 3 configuration for turning on the Greeen LED*/
    
        
    if(newstatesw3 == 1 && newstatesw3 != oldstatesw3) {
        
        TurnGreenOn(); // Turn Green On
        
        wait(0.2);
        
        }
        
    oldstatesw3 = newstatesw3;    
    
    /* Switch 4 configuration for turning off the Greeen LED*/  
        
    if(newstatesw4 == 1 && newstatesw4 != oldstatesw4) {
        
        TurnGreenOff(); // Turn Green Off
        
        wait(0.2);
        
        }
        
    oldstatesw4 = newstatesw4;      
    
    }

}
