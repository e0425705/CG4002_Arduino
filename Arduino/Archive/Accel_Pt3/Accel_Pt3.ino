// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

// This library allows communication with I2C devices
#include "Wire.h" 

// I2C address of MPU-6050
const int MPU_ADDR = 0x68; 

// Variables for accelerometer raw data
int16_t AcX, AcY, AcZ; 
// Variables for temperature data
int16_t Tmp; 
// Variables for gyroscope raw data
int16_t GyX, GyY, GyZ; 

// Variables for initialising accelerometer raw data
//int16_t initAcX, initAcY, initAcZ = 0; 
// Variables for initialising gyroscope raw data
//int16_t initGyX, initGyY, initGyZ = 0; 

int16_t initialise = 0;

unsigned long myTime;

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
  // Begins a transmission to the I2C slave (GY-521 board)
  Wire.beginTransmission(MPU_ADDR);
  // starting with register 0x3B (ACCEL_XOUT_H) 
  // [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.write(0x3B); 
  // The parameter indicates that the Arduino will send a restart. 
  // As a result, the connection is kept active
  Wire.endTransmission(false); 
  // request a total of 7*2=14 registers
  Wire.requestFrom(MPU_ADDR, 14, true); 

  /* Initialising the data in accelerometer & gyroscope */
  /*
  if (initialise == 0) {
    delay(100);

    Serial.println("before 1 accelerometer & gyroscope");
    Serial.print(initAcX);
    Serial.print(",");
    Serial.print(initAcY);
    Serial.print(","); 
    Serial.print(initAcZ);
    Serial.print(",");
    Serial.print(initGyX);
    Serial.print(",");
    Serial.print(initGyY);
    Serial.print(",");
    Serial.println(initGyZ);
    
    AcX = Wire.read()<<8 | Wire.read(); 
    AcY = Wire.read()<<8 | Wire.read();
    AcZ = Wire.read()<<8 | Wire.read(); 
    Tmp = Wire.read()<<8 | Wire.read(); 
    GyX = Wire.read()<<8 | Wire.read(); 
    GyY = Wire.read()<<8 | Wire.read(); 
    GyZ = Wire.read()<<8 | Wire.read(); 

    initAcX = initAcX + AcX;
    initAcY = initAcY + AcY;
    initAcZ = initAcZ + AcZ;
    initGyX = initGyX + GyX;
    initGyY = initGyX + GyY;
    initGyZ = initGyX + GyZ;

    Serial.println("1 accelerometer & gyroscope");
    Serial.print(initAcX);
    Serial.print(",");
    Serial.print(initAcY);
    Serial.print(","); 
    Serial.print(initAcZ);
    Serial.print(",");
    Serial.print(initGyX);
    Serial.print(",");
    Serial.print(initGyY);
    Serial.print(",");
    Serial.println(initGyZ);

    delay(100);

    Serial.println("before 2 accelerometer & gyroscope");
    Serial.print(initAcX);
    Serial.print(",");
    Serial.print(initAcY);
    Serial.print(","); 
    Serial.print(initAcZ);
    Serial.print(",");
    Serial.print(initGyX);
    Serial.print(",");
    Serial.print(initGyY);
    Serial.print(",");
    Serial.println(initGyZ);

    AcX = Wire.read()<<8 | Wire.read(); 
    AcY = Wire.read()<<8 | Wire.read();
    AcZ = Wire.read()<<8 | Wire.read(); 
    Tmp = Wire.read()<<8 | Wire.read(); 
    GyX = Wire.read()<<8 | Wire.read(); 
    GyY = Wire.read()<<8 | Wire.read(); 
    GyZ = Wire.read()<<8 | Wire.read(); 

    initAcX = initAcX + AcX;
    initAcY = initAcY + AcY;
    initAcZ = initAcZ + AcZ;
    initGyX = initGyX + GyX;
    initGyY = initGyX + GyY;
    initGyZ = initGyX + GyZ;

    Serial.println("2 accelerometer & gyroscope");
    Serial.print(initAcX);
    Serial.print(",");
    Serial.print(initAcY);
    Serial.print(","); 
    Serial.print(initAcZ);
    Serial.print(",");
    Serial.print(initGyX);
    Serial.print(",");
    Serial.print(initGyY);
    Serial.print(",");
    Serial.println(initGyZ);

    delay(100);

    initAcX = initAcX / 2;
    initAcY = initAcY / 2;
    initAcZ = initAcZ / 2;
    initGyX = initGyX / 2;
    initGyY = initGyX / 2;
    initGyZ = initGyX / 2;
    
    initialise = 1;
  }

  Serial.println("accelerometer & gyroscope");
  Serial.print(initAcX);
  Serial.print(",");
  Serial.print(initAcY);
  Serial.print(","); 
  Serial.print(initAcZ);
  Serial.print(",");
  Serial.print(initGyX);
  Serial.print(",");
  Serial.print(initGyY);
  Serial.print(",");
  Serial.println(initGyZ);
  */
  
  /* "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
     Each sensor value had size of 2 byte */

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
  
  /*
  if (initialise == 0) {
    initAcX = initAcX + AcX;
    initAcY = initAcY + AcY;
    initAcZ = initAcZ + AcZ;
    initGyX = initGyX + GyX;
    initGyY = initGyX + GyY;
    initGyZ = initGyX + GyZ;
  
    initialise = 1;
  }*/

/*
  Serial.println("Before filter");
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
  Serial.println(GyZ);*/

  // accelerometer +/- 2, 4, 8, or 16g
  // gyroscope +/- 250, 500, 1000, or 2000 deg/sec
  /* X/Y accel axes should read 0
  Z accel axis should read 1g, which is +16384 at a sensitivity of 2g
  X/Y/Z gyro axes should read 0 */
  /*
  AcX = AcX - initAcX;
  AcY = AcY - initAcY;
  AcZ = AcZ - initAcZ;
  GyX = GyX - initGyX;
  GyY = GyY - initGyY;
  GyZ = GyZ - initGyZ;*/

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

  myTime = millis();
  /*
  AcX = AcX - initAcX;
  AcY = AcY - initAcY;
  AcZ = AcZ - initAcZ;
  GyX = GyX - initGyX;
  GyY = GyY - initGyY;
  GyZ = GyZ - initGyZ;
  */
  
  /*
  Serial.println("After filter");
  */
  
  /* Serial Plotter */
  //Serial.print(myTime);
  //Serial.print(",");
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
