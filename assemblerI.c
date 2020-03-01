/**
 * This is the assembler I-Format file, which is used 
 * to process I-Format assembly language instructions 
 * into machine code.
 * 
 * Author: Nikhil Sodemba
 * Date Created: Feb, 20th, 2020
 * 
 */

#include "assembler.h"
#include "assemblerUtil.h"


/**
 * This function is used to process I-Format instructions into 
 * machine language. 
 * 
 * It takes four parameters: instName, restOfInstruction, lineNume, and table.
 * 
 * Will print out the instruction (machine language) to stdout
 * 
 * Will handle errors accordingly and print them to stderr
 * 
 * Pre-condition: 
 *      - For BNE and BEQ instructions, the instruction should contain the label 
 *          name in order (i.e. agrugments[2] == "loop")
 * 
 */
void assemblerI(char * instName, char * restOfInstruction,int lineNum, LabelTable table)
{
    char * arguments[3];    /* registers or values after instruction name */

    // lineNum subtracted by 1, because we start from line 1, therefore PC != 0 at line 1
    // refer to pass2, where in the first loop, the lineNum is initiated to 1
    int PC = (lineNum-1) * 4;

    // variable to store the opcode integer
    int * opcode = 0;
    int i;      // iterator value

    // variables to compare later in function
    char * bne="bne", *beq = "beq", *lui="lui", *lw="lw", *sw="sw";

    // Arrays to hold opcode operations
    char * opcodeOps [] = 
    {
        "beq", "bne", "addi", "addiu", "andi", "ori", "slti", "sltiu",
        "lui", "lw", "sw"
    };
    int opcodeIntOps [] = 
    {
        4,5,8,9,12,13,10,11,15,35,43
    };

    // determine current opcode function
    for(i =0; i<11; i++)
    {
        if(strcmp(instName, opcodeOps[i])==0)
        {
            opcode = &opcodeIntOps[i];
            break;
        }
    }

    // I-Format for lui instruction
    if(strcmp(instName, lui) == 0)
    {
        // lui instruction should have 2 tokens
        if( ! getNTokens(restOfInstruction, 2, arguments))
        {
            printError("\nError on line %d: %s\n", lineNum, arguments[0]);
            return;
        }

        // rs = 0 for lui instruction
        char * rs = "00000";
        // fetch register for rt
        int rt = getRegNum(arguments[0]);
        // check if register is valid
        if(rt == -1)
        {
            printError("\nError: Invalid Register at line %d\n",lineNum);
            return;
        }
        int immediate = atoi(arguments[1]);     // convert immediate from char to int
        // check - immediate should be in range 0 <= immediate < 65536
        if(immediate < 0 || immediate > 65535)
        {
            printError("\nError: Immediate value is out of range at line %d\n", lineNum);
            return;
        }
        // print binary represented instruction to stdout
        printf("\n");
        printBinary(*opcode, 5);
        printf("%s",rs);
        printBinary(rt,4);
        printBinary(immediate,15);
        printf("\n");
    }
    else
    {
        // All other I-Format instructions should have 3 tokens
        if( ! getNTokens(restOfInstruction, 3, arguments))
        {
            printError("\nError on line %d: %s\n", lineNum, arguments[0]);
            return;
        }
        // I-Format instruction for bne and beq
        if(strcmp(instName,bne)==0 || strcmp(instName,beq)==0)
        {
            // Get address of label from label table
            int address = findLabel(&table, arguments[2]);
            // Verify if address exists
            if(address == -1)
            {
                printError("\nError: Invalid label not contained in label table, at line %d\n",lineNum);
                return;
            }
            // immediate = offset = (addrFromLabelTable - PC) / 4
            int immediate = (address - PC)/4;
            // verify bounds for immediate 
            if(immediate < 0 || immediate > 65535)
            {
                printError("\nError: Immediate value is out of range at line %d\n", lineNum);
                return;
            }
            // fetch registers for rs and rt
            int rs = getRegNum(arguments[0]);
            int rt = getRegNum(arguments[1]);
            // verify registers
            if(rs == -1 || rt == -1)
            {
                printError("\nError: Invalid Register at line %d\n",lineNum);
                return;
            }
            // print binary represented instruction to stdout
            printf("\n");
            printBinary(*opcode,5);
            printBinary(rs,4);
            printBinary(rt,4);
            printBinary(immediate,15);
            printf("\n");
        }
        // I-Format for lw and sw instructions
        else if(strcmp(instName,lw)==0 || strcmp(instName,sw)==0)
        {
            // fetch registers for rs and rt
            int rs = getRegNum(arguments[2]);
            int rt = getRegNum(arguments[0]);
            if(rs == -1 || rt == -1)
            {
                printError("\nError: Invalid Register at line %d\n",lineNum);
                return;
            }
            int immediate = atoi(arguments[1]);
            if(immediate < 0 || immediate > 65535)
            {
                printError("\nError: Immediate value is out of range at line %d\n", lineNum);
                return;
            }
            // print instruction (machine code) to stdout
            printf("\n");
            printBinary(*opcode,5);
            printBinary(rs,4);
            printBinary(rt,4);
            printBinary(immediate,15);
            printf("\n");
        }
        else    // all other I-Format instructions
        {
            int rs = getRegNum(arguments[1]);
            int rt = getRegNum(arguments[0]);
            if(rs == -1 || rt == -1)
            {
                printError("\nError: Invalid Register at line %d\n",lineNum);
                return;
            }
            int immediate = atoi(arguments[2]);
            if(immediate < 0 || immediate > 65535)
            {
                printError("\nError: Immediate value is out of range at line %d\n", lineNum);
                return;
            }
            // print instruction (machine code) to stdout
            printf("\n");
            printBinary(*opcode,5);
            printBinary(rs,4);
            printBinary(rt,4);
            printBinary(immediate,15);
            printf("\n");
        }
    }
    
    return;
}
