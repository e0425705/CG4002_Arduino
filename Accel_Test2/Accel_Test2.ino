/*
   Get all possible data from MPU6050
   Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
   Gyro values are given in deg/s
   Angles are given in degrees
   Note that X and Y are tilt angles and not pitch/roll.

   License: MIT

   from: https://github.com/rfetick/MPU6050_light/blob/master/examples/GetAllData/GetAllData.ino
*/

/* This library allows communication with I2C devices */
#include "Wire.h"

/* This library allows calibrates Accelerometer and Gyroscope data */
#include <MPU6050_light.h>

/* Constructor of MPU6050 */
MPU6050 mpu(Wire);

/* Get timing */
unsigned long timer = 0;

void setup() {
  /* Baud rate */
  Serial.begin(9600);

  /* Join I2C bus */
  Wire.begin();

  /* Start communication with the MPU6050 device
     Sets status to 0 when success 
     Accelerometer range = +- 2 g
     Gyroscope range = +- 250 deg/s */
  /* 
     0: Accelerometer range = +- 2 g
     1: Accelerometer range = +- 4 g
     2: Accelerometer range = +- 8 g
     3: Accelerometer range = +- 16 g
   
     0: Gyroscope range = +- 250 deg/s
     1: Gyroscope range = +- 500 deg/s
     2: Gyroscope range = +- 1000 deg/s
     3: Gyroscope range = +- 2000 deg/s

     Variables set gyro, set accel
  */
  byte status = mpu.begin(0, 0);

  /* Stop everything if could not connect to MPU6050 */
  while (status != 0) { }

  /* One second to collect and calibrate data */
  delay(1000);

  /* Compute gyroscope and accelerometer offsets to remove measurement bias
     MPU6050 device must be on a at surface during the calibration */
  mpu.calcOffsets(true, true);

  /* Indicate finish offset */
  //Serial.println("Done!\n");
}

void loop() {
  /* Update data. This function must be called in the loop as often as possible
     to get consistent angleX, angleY and angleZ. As angles rely on the
     integration of the gyroscope data between two updates, a longer delay leads
     to a less accurate integration. */
  mpu.update();

  /* Prints data every 100 ms */
  if (millis() - timer > 100) { 
    /* Serial Monitor */
    /*
      Serial.print("Time: ");Serial.println(millis());
      Serial.println("");

      Serial.print("Acceleration (g aka 9.81m/s^2): x=");Serial.print(mpu.getAccX());
      Serial.print(", y=");Serial.print(mpu.getAccY());
      Serial.print(", z=");Serial.println(mpu.getAccZ());
      Serial.println("");

      Serial.print("Gyro (degrees/s): x=");Serial.print(mpu.getGyroX());
      Serial.print(", y=");Serial.print(mpu.getGyroY());
      Serial.print(", z=");Serial.println(mpu.getGyroZ());
    */

    /* Serial Plotter */
    //Serial.print(millis());
    //Serial.print(",");
    Serial.print(mpu.getAccX());
    Serial.print(",");
    Serial.print(mpu.getAccY());
    Serial.print(",");
    Serial.print(mpu.getAccZ());
    Serial.print(",");
    Serial.print(mpu.getGyroX());
    Serial.print(",");
    Serial.print(mpu.getGyroY());
    Serial.print(",");
    Serial.println(mpu.getGyroZ());

    timer = millis();
  }

  // send data to ultra96 via bluetooth
}
