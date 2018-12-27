/*
    __pressure7_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__pressure7_driver.h"
#include "__pressure7_hal.c"

/* ------------------------------------------------------------------- MACROS */

/* Command */
const uint8_t _PRESSURE7_CMD_RESET = 0x1E;
const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_256  = 0x40;
const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_512  = 0x42;
const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_1024 = 0x44;
const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_2048 = 0x46;
const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_4096 = 0x48;
const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_8192 = 0x4A;
const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_256  = 0x50;
const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_512  = 0x52;
const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_1024 = 0x54;
const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_2048 = 0x56;
const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_4096 = 0x58;
const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_8912 = 0x5A;
const uint8_t _PRESSURE7_CMD_ADC_READ            = 0x00;
const uint8_t _PRESSURE7_CMD_PROM_READ           = 0xA0;

/* PROM Address */
const uint8_t _PRESSURE7_PROM_ADDR_CRC = 0x00;
const uint8_t _PRESSURE7_PROM_ADDR_C1  = 0x01 << 1;
const uint8_t _PRESSURE7_PROM_ADDR_C2  = 0x02 << 1;
const uint8_t _PRESSURE7_PROM_ADDR_C3  = 0x03 << 1;
const uint8_t _PRESSURE7_PROM_ADDR_C4  = 0x04 << 1;
const uint8_t _PRESSURE7_PROM_ADDR_C5  = 0x05 << 1;
const uint8_t _PRESSURE7_PROM_ADDR_C6  = 0x06 << 1;
const uint8_t _PRESSURE7_PROM_ADDR_C7  = 0x07 << 1;

/* PROM ERROR */
const uint8_t _PRESSURE7_PROM_READ_ERROR = 1;
const uint8_t _PRESSURE7_PROM_READ_OK    = 0;

/* Device Slave Address */
const uint8_t _PRESSURE7_DEVICE_SLAVE_ADDRESS = 0x76;

/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __PRESSURE7_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* Read calibration data form PROM */
static uint16_t _PROM_C1;
static uint16_t _PROM_C2;
static uint16_t _PROM_C3;
static uint16_t _PROM_C4;
static uint16_t _PROM_C5;
static uint16_t _PROM_C6;
static uint16_t _PROM_CRC;

/* Read digital pressure and temperature data */
static volatile uint32_t _Pressure_D1;
static volatile uint32_t _Temperature_D2;

/* Calculate */
static int32_t _dT;
static int32_t _TEMP;
//static int64_t _OFF;
//static int64_t _SENS;
static int32_t _PRESSURE;

/*  Over sampling ratio */
static uint8_t _OSR_D1 = _PRESSURE7_CMD_CONVERT_D1_OSR_4096;
static uint8_t _OSR_D2 = _PRESSURE7_CMD_CONVERT_D2_OSR_4096;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint8_t _CRC4(uint16_t *n_prom);
static uint16_t _packageData16(uint8_t *inData);
static uint32_t _packageData24(uint8_t *inData);
static float _pow(uint8_t base, uint8_t ex);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint16_t _packageData16(uint8_t *inData)
{
    uint16_t outData;
    
    outData = inData[ 0 ];
    outData = outData << 8;
    outData = outData | inData[ 1 ];
    
    return outData;
}

static uint32_t _packageData24(uint8_t *inData)
{
    static volatile uint32_t outData;

    outData = inData[ 0 ] ;
    outData <<= 8;
    outData |= inData[ 1 ];
    outData <<= 8;
    outData |= inData[ 2 ];

    return outData;
}

static uint8_t _CRC4(uint16_t *n_prom)
{
    uint8_t cnt;
    uint16_t n_rem = 0;
    uint8_t n_bit;
    
    n_prom[ 0 ] = n_prom[ 0 ] & 0x0FFF;
    n_prom[ 7 ] = 0;
    
    for (cnt = 0; cnt < 16; cnt++)
    {
        if (cnt % 2 == 1)
        {
            n_rem^= n_prom[ cnt >> 1 ] & 0x00FF;
        }
        else
        {
            n_rem^= n_prom[ cnt >> 1 ] >> 8;
        }
        
        for (n_bit = 8; n_bit > 0; n_bit--)
        {
            if (n_rem & 0x8000)
            {
                n_rem = (n_rem << 1)^0x3000;
            }
            else
            {
                n_rem = n_rem << 1;
            }
        }
    }
    n_rem = (n_rem >> 12) & 0x000F;
    return (n_rem ^ 0x00);
}

