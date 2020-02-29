/**
 * This is the assembler J-Format file, which is used 
 * to process Assembly language instructions into machine
 * language.
 * 
 * Author: Nikhil Sodemba
 * Date Created: Feb,20th,2020
 */

#include "assembler.h"
#include "assemblerUtil.h"

/**
 * This function will process J-format instructions into 
 * machine language.
 * 
 * It takes four parameters: instName, restOfInstruction, lineNume, and table.
 * 
 * Will print instruction in machine language to stdout
 * 
 * Will handle errors accordingly and print them to stderr
 * 
 * Pre-condition:
 *      - The instruction should contain the label of the address,
 *          i.e. arugments[0] == "loop"
 * 
 */
void assemblerJ(char * instName, char * restOfInstruction,int lineNum, LabelTable table)
{
    char * arguments[1];

    // local variable opcode
    int opcode;
    // variable to compare opcode type
    char * j="j";

    if(strcmp(instName,j)==0)
    {
        opcode = 2;
    }
    else    // otherwise, instName == jal
    {
        opcode = 3;
    }
    // J-Format instructions should have 1 token
    if( ! getNTokens(restOfInstruction, 1, arguments))
    {
        printError("\nError on line %d: %s\n", lineNum, arguments[0]);
        return;
    }

    // Get address from label table
    int address = findLabel(&table, arguments[0]);
    // Verify if address exists
    if(address == -1)
    {
        printError("\nError: Invalid label not contained in label table, at line %d\n",lineNum);
        return;
    }
    // address = addrFromLabelTable/4
    address = address/4;
    // verify address bounds: 0<=address<67108864
    if(address < 0 || address >67108865)
    {
        printError("\nError: Address is out of bounds at line %d\n",lineNum);
        return;
    }
    // print binary representation of instruction to stdout
    printf("\n");
    printBinary(opcode,5);
    printBinary(address,25);
    printf("\n");

    return;
}
