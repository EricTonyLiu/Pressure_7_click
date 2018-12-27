/*
    __pressure7_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __pressure7_driver.h
@brief    Pressure7 Driver
@mainpage Pressure7 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   PRESSURE7
@brief      Pressure7 Click Driver
@{

| Global Library Prefix | **PRESSURE7** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **okt 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _PRESSURE7_H_
#define _PRESSURE7_H_

/** 
 * @macro T_PRESSURE7_P
 * @brief Driver Abstract type 
 */
#define T_PRESSURE7_P    const uint8_t*

/** @defgroup PRESSURE7_COMPILE Compilation Config */              /** @{ */

//  #define   __PRESSURE7_DRV_SPI__                            /**<     @macro __PRESSURE7_DRV_SPI__  @brief SPI driver selector */
   #define   __PRESSURE7_DRV_I2C__                            /**<     @macro __PRESSURE7_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __PRESSURE7_DRV_UART__                           /**<     @macro __PRESSURE7_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup PRESSURE7_VAR Variables */                           /** @{ */

/* Command */
extern const uint8_t _PRESSURE7_CMD_RESET;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_256 ;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_512 ;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_1024;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_2048;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_4096;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D1_OSR_8192;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_256 ;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_512 ;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_1024;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_2048;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_4096;
extern const uint8_t _PRESSURE7_CMD_CONVERT_D2_OSR_8912;
extern const uint8_t _PRESSURE7_CMD_ADC_READ           ;
extern const uint8_t _PRESSURE7_CMD_PROM_READ          ;

/* PROM Address */
extern const uint8_t _PRESSURE7_PROM_ADDR_CRC ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C1  ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C2  ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C3  ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C4  ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C5  ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C6  ;
extern const uint8_t _PRESSURE7_PROM_ADDR_C7  ;

/* PROM ERROR */
extern const uint8_t _PRESSURE7_PROM_READ_ERROR ;
extern const uint8_t _PRESSURE7_PROM_READ_OK    ;

/* Device Slave Address */
extern const uint8_t _PRESSURE7_DEVICE_SLAVE_ADDRESS;

                                                                       /** @} */

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup PRESSURE7_INIT Driver Initialization */              /** @{ */

#ifdef   __PRESSURE7_DRV_SPI__
void pressure7_spiDriverInit(T_PRESSURE7_P gpioObj, T_PRESSURE7_P spiObj);
#endif
#ifdef   __PRESSURE7_DRV_I2C__
void pressure7_i2cDriverInit(T_PRESSURE7_P gpioObj, T_PRESSURE7_P i2cObj, uint8_t slave);
#endif
#ifdef   __PRESSURE7_DRV_UART__
void pressure7_uartDriverInit(T_PRESSURE7_P gpioObj, T_PRESSURE7_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void pressure7_gpioDriverInit(T_PRESSURE7_P gpioObj);
                                                                       /** @} */
/** @defgroup PRESSURE7_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions for read data from address / register
 *
 * @param[in] cmd        Command
 * @param[in] outData    Output data buffer
 * @param[in] nData      Number of bytes
 */
void pressure7_readData(uint8_t cmd, uint8_t *outData, uint8_t nData);

/**
 * @brief Functions for send Command
 *
 * @param[in] cmd        Command
 */
void pressure7_sendCommand(uint8_t cmd);

/**
 * @brief Functions for start reset sequence
 */
void pressure7_reset();

/**
 * @brief Functions for read calibration data from PROM
 *
 * @return CRC information (READ PROM - OK or ERROR)
 *
 * @note This function must be performed at the beginning of the program in order to read the calibrated data from the PROM 
         required to calculate the Pressure and Temperature measurement.
 */
uint8_t pressure7_readPROM();

/**
 * @brief Functions for start measurement and calculation data
 *
 * @note This function are called at the beginning of each measurement before the function returns the Temperature and Pressure values.
         This function reads digital pressure and temperature data, then calculates these values with values read from the PROM.
         Before calling this function, you need to set OSR (Over sampling ratio) for Pressure(D1) and Temperature(D2) data.
 */
void pressure7_startMeasurement();

/**
 * @brief Functions for read Pressure and Temperature data
 *
 * @param[out] Temperature      Output Temperature data in C
 * @param[out] Pressure         Output Pressure data in mBar
 */
void pressure7_getSensorData(float *Temperature, float *Pressure);

/**
 * @brief Functions for set OSR(Over sampling ratio) for Pressure(D1) and Temperature(D2) data
 *
 * @param[in] osrD1        OSR for Pressure data
 * @param[in] osrD2        OSR for Temperature data
 *
 * @note OSR data (256,512,1024,2048,4095,8192)
 */
void presusre7_setOverSamplingRatio(uint8_t osrD1, uint8_t osrD2);





                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Pressure7_STM.c
    @example Click_Pressure7_TIVA.c
    @example Click_Pressure7_CEC.c
    @example Click_Pressure7_KINETIS.c
    @example Click_Pressure7_MSP.c
    @example Click_Pressure7_PIC.c
    @example Click_Pressure7_PIC32.c
    @example Click_Pressure7_DSPIC.c
    @example Click_Pressure7_AVR.c
    @example Click_Pressure7_FT90x.c
    @example Click_Pressure7_STM.mbas
    @example Click_Pressure7_TIVA.mbas
    @example Click_Pressure7_CEC.mbas
    @example Click_Pressure7_KINETIS.mbas
    @example Click_Pressure7_MSP.mbas
    @example Click_Pressure7_PIC.mbas
    @example Click_Pressure7_PIC32.mbas
    @example Click_Pressure7_DSPIC.mbas
    @example Click_Pressure7_AVR.mbas
    @example Click_Pressure7_FT90x.mbas
    @example Click_Pressure7_STM.mpas
    @example Click_Pressure7_TIVA.mpas
    @example Click_Pressure7_CEC.mpas
    @example Click_Pressure7_KINETIS.mpas
    @example Click_Pressure7_MSP.mpas
    @example Click_Pressure7_PIC.mpas
    @example Click_Pressure7_PIC32.mpas
    @example Click_Pressure7_DSPIC.mpas
    @example Click_Pressure7_AVR.mpas
    @example Click_Pressure7_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __pressure7_driver.h

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