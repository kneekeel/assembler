/*
 * This file includes common system header files, several local header
 * files widely used in the assembler program, and signatures for other
 * commonly used functions.
 */

#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>     /* May need to be _stdlib.h on some machines. */
#include <string.h>	/* Might be memory.h on some machines. */
#include <ctype.h>

#include "LabelTable.h"
#include "getToken.h"
#include "printFuncs.h"
#include "process_arguments.h"
#include "same.h"

int getNTokens (char * instructionBuffer, int N, char * results[]);
LabelTable pass1 (FILE * fp);
void pass2 (FILE * fp, LabelTable table);

void assemblerR(char * instName, char * restOfInstruction,
                        int lineNum);

void assemblerI(char * instName, char * restOfInstruction,
                        int lineNum, LabelTable table);

void assemblerJ(char * instName, char * restOfInstruction,
                        int lineNum, LabelTable table);

void printBinary(int num, int maxPow);
int getRegNum(char *reg);

#endif
