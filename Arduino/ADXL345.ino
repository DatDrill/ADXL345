// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADXL345
// This code is designed to work with the ADXL345_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=ADXL345_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// ADXL345 I2C address is 0x53(83)
#define Addr 0x53

void setup()
{
  // Initialise I2C communication as MASTER 
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Begin transmission with given device on I2C bus
  Wire.beginTransmission(Addr);
  // Select Bandwidth rate register
  Wire.write(0x2C);
  // Normal mode, Output data rate = 100 Hz
  Wire.write(0x0A);
  // Stop I2C transmission on the device
  Wire.endTransmission();

  // Begin transmission with given device on I2C bus
  Wire.beginTransmission(Addr);
  // Select Power control register
  Wire.write(0x2D);
  // Normal mode, auto-sleep disable
  Wire.write(0x08);
  // Stop I2C transmission on the device
  Wire.endTransmission();

  // Begin transmission with given device on I2C bus
  Wire.beginTransmission(Addr);
  // Select Data format register
  Wire.write(0x31);
  // Self test disabled, 4-wire interface, Full resolution, range = +/-2g
  Wire.write(0x08);
  // Stop I2C transmission on the device
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  int data[6];
  for(int i = 0; i < 6; i++)
  {
    // Begin transmission with given device on I2C bus
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write((50 + i));
    // Stop I2C transmission on the device
    Wire.endTransmission();

    // Request 1 byte of data from the device
    Wire.requestFrom(Addr, 1);

    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }

  // Convert the data to 10-bits
  int xAccl = (((data[1] & 0x03) * 256) + data[0]);
  if(xAccl > 511)
  {
    xAccl -= 1024;
  }
  int yAccl = (((data[3] & 0x03) * 256) + data[2]);
  if(yAccl > 511)
  {
    yAccl -= 1024;
  }
  int zAccl = (((data[5] & 0x03) * 256) + data[4]);
  if(zAccl > 511)
  {
    zAccl -= 1024;
  }
  // Output data to screen
  Serial.print("Acceleration in X-Axis is :");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis is :");
  Serial.println(yAccl);
  Serial.print("Acceleration in Z-Axis is :");
  Serial.println(zAccl);
  delay(1000);
}
