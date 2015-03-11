/*
 * IRSensor.c
 *
 *  Created on: Feb 9, 2015
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
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
/* Example/Board Header files */
#include "Board.h"
#include "motor.h"

#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include <stdint.h>
unsigned long dist;



extern UART_Handle uart;
extern UART_Params uartParams;


int reading;
int analogFlag=0;
int analogCt;
int x=0;


void IRSensorInit(void){
		SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
		ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
		ADCSequenceStepConfigure(ADC0_BASE,3,0,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
		ADCSequenceEnable(ADC0_BASE, 3);
}


void CheckIR(){
	uint32_t ANGRead[1];

	ADCProcessorTrigger(ADC0_BASE, 3);
	while(!ADCIntStatus(ADC0_BASE, 3, false)){
	}
	ADCIntClear(ADC0_BASE, 3);
	ADCSequenceDataGet(ADC0_BASE, 3, ANGRead);
	reading=ANGRead[0];
	analogFlag=1;
	analogCt++;
}




