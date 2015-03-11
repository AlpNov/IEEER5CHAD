/*
 * line_sensor.c
 *
 *  Created on: Feb 17, 2015
 *      Author: cmahn
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
/* Example/Board Header files */
#include "Board.h"
#include "motor.h"
#include "uart.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include <stdint.h>
unsigned long dist;


char inputC2[]=" ";
char inputC3[]="\n";
extern UART_Handle uart;
extern UART_Params uartParams;

int L,C,R;
void LineInit(void){
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5,(GPIO_PIN_4|GPIO_PIN_5));
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,(GPIO_PIN_3));

}

void LineClock(void){
    Semaphore_post(SensorSemaAlpha);
}


void ReadSensorsW(void){
		while(1){
		    Semaphore_pend(SensorSemaAlpha,BIOS_WAIT_FOREVER);
			//set the line sensor pins to output
		    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5);
	        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_3);
	        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_4|GPIO_PIN_5);
	        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,GPIO_PIN_3);
	        //set timer for 10 us for charging Line Sensors
	        Timer_start(timer1);
	        //wait for Semaphore Post for SensorSema
	        Semaphore_pend(SensorSema,BIOS_WAIT_FOREVER);
	        //performing PID calculations
	        UART_print_int(L,uart);
            UART_write(uart,&inputC2,1);
	        UART_print_int(C,uart);
            UART_write(uart,&inputC2,1);
	        UART_print_int(R,uart);
	        UART_write(uart,&inputC3,1);
		}

 //-> //errorCheck();
}

void LineSensorInput_ISR(void){
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_PIN_3);
    Timer_start(timer2);

}


void LineSensorRead_ISR(void){

    // using 6-line sensor
    /*Begin reading sensors, then setting sensor value to binary 1 or 0*/
        L=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_3);
        L=(L==8) ? 1 : 0 ;
    	C=GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4);
        C=(C==16) ? 1 : 0 ;
        R=GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_5);
        R=(R==32) ? 1 : 0 ;
    	/*End Reading line sensors*/
        Semaphore_post(SensorSema);

}
