//Arduino-IRremote library will be added
#include <IRremote.h>
#include <IRremoteInt.h>

//...and here initialized
IRsend irsend;

// The configuration of the output pin will be made by the library
// The output pin is a different one for different arduinos
// Arduino UNO: Output = D3
// Arduino MEGA: Output = D9
// Beetle: Output = A0
// You will find a full list of output pins on the website:
// http://z3t0.github.io/Arduino-IRremote/
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  // The transmitter sends the signal A90 (hex. decimal form) in the encoding "RC5"
  // It will be transmitted 3 times after that it will make a 5 second break
  for (int i = 0; i < 3; i++) {
  // Change this for different transmitter such that receiver can differentiate
  irsend.sendRC5(0xA90, 12); //[12] Bit-length signal (hex A90=1010 1001 0000)
  delay(40);
  }

  // no breaks, continuously sends signal
  //delay(5000); // 5 second break between the sending impulses
}
