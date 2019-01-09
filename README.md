![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Pressure7 Click

- **CIC Prefix**  : PRESSURE7
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : okt 2018.

---


### Software Support

We provide a library for the Pressure7 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2621/pressure-7-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines the I2C bus driver and drivers that offer a choice for sending a command and read data from register.
The library includes function for read Temperature data and Pressure data, function for read calibration data from PROM and function for start measurement.
The user also has the function for reset device and function for set OSR(Over sampling ratio) for Pressure and Temperature measurement data.

Key functions :

- ``` uint8_t pressure7_readPROM() ``` - Functions for read calibration data from PROM
- ``` void pressure7_startMeasurement() ``` - Functions for start measurement and calculation data
- ``` void pressure7_getSensorData(float *Temperature, float *Pressure) ``` - Functions for read Pressure and Temperature data

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module.
- Application Initialization - Initialization driver init, device reset, set OSR for measurement Pressure(D1) and Temperature(D2) data
                               and read calibration data from PROM.
- Application Task - (code snippet) -  Start measurement and reads Temperature data and Pressure data and logs data to USBUART every 500ms.

```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2621/pressure-7-click) page.

Other mikroE Libraries used in the example:

- I2C

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
