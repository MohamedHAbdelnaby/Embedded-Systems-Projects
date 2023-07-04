#include "mbed.h"
#include <vector>
AnalogIn vout(p18); // Declaring AnalogIn to read the temperature
BusOut display(p5,p6,p7,p8,p9,p10,p11,p12); // BusOut for the display
InterruptIn switch1(p16, PullUp); // Switch 1 is connected to ground - Needs a PullUp resistor
InterruptIn switch2(p25, PullDown); // Switch 2 is connected to VCC - Needs a PullDown resistor

/*

        SegConverter methods takes an integer digit and returns this digit as a binary number fo the display
        
        Input: Integer (Temperature)
        
        Output: Integer (Binary number that will display the entered digit)



*/

int SegConverter(int digit) {
    
    switch(digit) {
        
        case 0: return 0b00111111; // Displaying 0
        case 1: return 0b00000110; // Displaying 1
        case 2: return 0b01011011; // Displaying 2
        case 3: return 0b01001111; // Displaying 3
        case 4: return 0b01100110; // Displaying 4
        case 5: return 0b01101101; // Displaying 5
        case 6: return 0b01111101; // Displaying 6
        case 7: return 0b00000111; // Displaying 7
        case 8: return 0b01111111; // Displaying 8
        case 9: return 0b01101111; // Displaying 9
        case 'C': return 0b00111001; // Displaying C
        case 'F': return 0b01110001; // Displaying F
        case '-': return 0b01000000; // Displaying -
        case '.': return 0b10000000; // Displaying . (in case we want the decimal point of the temperature)
        default: return 0; // Default is 0
        
        }
    
}

/*

    extractBit method aims to extract the bits/digits of the temperature sensor.
    It will be able to successfully extract all the digits of a given float. 
    
    Input: Float (temperature)
    Output: A vector of integers that contains the digits of a given float
    
    Note: Part of this method is commented out to meet the requirement of this project
    The commented out part will extract the decimal numbers up and will extract
    up to 4 significant figures




*/

vector<int> extractBit(float N) {
    
    vector<int> digits; // Declaring a vector of integers
    
       if(N < 0) { // Dealing with negative numbers
        
        display = SegConverter('-'); // Display Negative if it's a negative number
                
        wait(1); // Wait a second
        
        N = -N; // Change the sign of the negative number to become positive number
                  
      }
    
    int number = (int) N; // Casting will round up to the nearest integer.
    
    //The code below in case you want to display decimal point.
    
   // int decimal = (N - number)*100;
     
     //   for(int i = 0; i < 2; i++){
              
       //    digits.push_back(SegConverter(decimal%10));
              
         //  decimal = decimal / 10;
                      
      //}
            
    //digits.push_back(SegConverter('.'));
            
    while(number != 0) { // Extracting digits from the number; stop when number = 0
        
          digits.push_back(SegConverter(number%10)); // Adding the digit to the vector
        
          number = number / 10; // Dividing by 10 to be able to extract big
        
      }
    
    std::reverse(digits.begin(), digits.end()); // Reversing the vector to get the arranged digits
        
    return digits; // Return the vector of integers that contains the digits
        
        
    }
    
/*
    
    averageVoltage method is able to compute the average voltage over 1000 samples
    
    Input: Float (voltage)
    
    Output: Float (average voltage over 1000 samples)


*/

float averageVoltage(float voltage) {
    
    float average; // Declaring a float that will hold the average
    
    float sum; // Declaring a float that will hold the sum of voltages
    
    for(int i = 0; i < 1000; i++) { // A for loop to compute the voltage over 1000 samples
        
        sum = sum + voltage*3.3; // multiplying voltage by 3.3 
        
        }
        
        average = sum / 1000; // Dividing the sum by 1000 to get the average
        
        return average; // returning the average
        
    }
    
/*
    
    celsius method is able to compute the temperature in celsius
    
    Input: Float (voltage)
    
    Output: Float (temperature in celsius)


*/
    
float celsius(float vout) {
    
    float averageV = averageVoltage(vout); // Computing the average voltage over 1000 samples
          
    float c = (averageV - 0.400)/(0.0195); // Computing the temperature in celsius by using the equation given 
    
    return c; // Returning the temperature in celsius
    
    }
    
/*
    
    fahrenheit method is able to convert the temperature from celsius to fahrenheit
    
    Input: Float (Temperature in celsius)
    
    Output: Float (Temperature in fahrenheit)


*/
    
float fahrenheit(float c) {
    
    float f = (c*(9.0/5.0))+32; // Conversion equation
    
    return f; // Returning the temperature in fahrenheit
    
}

/*
  
    DisplayTemp method will be able to display the temperature 
    It takes a vector of integers that contains the digits of the temperature
    Then, it displays those digits on the display.
    
    Input: a vector of integers containing the temperature digits
    
    Output: void - No Output 


*/

void DisplayTemp(vector<int> digits) {
   
    for(int i = 0; i < digits.size(); i++) { // A for loop to assign each digit to the display
            
          display = digits.at(i); // Displaying a digit at index i of the vector
          
          wait(1); // Wait a second
          
          display = 0; // Blink led for 0.1 seconds before display the other digits 
          
          wait(0.1); // Wait 0.1 between blinking the display and showing the other digit
          
        } 
    
  }
  
/*

     DisplayC method will display the temperature in celsius. It takes a float that represents the output voltage from the mbed
     Then, it will call the extractBit method and also the celsius method to get the digits of the temperature then, it will call
     the DisplayTemo method that will display each of the digits.
     
     Input: Float that represents the output voltage connected to the temperature sensor
     
     Output: void - No output


*/
  

void DisplayC(float f) {
    
    vector<int> digits = extractBit(celsius(f)); // Extracting the digits 
       
    DisplayTemp(digits); // Displaying the digits
    
    display = 0; // Blink the display
          
    wait(0.1); // Wait 0.1 seconds
      
    display = SegConverter('C'); // Display C on the display to indicate that temperature is in celsuis
        
    wait(1); // Wait a second
   
    }
    
/*

      DisplayF will display the temperature in fahrenheit. It will call extractBit which will take a parameter
      that includes calling the fahrenheit function that will convert the temperature from celsuis to fahrenheit
      
      Input: Float that represents the output voltage from the temperature senesor 
      
      Output: void - No output



*/
    
void DisplayF(float f) {
    
       vector<int> digits = extractBit(fahrenheit(celsius(f)));
       
       DisplayTemp(digits);
       
       display = 0;
          
       wait(0.1);
       
       display = SegConverter('F');
       
       wait(1);
    
    
    }
    
// Declaring a volatile that will aid us in determining the state of each switch
    
volatile int lastswitch = 1;

/*

    
     interrupt1 will keep the state of lastswitch as 1 
     
     Input: void - No input
     
     Output: void - No output



*/
    
void interrupt1(void) {
          
    lastswitch = 1;  
          
          
}

/*

    
     interrupt1 will keep the state of lastswitch as 2
     
     Input: void - No input
     
     Output: void - No output



*/

void interrupt2(void) {
    
    lastswitch = 2;
    
    
}

int main() {
    
    switch1.fall(interrupt1); // Switch 1 is connected to ground, so it's a falling edge
        
    switch2.rise(interrupt2); // Switch 2 is connected to vcc, so it's a rising edge
    
    while(1) {
    
    if(lastswitch == 1)
    
    DisplayC(vout);   
    
    if(lastswitch == 2)
    
    DisplayF(vout);   
       
   }
   
}