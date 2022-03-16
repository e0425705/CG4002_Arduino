// Arduino-IRremote library will be added
#include <IRremote.h>
#include <IRremoteInt.h>

// You can declare the input pin for the signal output of the KY-022 here
//int RECV_PIN = 11;
//int RECV_PIN = A1;
int RECV_PIN = A2;

// Arduino-IRremote library will be initialized
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Infrared receiver will start
}

void loop() {
  // put your main code here, to run repeatedly:
  // It will be checked if the receiver has gotten a signal.
  if (irrecv.decode(&results)) {
  
  //At signal input, the received and decoded signal will show via serial console.
  //Serial.println(IrReceiver.decodedIRData.results.value, HEX);
  Serial.println(results.value, HEX);
  irrecv.resume();
 }
}
