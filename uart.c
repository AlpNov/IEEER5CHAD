/*
 * modbus.c
 *
 *  Created on: Oct 26, 2014
 *      Author: Christopher Ahn & Khoa Van
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
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
/* Example/Board Header files */
#include "Board.h"

#include "motor.h"

#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"


#include <stdint.h>


UART_Handle uart;
UART_Params uartParams;


const char CRLF[] = "\r\n";
extern int deltaTime;
int distance;
int h=0;

int ct=0;
extern int32_t state ;
uint32_t Buffer1[11];
uint32_t Buffer2[11];
uint32_t* Fillptr=Buffer1;;
uint32_t* Txptr=Buffer1;



void UartInit(void){
	  /* Create a UART with data processing off. */
	    UART_Params_init(&uartParams);
	    uartParams.writeDataMode = UART_DATA_BINARY;
	    uartParams.readDataMode = UART_DATA_BINARY;
	    uartParams.readReturnMode = UART_RETURN_FULL;
	    uartParams.readEcho = UART_ECHO_ON;
	    uartParams.baudRate = 115200;
	    uart = UART_open(Board_UART1, &uartParams);
	    Fillptr=Buffer1;
}



void UART_print_int(uint32_t n, UART_Handle uart){
    if(n>=10){
        UART_print_int(n/10,uart);
        n=n%10;
    }
    char buf=(char)n+'0';
    UART_write(uart, &buf,1);
}