static float _pow(uint8_t base, uint8_t ex)
{
    uint8_t cnt;
    uint32_t tmp = 1;
    
    for (cnt = 0; cnt < ex; cnt++)
    {
        tmp *= base;
    }
    
    return tmp;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __PRESSURE7_DRV_SPI__

void pressure7_spiDriverInit(T_PRESSURE7_P gpioObj, T_PRESSURE7_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __PRESSURE7_DRV_I2C__

void pressure7_i2cDriverInit(T_PRESSURE7_P gpioObj, T_PRESSURE7_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __PRESSURE7_DRV_UART__

void pressure7_uartDriverInit(T_PRESSURE7_P gpioObj, T_PRESSURE7_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

void pressure7_readData(uint8_t cmd, uint8_t *outData, uint8_t nData)
{
    uint8_t writeCmd;

    writeCmd = cmd;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, &writeCmd, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, outData, nData, END_MODE_STOP);
}

void pressure7_sendCommand(uint8_t cmd)
{
    uint8_t writeCmd;

    writeCmd = cmd;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, &writeCmd, 1, END_MODE_STOP);
}

void pressure7_reset()
{
    pressure7_sendCommand(_PRESSURE7_CMD_RESET);
}

uint8_t pressure7_readPROM()
{
    uint8_t readData[ 2 ];
    uint16_t crcTest[ 8 ];
    volatile uint8_t crcError;
    
    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_CRC, readData, 2);
    _PROM_CRC = _packageData16(readData);

    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_C1, readData, 2);
    _PROM_C1 = _packageData16(readData);
    
    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_C2, readData, 2);
    _PROM_C2 = _packageData16(readData);
    
    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_C3, readData, 2);
    _PROM_C3 = _packageData16(readData);
    
    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_C4, readData, 2);
    _PROM_C4 = _packageData16(readData);
    
    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_C5, readData, 2);
    _PROM_C5 = _packageData16(readData);
    
    pressure7_readData(_PRESSURE7_CMD_PROM_READ | _PRESSURE7_PROM_ADDR_C6, readData, 2);
    _PROM_C6 = _packageData16(readData);
    
    crcTest[ 0 ] = _PROM_CRC;
    crcTest[ 1 ] = _PROM_C1;
    crcTest[ 2 ] = _PROM_C2;
    crcTest[ 3 ] = _PROM_C3;
    crcTest[ 4 ] = _PROM_C4;
    crcTest[ 5 ] = _PROM_C5; 
    crcTest[ 6 ] = _PROM_C6;

    crcError = _CRC4(crcTest);
    if(crcError == (_PROM_CRC >> 12))
    {
        crcError = _PRESSURE7_PROM_READ_OK;
    }
    else
    {
        crcError = _PRESSURE7_PROM_READ_ERROR;
    }

    return crcError;
}
/* --------------------------------------------------------------- CALCULATE  */

void pressure7_startMeasurement()
{
    uint8_t writeCmd;
    uint8_t readData[ 3 ];
    
// TEMPERATURE CALCULATE
    pressure7_sendCommand(_OSR_D2);
    Delay_10ms();
    pressure7_readData(_PRESSURE7_CMD_ADC_READ, readData, 3);
    _Temperature_D2 = _packageData24(readData);

    _dT = _Temperature_D2 - _PROM_C5 * _pow(2,8);
    _TEMP = 2000 + _dT * (_PROM_C6 / _pow(2,23));

// PRESSURE CALCULATE
    pressure7_sendCommand(_OSR_D1);
    Delay_10ms();
    pressure7_readData(_PRESSURE7_CMD_ADC_READ, readData, 3);
    _Pressure_D1 = _packageData24(readData);
    
    //_OFF = (_PROM_C2 * _pow(2,16) + (_PROM_C4 *_dT) / _pow(2,7));
    //_SENS = (_PROM_C1 * _pow(2,15) + (_PROM_C3 * _dT) / _pow(2,8));
    _PRESSURE = (_Pressure_D1 * (_PROM_C1 * _pow(2,15) + (_PROM_C3 * _dT) / _pow(2,8)) / _pow(2,21)
                 - (_PROM_C2 * _pow(2,16) + (_PROM_C4 *_dT) / _pow(2,7))) / _pow(2,13);
}

void pressure7_getSensorData(float *Temperature, float *Pressure)
{
    *Temperature = _TEMP / 100.00;
    *Pressure = _PRESSURE / 10.0;
}

void presusre7_setOverSamplingRatio(uint8_t osrD1, uint8_t osrD2)
{
    _OSR_D1 = osrD1;
    _OSR_D2 = osrD2;
}

/* -------------------------------------------------------------------------- */
/*
  __pressure7_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */