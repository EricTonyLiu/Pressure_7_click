_systemInit:
;Click_Pressure7_STM.c,36 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Pressure7_STM.c,38 :: 		mikrobus_i2cInit( _MIKROBUS1, &_PRESSURE7_I2C_CFG[0] );
MOVW	R0, #lo_addr(__PRESSURE7_I2C_CFG+0)
MOVT	R0, #hi_addr(__PRESSURE7_I2C_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_i2cInit+0
;Click_Pressure7_STM.c,39 :: 		mikrobus_logInit( _LOG_USBUART_A, 9600 );
MOVW	R1, #9600
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_Pressure7_STM.c,40 :: 		mikrobus_logWrite(" --- System Init --- ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr1_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_Pressure7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,41 :: 		Delay_100ms();
BL	_Delay_100ms+0
;Click_Pressure7_STM.c,42 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_Pressure7_STM.c,44 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Pressure7_STM.c,46 :: 		pressure7_i2cDriverInit( (T_PRESSURE7_P)&_MIKROBUS1_GPIO, (T_PRESSURE7_P)&_MIKROBUS1_I2C, _PRESSURE7_DEVICE_SLAVE_ADDRESS );
MOVS	R2, __PRESSURE7_DEVICE_SLAVE_ADDRESS
MOVW	R1, #lo_addr(__MIKROBUS1_I2C+0)
MOVT	R1, #hi_addr(__MIKROBUS1_I2C+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_pressure7_i2cDriverInit+0
;Click_Pressure7_STM.c,47 :: 		pressure7_reset();
BL	_pressure7_reset+0
;Click_Pressure7_STM.c,48 :: 		Delay_1sec();
BL	_Delay_1sec+0
;Click_Pressure7_STM.c,49 :: 		presusre7_setOverSamplingRatio(_PRESSURE7_CMD_CONVERT_D1_OSR_2048, _PRESSURE7_CMD_CONVERT_D2_OSR_2048);
MOVS	R1, __PRESSURE7_CMD_CONVERT_D2_OSR_2048
MOVS	R0, __PRESSURE7_CMD_CONVERT_D1_OSR_2048
BL	_presusre7_setOverSamplingRatio+0
;Click_Pressure7_STM.c,51 :: 		promError = pressure7_readPROM();
BL	_pressure7_readPROM+0
MOVW	R1, #lo_addr(_promError+0)
MOVT	R1, #hi_addr(_promError+0)
STRB	R0, [R1, #0]
;Click_Pressure7_STM.c,52 :: 		if(promError == _PRESSURE7_PROM_READ_OK)
CMP	R0, __PRESSURE7_PROM_READ_OK
IT	NE
BNE	L_applicationInit0
;Click_Pressure7_STM.c,54 :: 		mikrobus_logWrite(" --- Read PROM - OK!!! ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr2_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_Pressure7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,55 :: 		}
IT	AL
BAL	L_applicationInit1
L_applicationInit0:
;Click_Pressure7_STM.c,58 :: 		mikrobus_logWrite(" --- Read PROM - ERROR!!! ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr3_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr3_Click_Pressure7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,59 :: 		}
L_applicationInit1:
;Click_Pressure7_STM.c,60 :: 		Delay_100ms();
BL	_Delay_100ms+0
;Click_Pressure7_STM.c,61 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_Pressure7_STM.c,63 :: 		void applicationTask()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Pressure7_STM.c,65 :: 		pressure7_startMeasurement();
BL	_pressure7_startMeasurement+0
;Click_Pressure7_STM.c,66 :: 		pressure7_getSensorData(&Temperature, &Pressure);
MOVW	R1, #lo_addr(_Pressure+0)
MOVT	R1, #hi_addr(_Pressure+0)
MOVW	R0, #lo_addr(_Temperature+0)
MOVT	R0, #hi_addr(_Temperature+0)
BL	_pressure7_getSensorData+0
;Click_Pressure7_STM.c,68 :: 		FloatToStr(Temperature, demoText);
MOVW	R0, #lo_addr(_Temperature+0)
MOVT	R0, #hi_addr(_Temperature+0)
LDR	R0, [R0, #0]
MOVW	R1, #lo_addr(_demoText+0)
MOVT	R1, #hi_addr(_demoText+0)
BL	_FloatToStr+0
;Click_Pressure7_STM.c,69 :: 		demoText[6] = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_demoText+6)
MOVT	R0, #hi_addr(_demoText+6)
STRB	R1, [R0, #0]
;Click_Pressure7_STM.c,70 :: 		mikrobus_logWrite(" Temperature : ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr4_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr4_Click_Pressure7_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,71 :: 		mikrobus_logWrite(demoText, _LOG_TEXT);
MOVS	R1, #1
MOVW	R0, #lo_addr(_demoText+0)
MOVT	R0, #hi_addr(_demoText+0)
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,72 :: 		mikrobus_logWrite(" C ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr5_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr5_Click_Pressure7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,74 :: 		FloatToStr(Pressure, demoText);
MOVW	R0, #lo_addr(_Pressure+0)
MOVT	R0, #hi_addr(_Pressure+0)
LDR	R0, [R0, #0]
MOVW	R1, #lo_addr(_demoText+0)
MOVT	R1, #hi_addr(_demoText+0)
BL	_FloatToStr+0
;Click_Pressure7_STM.c,75 :: 		demoText[7] = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_demoText+7)
MOVT	R0, #hi_addr(_demoText+7)
STRB	R1, [R0, #0]
;Click_Pressure7_STM.c,76 :: 		mikrobus_logWrite(" Pressure : ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr6_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr6_Click_Pressure7_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,77 :: 		mikrobus_logWrite(demoText, _LOG_TEXT);
MOVS	R1, #1
MOVW	R0, #lo_addr(_demoText+0)
MOVT	R0, #hi_addr(_demoText+0)
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,78 :: 		mikrobus_logWrite(" mBar ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr7_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr7_Click_Pressure7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,80 :: 		mikrobus_logWrite("  ", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr8_Click_Pressure7_STM+0)
MOVT	R0, #hi_addr(?lstr8_Click_Pressure7_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Pressure7_STM.c,81 :: 		Delay_ms( 1000 );
MOVW	R7, #6911
MOVT	R7, #183
NOP
NOP
L_applicationTask2:
SUBS	R7, R7, #1
BNE	L_applicationTask2
NOP
NOP
NOP
;Click_Pressure7_STM.c,82 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationTask
_main:
;Click_Pressure7_STM.c,84 :: 		void main()
SUB	SP, SP, #4
;Click_Pressure7_STM.c,86 :: 		systemInit();
BL	_systemInit+0
;Click_Pressure7_STM.c,87 :: 		applicationInit();
BL	_applicationInit+0
;Click_Pressure7_STM.c,89 :: 		while (1)
L_main4:
;Click_Pressure7_STM.c,91 :: 		applicationTask();
BL	_applicationTask+0
;Click_Pressure7_STM.c,92 :: 		}
IT	AL
BAL	L_main4
;Click_Pressure7_STM.c,93 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
