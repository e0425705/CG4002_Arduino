// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

//#include "I2Cdev.h"
//#include "MPU6050.h"

#include <MPU6050_light.h>

// This library allows communication with I2C devices
#include "Wire.h" 

unsigned long myTime;

MPU6050 mpu(Wire);

void setup() {
  // baud rate
  Serial.begin(115200);

  // join I2C bus
  Wire.begin();

  mpu.begin();
  mpu.calcGyroOffsets();
}

void loop() {

  mpu.update();
  //float tmp = mpu.getTemp();
  //float angle[3] = {mpu.getAngleX(),mpu.getAngleY(),mpu.getAngleZ()};
  float accel[3] = {mpu.getAccX(), mpu.getAccY(), mpu.getAccZ()};
  float gyro[3] = {mpu.getGyroX(), mpu.getGyroY(), mpu.getGyroZ()};
  
  /*
  Serial.print("Device Temperature: ");Serial.print(tmp);Serial.println(" Celsius");
  Serial.print("Angles (degrees): x=");Serial.print(angle[0]);
  Serial.print(", y=");Serial.print(angle[1]);
  Serial.print(", z=");Serial.println(angle[2]);
  */

  myTime = millis();

  /* Serial Monitor */
  /*
  Serial.print("Time");Serial.println(myTime);
  Serial.println("");
  
  Serial.print("Acceleration (g aka 9.81m/s^2): x=");Serial.print(accel[0]);
  Serial.print(", y=");Serial.print(accel[1]);
  Serial.print(", z=");Serial.println(accel[2]);
  Serial.println("");
  
  Serial.print("Gyro (degrees/s): x=");Serial.print(gyro[0]);
  Serial.print(", y=");Serial.print(gyro[1]);
  Serial.print(", z=");Serial.println(gyro[2]);
  */

  /* Serial Plotter */
  Serial.print(myTime);
  Serial.print(",");
  Serial.print(accel[0]);
  Serial.print(",");
  Serial.print(accel[1]);
  Serial.print(","); 
  Serial.print(accel[2]);
  Serial.print(",");
  Serial.print(gyro[0]);
  Serial.print(",");
  Serial.print(gyro[1]);
  Serial.print(",");
  Serial.println(gyro[2]);
  
  // delay 100ms
  delay(100);

  // send data to ultra96 via bluetooth
}
