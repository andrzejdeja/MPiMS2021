/*
L3G4200D.cpp - Class file for the L3G4200D Triple Axis Gyroscope Arduino Library.

Version: 1.3.3
(c) 2014 Korneliusz Jarzebski
www.jarzebski.pl

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include <Wire.h>
#include <math.h>

#include "L3G4200D.hpp"

bool L3G4200D::begin(l3g4200d_dps_t scale, l3g4200d_odrbw_t odrbw)
{
    // Reset calibrate values
    d.XAxis = 0;
    d.YAxis = 0;
    d.ZAxis = 0;

    Wire.begin();

    // Check L3G4200D Who Am I Register
    if (readRegister8(L3G4200D_REG_WHO_AM_I) != 0xD3)
    {
	return false;
    }

    // Enable all axis and setup normal mode + Output Data Range & Bandwidth
    uint8_t reg1 = 0x00;
    reg1 |= 0x0F; // Enable all axis and setup normal mode
    reg1 |= (odrbw << 4); // Set output data rate & bandwidh
    writeRegister8(L3G4200D_REG_CTRL_REG1, reg1);

    // Disable high pass filter
    writeRegister8(L3G4200D_REG_CTRL_REG2, 0x00);

    // Generata data ready interrupt on INT2
    writeRegister8(L3G4200D_REG_CTRL_REG3, 0x08);

    // Set full scale selection in continous mode
    writeRegister8(L3G4200D_REG_CTRL_REG4, scale << 4);

    // Boot in normal mode, disable FIFO, HPF disabled
    writeRegister8(L3G4200D_REG_CTRL_REG5, 0x00);

    return true;
}

// Get current scale
l3g4200d_dps_t L3G4200D::getScale(void)
{
    return (l3g4200d_dps_t)((readRegister8(L3G4200D_REG_CTRL_REG4) >> 4) & 0x03);
}


// Get current output data range and bandwidth
l3g4200d_odrbw_t L3G4200D::getOdrBw(void)
{
    return (l3g4200d_odrbw_t)((readRegister8(L3G4200D_REG_CTRL_REG1) >> 4) & 0x0F);
}

// Calibrate algorithm
void L3G4200D::calibrate(uint8_t samples)
{
    // Reset values
    int16_t sumX = 0;
    int16_t sumY = 0;
    int16_t sumZ = 0;
    // Read n-samples
    for (uint8_t i = 0; i < samples; ++i) {
      	readRaw();
      	sumX += r.XAxis;
      	sumY += r.YAxis;
      	sumZ += r.ZAxis;
    }
    // Calculate delta vectors
    d.XAxis = sumX / samples;
    d.YAxis = sumY / samples;
    d.ZAxis = sumZ / samples;
}

// Write 8-bit to register
void L3G4200D::writeRegister8(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
    Wire.endTransmission();
}

// Read 8-bit from register
uint8_t L3G4200D::readRegister8(uint8_t reg)
{
    uint8_t value;

    Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(reg);
    Wire.endTransmission();

    Wire.beginTransmission(L3G4200D_ADDRESS);
    Wire.requestFrom(L3G4200D_ADDRESS, 1);
    while(!Wire.available()) {};
	value = Wire.read();
    Wire.endTransmission();

    return value;
}

// Read raw values
Vector L3G4200D::readRaw()
{
    while(1){
        uint8_t zyxda = readRegister8(L3G4200D_REG_STATUS_REG);
        if (zyxda & (0b1 << 3) != 0) break;
    }
	uint8_t xla = readRegister8(L3G4200D_REG_OUT_X_L);
	uint8_t xha = readRegister8(L3G4200D_REG_OUT_X_H);
	uint8_t yla = readRegister8(L3G4200D_REG_OUT_Y_L);
	uint8_t yha = readRegister8(L3G4200D_REG_OUT_Y_H);
	uint8_t zla = readRegister8(L3G4200D_REG_OUT_Z_L);
	uint8_t zha = readRegister8(L3G4200D_REG_OUT_Z_H);

    r.XAxis = (short)(xha << 8 | xla);
    r.YAxis = (short)(yha << 8 | yla);
    r.ZAxis = (short)(zha << 8 | zla);
   
    return r;
}
