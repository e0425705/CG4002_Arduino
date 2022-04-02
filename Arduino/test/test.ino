/*
MIT License
Copyright 2021 Michael Schoeffler (https://www.mschoeffler.com)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <IRremote.h>

/* IR Transmitter D3 */
#define PIN_SEND 3
/* Button D5 */
//#define PIN_BUTTON 4                                                                        
/* Buzzer D4 */
#define PIN_BUZZER 5

void setup()  
{  
  // Initialize serial connection to print on the Serial Monitor of the Arduino IDE
  Serial.begin(9600);
  // Initializes IR Transmitter.yr
  IrSender.begin(PIN_SEND);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);

}  
                               
void loop()  
{  
  int buttonState = digitalRead(PIN_BUZZER);
  
  if (buttonState == HIGH) {
    Serial.println("Button pressed, sending signal...");

    /* Player 1 */
    // if receives a signal from D5, then send the following to D3
    IrSender.sendNEC(0x1111, 0x34, true, 0);

    /* Player 2 */
    // if receives a signal from D5, then send the following to D3
    //IrSender.sendNEC(0x1010, 0x34, true, 0);

    /* set buzzer as high for 100ms */
    digitalWrite(PIN_BUZZER, HIGH);
    delay(100);
    digitalWrite(PIN_BUZZER, LOW);
   }

  // Wait for 100ms
  delay(100); 
}  
