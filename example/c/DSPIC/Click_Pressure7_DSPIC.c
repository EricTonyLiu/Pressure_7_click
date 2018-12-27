/*
Example for Pressure7 Click

    Date          : okt 2018.
    Author        : Katarina Perendic

Test configuration dsPIC :
    
    MCU                : P33FJ256GP710A
    Dev. Board         : EasyPIC Fusion v7
    dsPIC Compiler ver : v7.1.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module.
- Application Initialization - Initialization driver init, device reset, set OSR for measurement Pressure(D1) and Temperature(D2) data
                               and read calibration data from PROM.
- Application Task - (code snippet) -  Start measurement and reads Temperature data and Pressure data and logs data to USBUART every 500ms.

*/

#include "Click_Pressure7_types.h"
#include "Click_Pressure7_config.h"

float Temperature = 0;
float Pressure;
uint8_t promError;
char demoText[ 50 ];

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_PRESSURE7_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    mikrobus_logWrite(" --- System Init --- ", _LOG_LINE);
    Delay_100ms();
}

void applicationInit()
{
    pressure7_i2cDriverInit( (T_PRESSURE7_P)&_MIKROBUS1_GPIO, (T_PRESSURE7_P)&_MIKROBUS1_I2C, _PRESSURE7_DEVICE_SLAVE_ADDRESS );
    pressure7_reset();
    Delay_1sec();
    presusre7_setOverSamplingRatio(_PRESSURE7_CMD_CONVERT_D1_OSR_2048, _PRESSURE7_CMD_CONVERT_D2_OSR_2048);
    
    promError = pressure7_readPROM();
    if(promError == _PRESSURE7_PROM_READ_OK)
    {
        mikrobus_logWrite(" --- Read PROM - OK!!! ", _LOG_LINE);
    }
    else
    {
        mikrobus_logWrite(" --- Read PROM - ERROR!!! ", _LOG_LINE);
    }
    Delay_100ms();
}

void applicationTask()
{
    pressure7_startMeasurement();
    pressure7_getSensorData(&Temperature, &Pressure);

    FloatToStr(Temperature, demoText);
    demoText[6] = 0;
    mikrobus_logWrite(" Temperature : ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_TEXT);
    mikrobus_logWrite(" C ", _LOG_LINE);

    FloatToStr(Pressure, demoText);
    demoText[7] = 0;
    mikrobus_logWrite(" Pressure : ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_TEXT);
    mikrobus_logWrite(" mBar ", _LOG_LINE);
    
    mikrobus_logWrite("  ", _LOG_LINE);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}