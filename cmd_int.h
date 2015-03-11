/*
 * cmd_int.h
 *
 *  Created on: Feb 3, 2015
 *      Author: cmahn
 */

#ifndef CMD_INT_H_
#define CMD_INT_H_

struct cmd_to_funct{
	char cmd[2]; //command characters
	void (*fn)(void); //command function
};
void Forward(void);
void Reverse(void);
void Left1Test(void);
void Left2Test(void);
void Right1Test(void);
void Right2Test(void);
void InitialPinSet(void);
void ReversePinSet(void);
void Brake(void);
#endif /* CMD_INT_H_ */
