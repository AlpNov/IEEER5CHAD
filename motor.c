/*
 * Motor.C
 *
 *  Created on: Oct 25, 2014
 *      Author: Christopher Ahn & Khoa Van
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
/*Uart monitor files*/
#include <ti/sysbios/knl/Clock.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
 #include <ti/drivers/UART.h>


/* Example/Board Header files */
#include "Board.h"

#include <stdbool.h>
#include <stdint.h>
#include <ti/drivers/GPIO.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"
#include "driverlib/pwm.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "Motor.h"
#include "line_sensor.h"
unsigned long ulPeriod;
unsigned long distance;


extern UART_Handle uart;
extern UART_Params uartParams;



void Motors_Init(){


	    //Set the clock

	   //Configure PWM Clock to match system
	   SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	   // Enable the peripherals used by this program.
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins
	    ulPeriod = SysCtlClockGet()/200; //PWM frequency 200HZ

	    //Configure PF1,PF2,PF3 Pins as PWM
	    GPIOPinConfigure(GPIO_PA6_M1PWM2);
	    GPIOPinConfigure(GPIO_PA7_M1PWM3);
	    GPIOPinConfigure(GPIO_PF2_M1PWM6);
	    GPIOPinConfigure(GPIO_PF3_M1PWM7);
	    GPIOPinTypePWM(GPIO_PORTA_BASE,GPIO_PIN_6 | GPIO_PIN_7);
	    GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_2 | GPIO_PIN_3);

	    //Configure PWM Options
	    //PWM_GEN_2 Covers M1PWM4 and M1PWM5
	    //PWM_GEN_3 Covers M1PWM6 and M1PWM7 See page 207 4/11/13 DriverLib doc
	    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

	    //Set the Period (expressed in clock ticks)
	    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ulPeriod+1);
	    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ulPeriod+1);

	    //Set PWM duty-50% (Period * % value)
	    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,ulPeriod*(99/100));
	    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,ulPeriod*(99/100));
	    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,ulPeriod*(99/100));
	    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,ulPeriod*(99/100));



	    // Turn on the Output pins
	    PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT |PWM_OUT_3_BIT|PWM_OUT_6_BIT|PWM_OUT_7_BIT, true);

		GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_6);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4);
		GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_6|GPIO_PIN_7);
		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);
		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0);
		GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,0);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,0);
        // Do not allow PWM Generators to begin until told to do so
	    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
	    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
	    Motors_shift(99,99,99,99);
}

void Motors_shift(uint32_t l1, uint32_t l2, uint32_t r1, uint32_t r2){
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,ulPeriod*l1/100);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,ulPeriod*l2/100);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,ulPeriod*r1/100);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,ulPeriod*r2/100);
	PWMGenEnable(PWM1_BASE, PWM_GEN_1);
	PWMGenEnable(PWM1_BASE, PWM_GEN_3);
}

void MotorStop(void){
    PWMGenDisable(PWM1_BASE, PWM_GEN_1);
    PWMGenDisable(PWM1_BASE, PWM_GEN_3);
}




