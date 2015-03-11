#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Motor.h
 *
 *  Created on: Oct 25, 2014
 *      Author: kdvan */

//#ifndef MOTOR_H_
#define MOTOR_H_
//Put Driver Codes here

#ifndef MOTOR_H
#define MOTOR_H

extern void Motors_Init(void);
void Motors_shift(uint32_t r1, uint32_t r2, uint32_t l1, uint32_t l2);


#ifdef __cplusplus
}
#endif
#endif /* MOTOR_H_ */
