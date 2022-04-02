/*
MIT License
Copyright 2021 Michael Schoeffler (https://www.mschoeffler.com)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <IRremote.h>

/* PLAYER 1 */
//#define PIN_RECV A1

/* PLAYER 2 */
#define PIN_RECV A2

/* Define buzzer at receiver end */
#define PIN_BUZZER 4

void setup()  
{  
  // Initialize serial connection to print on the Serial Monitor of the Arduino IDE
  Serial.begin(9600); 
  // Initialize the IR Receiver
  IrReceiver.begin(PIN_RECV); 

  pinMode(PIN_BUZZER, OUTPUT);
}  
                               
void loop()  
{  
  if (IrReceiver.decode()) {
    Serial.println("Player has received something...");    

    /* Buzzer buzz */
    digitalWrite(PIN_BUZZER, HIGH);
    delay(100);
    digitalWrite(PIN_BUZZER, LOW);
    
    // Prints a summary of the received data
    /* Player 1: Protocol=NEC Address=0x1111 Command=0x34 Raw-Data=0xCB340102 32 bits LSB first */
    /* PLayer 2: Protocol=NEC Address=0x1010 Command=0x34 Raw-Data=0xCB340102 32 bits LSB first */    
    IrReceiver.printIRResultShort(&Serial);   
    Serial.println();
    
    // To receive the next IR signal
    IrReceiver.resume(); 
  }  
}  
