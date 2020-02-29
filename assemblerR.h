/*
 * This file includes common system header files, several local header
 * files widely used in the assembler program, and signatures for other
 * commonly used functions.
 * 
 * Author: Nikhil Sodemba
 * Date Created: Feb, 20th, 2020
 */

#ifndef _ASSEMBLERR_H
#define _ASSEMBLERR_H

#include "assembler.h"

void assemblerR(char * instName, char * restOfInstruction,
                        int lineNum);

void printBinary(int num, int maxPow);
int getRegNum(char *reg);

#endif
