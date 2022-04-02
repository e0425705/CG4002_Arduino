// This library allows communication with I2C devices
#include<Wire.h>

// I2C address of MPU-6050
const int MPU = 0x68; 

// Variables for accelerometer, temperature, gyro raw data
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup(){
  Serial.begin(9600);

  // join I2C bus
  Wire.begin();
  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.beginTransmission(MPU);
  // PWR_MGMT_1 register
  Wire.write(0x6B); 
  // set to zero (wakes up the MPU-6050)
  Wire.write(0);    
  Wire.endTransmission(true);
}

void loop(){
  Wire.beginTransmission(MPU);
  // starting with register 0x3B (ACCEL_XOUT_H) 
  // [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.write(0x3B);  
  // the parameter indicates that the Arduino will send a restart. 
  // As a result, the connection is kept active
  Wire.endTransmission(false);
  // Request for a total of 12 registers
  Wire.requestFrom(MPU, 12, true);  

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  // each sensor value had size of 2 byte
  
  // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  AcX = Wire.read()<<8 | Wire.read();    
  // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  AcY = Wire.read()<<8 | Wire.read();
  // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)  
  AcZ = Wire.read()<<8 | Wire.read();  
  // reading registers: 0x41 (GYRO_XOUT_H) and 0x42 (GYRO_XOUT_L)
  GyX = Wire.read()<<8 | Wire.read();  
  // reading registers: 0x43 (GYRO_YOUT_H) and 0x44 (GYRO_YOUT_L)
  GyY = Wire.read()<<8 | Wire.read();  
  // reading registers: 0x45 (GYRO_ZOUT_H) and 0x46 (GYRO_ZOUT_L)
  GyZ = Wire.read()<<8 | Wire.read();  

  // accelerometer +/- 2, 4, 8, or 16g
  // gyroscope +/- 250, 500, 1000, or 2000 deg/sec
  /* X/Y accel axes should read 0
  Z accel axis should read 1g, which is +16384 at a sensitivity of 2g
  X/Y/Z gyro axes should read 0 */

  /* BLACK BOARD offset values for initialising */
  
  AcX = AcX - 500;
  AcY = AcY - 300;
  AcZ = AcZ + 500;
  GyX = GyX + 2000;
  GyY = GyY + 10;
  GyZ = GyZ + 400;
  

  /* YELLOW BOARD offset values for initialising */
  /*
  AcX = AcX - 300;
  AcY = AcY - 1100;
  AcZ = AcZ + 1500;
  GyX = GyX + 1000;
  GyY = GyY + 400;
  GyZ = GyZ + 60;
  */

  /* Serial Monitor */
  /*
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  */

  /* Serial Plotter */
  /*
  Serial.print(AcX);
  Serial.print(" "); // a space ' ' or  tab '\t' character is printed between the two values.
  Serial.print(AcY);
  Serial.print(" "); // a space ' ' or  tab '\t' character is printed between the two values.
  Serial.print(AcZ);
  Serial.print(" "); // a space ' ' or  tab '\t' character is printed between the two values.
  Serial.print(GyX);
  Serial.print(" ");
  Serial.print(GyY);
  Serial.print(" ");
  Serial.println(GyZ);
  */

  // delay 100ms
  delay(100);

  // send data to ultra96 via bluetooth
}
