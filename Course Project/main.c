/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#define PWM_PAN XPAR_PWM_0_PWM_AXI_BASEADDR
#define PWM_TILT XPAR_PWM_1_PWM_AXI_BASEADDR
#define GPIO_INPUTS XPAR_AXI_GPIO_0_DEVICE_ID
#define BTN_CHANNEL 1
#define SWS_CHANNEL 2
#define PERIOD 2000000
#define MIN_DUTY 90000
#define MAX_DUTY 223000

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "PWM.h"
#include "xparameters.h"
#include "sleep.h"
#include "xgpio.h"
#include "PmodJSTK2.h"
#include "math.h"
#include "PmodOLED.h"

XGpio Gpio;
PmodJSTK2 joystick;
PmodOLED myDevice;

_Bool btn = 0;
int pan_value = (MIN_DUTY + MAX_DUTY)/2;
int tilt_value = (MIN_DUTY + MAX_DUTY)/2;
const u8 orientation = 0x0;
const u8 invert = 0x0;

void initLPT();
void driverLoop();
void servoJoy();
void squarePattern();
void circlePattern();
void linePattern();
void crossPattern();
void reset();

int main()
{
    init_platform();
    initLPT();
    driverLoop();

    cleanup_platform();
    return 0;
}

void initLPT(){
	PWM_Set_Period(PWM_PAN, PERIOD);
	PWM_Set_Period(PWM_TILT, PERIOD);
	PWM_Set_Duty(PWM_PAN, (MIN_DUTY + MAX_DUTY)/2, 0);
	PWM_Set_Duty(PWM_TILT, (MIN_DUTY + MAX_DUTY)/2, 0);
	u8 *pat;

	XGpio_Initialize(&Gpio, GPIO_INPUTS);
	XGpio_SetDataDirection(&Gpio, BTN_CHANNEL, 0xf);
	XGpio_SetDataDirection(&Gpio, SWS_CHANNEL, 0xf);

	OLED_Begin(&myDevice, XPAR_PMODOLED_0_AXI_LITE_GPIO_BASEADDR,
	         XPAR_PMODOLED_0_AXI_LITE_SPI_BASEADDR, orientation, invert);

	pat = OLED_GetStdPattern(0);
	OLED_SetFillPattern(&myDevice, pat);
	OLED_SetCharUpdate(&myDevice, 0);

	JSTK2_begin(
	      &joystick,
	      XPAR_PMODJSTK2_0_AXI_LITE_SPI_BASEADDR,
	      XPAR_PMODJSTK2_0_AXI_LITE_GPIO_BASEADDR
	   );
	JSTK2_setInversion(&joystick, 0, 1);

	PWM_Enable(PWM_PAN);
	PWM_Enable(PWM_TILT);
}

void driverLoop(){
	while(1){
		switch(XGpio_DiscreteRead(&Gpio, SWS_CHANNEL)){
			case 0x0:
				reset();
				break;
			case 0x1:
				servoJoy();
				break;
			case 0x2:
				squarePattern();
				break;
			case 0x3:
				linePattern();
				break;
			case 0x4:
				crossPattern();
				break;
			case 0x5:
				circlePattern();
				break;

			default :
				reset();
				break;
		}
	}
}

void reset(){
	pan_value = (MIN_DUTY + MAX_DUTY)/2;
	tilt_value = (MIN_DUTY + MAX_DUTY)/2;

	OLED_ClearBuffer(&myDevice);
	OLED_SetCursor(&myDevice, 0, 0);
	OLED_PutString(&myDevice, "Idle                      ");
	OLED_Update(&myDevice);

	PWM_Set_Duty(PWM_PAN, pan_value, 0); // Sets Duty for PWM 0 ip connected to pan servo
	PWM_Set_Duty(PWM_TILT, tilt_value, 0); // Sets Duty for PWM 1 ip connected to tilt servo
	PWM_Enable(PWM_PAN);
	PWM_Enable(PWM_TILT);
	usleep(20000);
}

void servoJoy(){
	JSTK2_Position position;
	position = JSTK2_getPosition(&joystick);

	printf("X: %d, Y: %d\n\r", position.XData, position.YData);
	OLED_ClearBuffer(&myDevice);
	OLED_SetCursor(&myDevice, 0, 0);
	OLED_PutString(&myDevice, "Joystick Control           ");
	OLED_Update(&myDevice);

	pan_value += 60 * (position.XData - 128);
	tilt_value += 60 * (position.YData - 128);

	if(pan_value > MAX_DUTY) pan_value = MAX_DUTY;
	if(pan_value < MIN_DUTY) pan_value = MIN_DUTY;
	if(tilt_value > MAX_DUTY) tilt_value = MAX_DUTY;
	if(tilt_value < MIN_DUTY) tilt_value = MIN_DUTY;

	PWM_Set_Duty(PWM_PAN, pan_value, 0);
	PWM_Set_Duty(PWM_TILT, tilt_value, 0);

	usleep(20000);
}

