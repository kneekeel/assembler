/**
 * This is the Assembler R-Format file, used to process R-Format
 * instructions from assembly language to machine code. 
 * 
 * Author: Nikhil Sodemba
 * Date Created: Feb, 20th, 2020
 * 
 */

#include "assembler.h"
#include "assemblerUtil.h"

/**
 * This function is used to process R-Format instructions into 
 * machine language.
 * 
 * The function takes in 3 arguments: instName, restOfInstruction, 
 * and lineNum.
 * 
 * Will print out the instruction (machine language) to stdout
 * 
 * Will handle errors accordingly and print them to stderr.
 * 
 * 
 */
void assemblerR(char * instName, char * restOfInstruction,
                        int lineNum)
{
    char * arguments[3];    /* registers or values after instruction name */

    // variables to compare instNum with
    char * jr = "jr", *sll = "sll", *srl = "srl";
    // The opcode for all R-Format Instructions is 0
    char * opcode = "000000";

    // variable to store decimal value of funct operation.
    int * functDec = 0;
    // Arrays for all funct operations
    char * functOps [] = 
    {
        "add", "addu", "sub", "subu", "and", "or", "nor", "slt",
        "sltu", "sll", "srl", "jr"
    };
    int functDecOps [] =
    {
        32,33,34,35,36,37,39,42,43,0,2,8
    };
    // Used for iteration
    int i;
    for(i = 0; i<12; i++)
    {
        if(strcmp(functOps[i],instName)== 0)
        {
            functDec = &functDecOps[i];
            break;
        }
    }

    // R-Format instruction for jr
    if (strcmp(instName, jr) == 0)
    {
        // jr intruction should only have 1 token
        if( ! getNTokens(restOfInstruction, 1, arguments))
        {
            printError("\nError on line %d: %s\n", lineNum, arguments[0]);
            return;
        }
        int rs = getRegNum(arguments[0]);
        if(rs == -1)
        {
            printError("\nError: Invalid register, at line %d: %s\n", lineNum, arguments[0]);
            return;
        }
        // registers rt and rd are 0 for jr instruction
        char * rt = "00000";
        char * rd = "00000";
        char * shamt = "00000";
        // print the binary represented instruction to stdout
        printf("\n%s",opcode);
        printBinary(rs,4);
        printf("%s%s%s",rt,rd,shamt);
        printBinary(*functDec,5);
        printf("\n");
    }
    else
    {
        // All other instruction types will have 3 tokens
        if ( ! getNTokens(restOfInstruction, 3, arguments) )
        {
            /* When getNTokens encounters an error, it puts a pointer
            * to the error message in arguments[0]. */
            printError("\nError on line %d: %s\n", lineNum, arguments[0]);
            return;
        }
        // R-Format instruction for sll or srl
        if(strcmp(instName, sll) == 0 || strcmp(instName, srl) == 0)
        {
            // rs = 0 for both sll and srl
            char * rs = "00000";
            // Fetch register numbers for rt and rd
            int rt = getRegNum(arguments[1]);
            int rd = getRegNum(arguments[0]);
            // Check for valid registers
            if(rt == -1 || rd == -1)
            {
                printError("\nError, Invalid register at line %d\n", lineNum);
                return;
            }

            int shamt = atoi(arguments[2]);     // Convert char to int
            // shamt has to be in the range 0<= shamt < 32
            if(shamt < 0 || shamt > 31)
            {
                printError("\nError: Shamt out of range at Line %d\n", lineNum);
                return;
            }
            // Print the binary represented instruction to stdout
            printf("\n%s%s", opcode,rs);
            printBinary(rt,4);
            printBinary(rd,4);
            printBinary(shamt,4);
            printBinary(*functDec,5);
            printf("\n");
        }
        else    // All other R-Format Instructions
        {
            // shamt = 0 for all other instructions
            char * shamt = "00000";
            // Fetch register numbers
            int rs = getRegNum(arguments[1]);
            int rt = getRegNum(arguments[2]);
            int rd = getRegNum(arguments[0]);
            // verify registers
            if(rs == -1 || rt == -1 || rd == -1)
            {
                printError("\nError: Invalid register at line %d\n", lineNum);
                return;
            }
            // print the binary represented instruction to stdout
            printf("\n%s", opcode);
            printBinary(rs,4);
            printBinary(rt,4);
            printBinary(rd,4);
            printf("%s",shamt);
            printBinary(*functDec,5);
            printf("\n");
        }
    }
    return;
}
