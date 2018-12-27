#line 1 "D:/Clicks_git/P/Pressure_7_click/SW/example/c/ARM/STM/Click_Pressure7_STM.c"
#line 1 "d:/clicks_git/p/pressure_7_click/sw/example/c/arm/stm/click_pressure7_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "d:/clicks_git/p/pressure_7_click/sw/example/c/arm/stm/click_pressure7_config.h"
#line 1 "d:/clicks_git/p/pressure_7_click/sw/example/c/arm/stm/click_pressure7_types.h"
#line 3 "d:/clicks_git/p/pressure_7_click/sw/example/c/arm/stm/click_pressure7_config.h"
const uint32_t _PRESSURE7_I2C_CFG[ 1 ] =
{
 100000
};
#line 31 "D:/Clicks_git/P/Pressure_7_click/SW/example/c/ARM/STM/Click_Pressure7_STM.c"
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
 pressure7_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, _PRESSURE7_DEVICE_SLAVE_ADDRESS );
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