void squarePattern(){
	int sqMin = MIN_DUTY + 2*(MAX_DUTY-MIN_DUTY)/8;
	int sqMax = MIN_DUTY + 5*(MAX_DUTY-MIN_DUTY)/8;
	pan_value = sqMin;
	tilt_value = sqMin;

	OLED_ClearBuffer(&myDevice);
	OLED_SetCursor(&myDevice, 0, 0);
	OLED_PutString(&myDevice, "Square Pattern           ");
	OLED_Update(&myDevice);

	PWM_Set_Duty(PWM_PAN, pan_value, 0);
	PWM_Set_Duty(PWM_TILT, tilt_value, 0);

	for(int i = sqMin; i < sqMax; i += 16000){
		pan_value = i;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = sqMin; i < sqMax; i += 16000){
		tilt_value = i;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > sqMin; i -= 16000){
		pan_value = i;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > sqMin; i -= 16000){
		tilt_value = i;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}
}

void circlePattern(){
	int sqMin = MIN_DUTY + 2*(MAX_DUTY-MIN_DUTY)/8;
	int sqMax = MIN_DUTY + 5*(MAX_DUTY-MIN_DUTY)/8;
	pan_value = sqMin;
	tilt_value = sqMin;

	OLED_ClearBuffer(&myDevice);
	OLED_SetCursor(&myDevice, 0, 0);
	OLED_PutString(&myDevice, "Circle Pattern           ");
	OLED_Update(&myDevice);

	PWM_Set_Duty(PWM_PAN, pan_value, 0);
	PWM_Set_Duty(PWM_TILT, tilt_value, 0);

	for(int i = sqMin; i < sqMax; i += 32000){
		pan_value = i;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = sqMin; i < sqMax; i += 32000){
		tilt_value = i;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > sqMin; i -= 32000){
		pan_value = i;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > sqMin; i -= 32000){
		tilt_value = i;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}
}

void linePattern(){
	int sqMin = MIN_DUTY + 2*(MAX_DUTY-MIN_DUTY)/8;
	int sqMax = MIN_DUTY + 5*(MAX_DUTY-MIN_DUTY)/8;

	OLED_ClearBuffer(&myDevice);
	OLED_SetCursor(&myDevice, 0, 0);
	OLED_PutString(&myDevice, "Line Pattern           ");
	OLED_Update(&myDevice);

	PWM_Set_Duty(PWM_PAN, sqMin, 0);
	PWM_Set_Duty(PWM_TILT, (MIN_DUTY + MAX_DUTY)/2, 0);

	for(int i = sqMin; i < sqMax; i += 8000){
		pan_value = i;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > sqMin; i -= 8000){
		pan_value = i;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}
}

void crossPattern(){
	int sqMin = MIN_DUTY + 2*(MAX_DUTY-MIN_DUTY)/8;
	int sqMax = MIN_DUTY + 5*(MAX_DUTY-MIN_DUTY)/8;
	int halfWay = (sqMin + sqMax)/2;
	pan_value = sqMin;
	tilt_value = sqMin;

	OLED_ClearBuffer(&myDevice);
	OLED_SetCursor(&myDevice, 0, 0);
	OLED_PutString(&myDevice, "Cross Pattern           ");
	OLED_Update(&myDevice);

	PWM_Set_Duty(PWM_PAN, pan_value, 0);
	PWM_Set_Duty(PWM_TILT, halfWay, 0);

	for(int i = sqMin; i < halfWay; i += 8000){
		pan_value = i;
		if(pan_value > halfWay) pan_value = halfWay;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = halfWay; i < sqMax; i += 8000){
		tilt_value = i;
		if(tilt_value > sqMax) pan_value = sqMax;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > halfWay; i -= 8000){
		tilt_value = i;
		if(tilt_value < halfWay) pan_value = halfWay;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}

	for(int i = halfWay; i < sqMax; i += 8000){
		pan_value = i;
		if(tilt_value > sqMax) pan_value = sqMax;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = sqMax; i > halfWay; i -= 8000){
		pan_value = i;
		if(tilt_value < halfWay) pan_value = halfWay;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}

	for(int i = halfWay; i > sqMin; i -= 8000){
		tilt_value = i;
		if(tilt_value < sqMin) pan_value = sqMin;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}

	for(int i = sqMin; i < halfWay; i += 8000){
		tilt_value = i;
		if(tilt_value > halfWay) pan_value = halfWay;
		PWM_Set_Duty(PWM_TILT, tilt_value, 0);
		usleep(20000);
	}

	for(int i = halfWay; i > sqMin; i -= 8000){
		pan_value = i;
		if(tilt_value < sqMin) pan_value = sqMin;
		PWM_Set_Duty(PWM_PAN, pan_value, 0);
		usleep(20000);
	}
}



