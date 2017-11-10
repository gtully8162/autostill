/***************************************************
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "MAX31865.h"
//#include <QThread>
#include <wiringPiSPI.h>
#include <stdlib.h>
#include<QDebug>
#include <cmath>

MAX31865::MAX31865(int spiChannel, int spiSpeed):
    m_spiChannel(spiChannel),
    m_spiSpeed(spiSpeed),
    m_csPin(24)
{    
}
void MAX31865::init()
{
    const int SPI_MODE = 1;
    //initialize spi port for temperature probe
   wiringPiSPISetupMode(m_spiChannel, m_spiSpeed, SPI_MODE);
   setWires(MAX31865_3WIRE);
   enableBias(true);
   autoConvert(true);
   clearFault();
}

uint8_t MAX31865::readFault(void) {
  return readRegister8(MAX31856_FAULTSTAT_REG);
}

void MAX31865::clearFault(void) {
  uint8_t t = readRegister8(MAX31856_CONFIG_REG);
  t &= ~0x2C;
  t |= MAX31856_CONFIG_FAULTSTAT;
  writeRegister8(MAX31856_CONFIG_REG, t);
}

void MAX31865::enableBias(bool b) {
  uint8_t t = readRegister8(MAX31856_CONFIG_REG);
  if (b) {
    t |= MAX31856_CONFIG_BIAS;       // enable bias
  } else {
    t &= ~MAX31856_CONFIG_BIAS;       // disable bias
  }
  writeRegister8(MAX31856_CONFIG_REG, t);
}

void MAX31865::autoConvert(bool b) {
  uint8_t t = readRegister8(MAX31856_CONFIG_REG);
  if (b) {
    t |= MAX31856_CONFIG_MODEAUTO;       // enable autoconvert
  } else {
    t &= ~MAX31856_CONFIG_MODEAUTO;       // disable autoconvert
  }
  writeRegister8(MAX31856_CONFIG_REG, t);
}

void MAX31865::setWires(max31865_numwires_t wires ) {
  uint8_t t = readRegister8(MAX31856_CONFIG_REG);
  if (wires == MAX31865_3WIRE) {
    t |= MAX31856_CONFIG_3WIRE;
  } else {
    // 2 or 4 wire
    t &= ~MAX31856_CONFIG_3WIRE;
  }

  writeRegister8(MAX31856_CONFIG_REG, t);
}

float  MAX31865::temperature(float RTDnominal, float refResistor) {
  // http://www.analog.com/media/en/technical-documentation/application-notes/AN709_0.pdf

  float Z1, Z2, Z3, Z4, Rt, temp;

  Rt = readRTD();
  Rt /= 32768;
  Rt *= refResistor;

  //Serial.print("Resistance: "); Serial.println(Rt, 8);

  Z1 = -RTD_A;
  Z2 = RTD_A * RTD_A - (4 * RTD_B);
  Z3 = (4 * RTD_B) / RTDnominal;
  Z4 = 2 * RTD_B;

  temp = Z2 + (Z3 * Rt);
  temp = (sqrt(temp) + Z1) / Z4;

  if (temp >= 0) return temp;

  // ugh.
  float rpoly = Rt;

  temp = -242.02;
  temp += 2.2228 * rpoly;
  rpoly *= Rt;  // square
  temp += 2.5859e-3 * rpoly;
  rpoly *= Rt;  // ^3
  temp -= 4.8260e-6 * rpoly;
  rpoly *= Rt;  // ^4
  temp -= 2.8183e-8 * rpoly;
  rpoly *= Rt;  // ^5
  temp += 1.5243e-10 * rpoly;

  return temp;
}

uint16_t MAX31865::readRTD (void) {
  clearFault();

  uint8_t msb = readRegister8(MAX31856_RTDMSB_REG);
  uint8_t lsb = readRegister8(MAX31856_RTDLSB_REG);

  uint16_t rtd = (msb << 8)  | lsb;
  // remove fault
  rtd >>= 1;

  return rtd;
}

/**********************************************/

uint8_t MAX31865::readRegister8(uint8_t addr) {
  unsigned char xfer[2];
  xfer[0] = addr & 0x7F;
  xfer[1] = 0;
  wiringPiSPIDataRW(m_spiChannel, xfer, 2);
  return xfer[1];
}

uint16_t MAX31865::readRegister16(uint8_t addr) {
    unsigned char xfer[3];
    xfer[0] = addr & 0x7F;
    xfer[1] = 0;
    wiringPiSPIDataRW(m_spiChannel, xfer, 3);

    uint16_t ret = xfer[1];
    ret <<= 8;
    ret |= xfer[2];

    return ret;
}

void MAX31865::writeRegister8(uint8_t addr, uint8_t data)
{
//  addr |= 0x80;
  unsigned char xfer[2];
  xfer[0] = addr | 0x80; // make sure top bit is set
  xfer[1] = data;
  wiringPiSPIDataRW(m_spiChannel, xfer, 2);
}
