
 /*
 * main.c
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
/* Example/Board Header files */
#include "Board.h"
#include "motor.h"
#include "cmd_int.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "IRSensor.h"
#include "uart.h"
#include <stdint.h>
#include "line_sensor.h"

extern UART_Handle uart;
extern UART_Params uartParams;


int32_t Left,Center,Right;

 int main(void){
    /* Call init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();
    Motors_Init();
    LineInit();
    cmd_Init();
    IRSensorInit();
    UartInit();


    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);
    /* This example has logging and many other debug capabilities enabled */
    System_printf("This example does not attempt to minimize code or data "
                  "footprint\n");
    System_flush();
    System_printf("Starting the Race. "
                  "SysMin. Halt the target to view any SysMin contents in "
                  "ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();
    /* Start BIOS */
    BIOS_start();
    return (0);
}

