/**
 * This is the assembler utilities file, the functions used
 * in this file will help the assembler functions process
 * its' instructions correctly.
 * 
 * There are two functions in this file: printBinary(...) and 
 * getRegNum(...) both functions have detailed explainations to
 * how they work in their respective comments.
 * 
 * Author: Nikhil Sodemba
 * Date Created: Feb, 20th, 2020
 * 
 */

#include "assembler.h"

/**
 * This function will print the binary representation 
 * of a decimal number to stdout. 
 * 
 * The function takes two parameters as arguments: num and maxPow,
 *      - num is the decimal integer and maxPow is the number of bits in the binary number
 * 
 * Pre-condition: 
 *      - the value of maxPow must be large enough to represent the decimal integer - num.
 *      - maxPow shouldn't be greater than 31 (inclusive of 0).
 * 
 */
void printBinary(int num, int maxPow)
{
    // local variables
    int n, c, k, x;
    // assign n to decimal integer we are trying to convert.
    n = num;

    // Array to hold the binary representation
    int binary[maxPow];

    // loop through powers of 2
    for (c = maxPow; c >= 0; c--)
    {
        // Using Shift operator 
        k = n >> c;
        
        if (k & 1)
        {
            binary[c] = 1;
        }
        else
        {
            binary[c] = 0;
        }
    }
    // print binary number to stdout
    for(x = maxPow; x >= 0; x--)
    {
        printf("%d",binary[x]);
    }
    return;
}

/**
 * This function is used to validate whether or not the register
 * is a legitimate one. 
 * 
 * The function takes 1 argument: the register.
 *
 * The function will return the register number, if it 
 * exists, else return -1.
 * 
 * Error Handling will be taken care of in the callback.
 */
int getRegNum(char *reg)
{
    // iterator value
    int x;

    int regNum = -1;

    // array of all registers
    char * regArray[] =
    {
            "$zero",
            "$at",
            "$v0","$v1",
            "$a0","$a1","$a2","$a3",
            "$t0", "$t1", "$t2", "$t3", "$t4",
            "$t5", "$t6", "$t7",
            "$s0", "$s1", "$s2", "$s3", "$s4",
            "$s5", "$s6", "$s7",
            "$t8", "$t9", "$k0", "$k1", "$gp",
            "$sp", "$fp", "$ra"
    };

    // Loop through regArray to find match
    for(x = 0; x<32; x++)
    {
        if(strcmp(regArray[x], reg) == 0)
        {
            regNum = x;
            break;   
        }
    }
    return regNum;;
}
