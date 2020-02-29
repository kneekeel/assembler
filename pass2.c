/**
 * LabelTable pass2 (FILE * fp, LabelTable table)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @param  table  an existing Label Table
 *      @return a newly-created table containing labels found in the
 *              input file, each with the address of the instruction
 *              containing it (assuming the first line of input
 *              corresponds to address 0)
 *
 * The pass2 function will read each line of instruction, determine its format
 * type and then print either its corresponding machine code or error, using one
 * of the 3 assembler functions for: R-Format, I-Format, or J-Format.
 * 
 * The processFormat(...) function will determine which format the instruction
 * belongs to and pass the format type back to processInstruction(...) which
 * will pass the correct parameters into one of the assembler format type
 * functions/will return an error if instruction doesn't belong to any 
 * format type.
 *
 * Author: Nikhil Sodemba
 * Date:   Feb, 20th, 2020
 *
 */

#include "assembler.h"

/* Declaration of helper function - processInstruction, defined later in this file. */
void processInstruction(char * instName, char * restOfInstruction,
                        int lineNum, LabelTable table);

/* Declaration of helper function - processFormat, defined later in thie file */
int processFormat(char * instName);

/**
 * Main for the pass2 function.
 * 
 * Takes in the file pointer and the lable table (generated from pass1) as arguments
 * in the parameters.
 */
void pass2 (FILE * fp, LabelTable table)
  /* returns a copy of the label table that was constructed */
{
    int    lineNum;                /* line number */
    int    PC;                     /* program counter */
    char * tokBegin, * tokEnd;     /* used to step thru inst */
    char   inst[BUFSIZ];           /* will hold instruction; BUFSIZ
                                      is max size of I/O buffer
                                      (defined in stdio.h) */
    char * instrName;              /* instruction name (e.g., "add") */

    /* Continuously read next line of input until EOF is encountered.
     */
    for (lineNum = 1, PC = 0; fgets (inst, BUFSIZ, fp); lineNum++, PC += 4)
    {
        /* If the line starts with a comment, move on to next line.
         * If there's a comment later in the line, strip it off
         *  (replace the '#' with a null byte).
         */
        if ( *inst == '#' ) continue;
        (void) strtok (inst, "#");

        /* Read the first token, skipping any leading whitespace. */
        tokBegin = inst;
        getToken (&tokBegin, &tokEnd);
            /* tokBegin now points to 1st non-whitespace character
             * in the token and tokEnd points to 1st punctuation mark
             * or whitespace after the end of the token.
             */

        /* Skip label, if any */
        if ( *(tokEnd) == ':' )
        {
            /* Line has a label!  Get new token! */
            tokBegin = tokEnd + 1;
            getToken (&tokBegin, &tokEnd);
        }

        /* If empty line or line containing only a label, get next line */
        if ( *tokBegin == '\0' )
            continue;

        /* We have a valid token; turn it into a string and set
         * tokBegin to point to the character after the end.
         */
        *tokEnd = '\0';
        instrName = tokBegin;
        tokBegin = tokEnd + 1;

        // print current instruction
        printDebug("\nLine #%d: %s, %s\n", lineNum, instrName, tokBegin);

        processInstruction(instrName, tokBegin, lineNum, table);
    }

    return;
}

/**
 * This function will process the given instruction and determine 
 * which format type the instruction belongs to (using processFormat(...)).
 * Once the function determines which format type the instruction belongs to,
 * it will call the appropiate function to process the instruction into 
 * its binary representation (Machine Code).
 * 
 * The function takes 4 arguments: instName, restOfInstruction, lineNum, and table.
 * 
 * Will print error to stderr, if the given instruction doesn't belong to any
 * legitimate format type.
 * 
 */
void processInstruction(char * instName, char * restOfInstruction,
                        int lineNum, LabelTable table)
{
    // Call processFormat function to identify format type.
    int formatResult = processFormat(instName);
    if(formatResult == 0)
    {
        printDebug("\tThe instruction is of R-Format.\n");
        assemblerR(instName, restOfInstruction, lineNum);
    }
    else if(formatResult == 1)
    {
        printDebug("\tThe instruction is of I-Format.\n");
        assemblerI(instName, restOfInstruction, lineNum, table);
    }
    else if(formatResult == 2)
    {
        printDebug("\tThe instruction is of J-Format.\n");
        assemblerJ(instName, restOfInstruction, lineNum, table);
    }
    else if(formatResult == -1)
    {
        printError("\nError on line: %d. Invalid instruction: '%s'.\n", lineNum, instName);
    }
    return;
}

/**
 * This function will return the format type for the given instruction,
 * can be one of the following: R-Format, I-Format, J-Format, and invalid Format.
 * 
 * The function takes in one argument as a parameter, the given instruction 
 * name for the given instruction line. I.e. instName = "add"
 * 
 * Returns 0 for R-Format, 1 for I-Format, 2 for J-Format 
 * and -1 for an invalid instruction name, not beloning to any of the 3
 * valid format types. 
 * 
 */
int processFormat(char * instName)
{
    // Local Variables for the posible format types
    // R-Format options array
    char * rFormat [] = 
    {
        "add", "addu", "sub", "subu", "and", "or", "nor", "slt",
        "sltu", "sll", "srl", "jr"
    };
    // I-Format options array
    char * iFormat [] = 
    {
        "beq", "bne", "addi", "addiu", "andi", "ori", "slti", "sltiu",
        "lui", "lw", "sw"
    };
    // J-Format options array
    char * jFormat [] =
    {
        "j", "jal"
    };
    int i; // constant to loop through the arrays

    // Loop through the arrays
    for(i = 0; i < 12; i++)
    {
        // R-Format array
        if(strcmp(rFormat[i], instName) == 0)
        {
            return 0;
        }
        // I-Format array
        if(i < 11)
        {
            if(strcmp(iFormat[i], instName) == 0)
            {
                return 1;
            }
        }
        // J-Format array
        if(i < 2)
        {
            if(strcmp(jFormat[i], instName) == 0)
            {
                return 2;
            }
        }
    }
    // Invalid-Instruction name, proper error handling will be dealt 
    // in processInstruction function.
    return -1;
}
