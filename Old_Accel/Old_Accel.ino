// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

// This library allows communication with I2C devices
#include "Wire.h" 

// I2C address of MPU-6050
const int MPU_ADDR = 0x68; 

// Variables for accelerometer raw data
int16_t AcX, AcY, AcZ; 
// Variables for gyroscope raw data
int16_t GyX, GyY, GyZ; 
// Variables for temperature data
int16_t Tmp; 

unsigned long myTime;

// Temporary variable used in convert function
/* The convert-function makes sure that all sensor values have the 
same width when they are printed out to the serial monitor later. */
//char tmp_str[7]; 

/* Converts int16 to string. Moreover, resulting strings will 
have the same length in the debug monitor. */
/*
char* convert_int16_to_str(int16_t i) { 
  sprintf(tmp_str, "%6d", i);
  
  return tmp_str;
}
*/

void setup() {
  // baud rate
  Serial.begin(9600);
  //Serial.begin(115200);

  // join I2C bus
  Wire.begin();
  
  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.beginTransmission(MPU_ADDR); 
  // PWR_MGMT_1 register
  Wire.write(0x6B); 
  // Set to zero (wakes up the MPU-6050)
  Wire.write(0); 
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  // starting with register 0x3B (ACCEL_XOUT_H) 
  // [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.write(0x3B); 
  // the parameter indicates that the Arduino will send a restart. 
  // As a result, the connection is kept active
  Wire.endTransmission(false); 
  // request a total of 7*2=14 registers
  Wire.requestFrom(MPU_ADDR, 14, true); 
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  // Each sensor value had size of 2 byte

  // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  AcX = Wire.read()<<8 | Wire.read(); 
  // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  AcY = Wire.read()<<8 | Wire.read();
  // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L) 
  AcZ = Wire.read()<<8 | Wire.read(); 
  // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  Tmp = Wire.read()<<8 | Wire.read(); 
  // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  GyX = Wire.read()<<8 | Wire.read(); 
  // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  GyY = Wire.read()<<8 | Wire.read(); 
  // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  GyZ = Wire.read()<<8 | Wire.read(); 

  // accelerometer +/- 2, 4, 8, or 16g
  // gyroscope +/- 250, 500, 1000, or 2000 deg/sec
  /* X/Y accel axes should read 0
  Z accel axis should read 1g, which is +16384 at a sensitivity of 2g
  X/Y/Z gyro axes should read 0 */

  /* BLACK BOARD offset values for initialising */
  
  AcX = AcX;
  AcY = AcY;
  AcZ = AcZ + 1500;
  Tmp = Tmp;
  GyX = GyX;
  GyY = GyY + 400;
  GyZ = GyZ + 50;
  
  
  /* YELLOW BOARD offset values for initialising */
  /*
  AcX = AcX - 1350;
  AcY = AcY;
  AcZ = AcZ + 1800;
  Tmp = Tmp;
  GyX = GyX + 450;
  GyY = GyY + 50;
  GyZ = GyZ - 300;
  */

  /* Serial Monitor */
  /*
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  // the following equation was taken from the documentation 
  // [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print("Temperature: ");
  Serial.print("Tmp = "); Serial.println(Tmp/340.00+36.53);
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  */

  /* Serial Plotter */
  /*
  Serial.print(AcX);
  Serial.print(" ");
  Serial.print(AcY);
  Serial.print(" "); 
  Serial.print(AcZ);
  //Serial.print(" ");
  //Serial.print(Tmp/340.00+36.53);
  Serial.print(" ");
  Serial.print(GyX);
  Serial.print(" ");
  Serial.print(GyY);
  Serial.print(" ");
  Serial.println(GyZ);
  */

  myTime = millis();

  //Serial.println(myTime);
  Serial.print(myTime);
  Serial.print(",");
  Serial.print(AcX);
  Serial.print(",");
  Serial.print(AcY);
  Serial.print(","); 
  Serial.print(AcZ);
  Serial.print(",");
  Serial.print(Tmp/340.00+36.53);
  Serial.print(",");
  Serial.print(GyX);
  Serial.print(",");
  Serial.print(GyY);
  Serial.print(",");
  Serial.println(GyZ);
  
  // delay 100ms
  delay(100);

  // send data to ultra96 via bluetooth
}
