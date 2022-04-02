//Arduino-IRremote library will be added
#include <IRremote.h>
#include <IRremoteInt.h>

IRsend irsend;
#define PIN_SEND 3
// #define PIN_SEND 5

// The configuration of the output pin will be made by the library
// The output pin is a different one for different arduinos
// Arduino UNO: Output = D3, Arduino MEGA: Output = D9
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //IrSender.begin(PIN_SEND);
}

// should put no break such that when powered, will transmit immediately
void loop() {
  // put your main code here, to run repeatedly:
  // The transmitter sends the signal A90 (hex. decimal form) in the encoding "RC5"
  // It will be transmitted 10 times after that it will make a 5 second break
  for (int i = 0; i < 10; i++) {
  // ADD if (bullet > 0)
    // Change this for different transmitter such that receiver can differentiate
    //irsend.sendRC5(0xA90, 12); //[12] Bit-length signal (hex A90=1010 1001 0000)
    //irsend.sendSAMSUNG(0xE0E040BF, 32);
    irsend.sendNEC(0xA0A0A0A0, 32);
    //irsend.sendKaseikyo_Mitsubishi(0x36480000, 32);
    delay(100);
    Serial.println("Sending an impulse...");
  }

  // 5 second break between the sending impulses
  //delay(5000); 
}
