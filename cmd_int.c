/*
 * cmd_int.c
 *
 *  Created on: Feb 3, 2015
 *      Author: cmahn
 */

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
/* Example/Board Header files */
#include "Board.h"
#include "motor.h"
#include "cmd_int.h"
#include "inc/hw_pwm.h"
#include "driverlib/pwm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"

#include <stdint.h>


#include <string.h>
#include <stdio.h>
#include <stdbool.h>

extern UART_Handle uart;
extern UART_Params uartParams;

char inputC1[2];

void cmd_Init(void){
	InitialPinSet();
}

const struct cmd_to_funct director[]=
{
		{"FW",&Forward},
		{"RV",&Reverse},
		{"L1",&Left1Test},
		{"L2",&Left2Test},
		{"R1",&Right1Test},
		{"R2",&Right2Test},
		{"IS",&InitialPinSet},
		{"RS",&ReversePinSet},
		{"BK",&Brake}

		//,
		//{"SP",&Stop},
		//{"00",&Nothin}
};


void InterpretTask(char *tag){
	//while(1){
		//Semaphore_pend(CmdSema,BIOS_WAIT_FOREVER);
		int i=0;
		while((director[i].cmd[0] != '0') && (director[i].cmd[1] != '0')){
			if((director[i].cmd[0] == tag[0]) && (director[i].cmd[1] == tag[1])){
			(*director[i].fn)();
			//(*director[i].fn)(int);
			}
			i++;
		}
		//Semaphore_post(RXSema);
	//}
}

//void Motors_shift(uint32_t l1, uint32_t l2, uint32_t r1, uint32_t r2){

void RXCmdTask(void){
	while(1){
    	UART_read(uart, &inputC1,2);
        	InterpretTask((char*)inputC1);

	}
}

void InitialPinSet(void){
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6|GPIO_PIN_7,0);
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,(GPIO_PIN_6));
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,(GPIO_PIN_4));
}
void ReversePinSet(void){
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6|GPIO_PIN_7,(GPIO_PIN_6|GPIO_PIN_7));
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,0);
}

void Forward(void){
		Motors_shift(93,93,93,93);
}

void Reverse(void){
		Motors_shift(93,93,93,93);
}

void Left1Test(void){
		Motors_shift(90,99,99,99);
}

void Left2Test(void){
		Motors_shift(99,90,99,99);
}

void Right1Test(void){
		Motors_shift(99,99,90,99);
}

void Right2Test(void){
		Motors_shift(99,99,99,90);
}

void Brake(void){
	//	Motors_shift(99,99,99,99);
        MotorStop();
}
