/**
 * This is the Assembler programs main file.
 * 
 * The purpose of this program is to process assembly language to 
 * machine language. It is a compiler (assembler).
 * 
 * IMPORTANT: Please avoid using standard input to pass instructions to this 
 * function. Pass in a file that contains assembly language instructions.
 * 
 * The main(...) function processes instructions using the two pass 
 * functions: pass1 and pass2. The pass1 function will read the file/stdin
 * and put associated labels into a label table, thus returning the label table.
 * If no labels are present the function will return an empty label table. The 
 * pass2 function will read the same file and take each instruction of that file, 
 * format it into its specific type and print either the machine code for the given
 * instruction or print the corresponding error. 
 * 
 * You can find a detailed description of the functions used in this file in their
 * corresponding files.
 * 
 * Debugging can turned on/off by passing either 0 or 1, in standard input. Turn debugging
 * off if you want to see only the machine code output/potential errors.
 * 
 * Author: Nikhil Sodemba
 * Date Created: Feb, 20th, 2020
 * 
 */

#include "assembler.h"

/**
 *  Main for the assembler program, used to process Assembly Language into its
 * corresponding machine language. 
 * 
 * The function takes two parameters: argc and argv. 
 * 
 * The function will use pass1 and pass2 to process the instructions properly,
 * it also uses a handful of external functions in order to process
 * each instruction. The documentation found in the pass2 file will explain
 * more in depth about how the instructions are processed.
 *  
 */
int main (int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */
    LabelTable table;

    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    // Call pass1 to generate the label table, if labels exists in the file/stdin
    table = pass1(fptr);    // Returns an empty label table if no labels exist

    /* Print the label table if debugging is turned on. */
    if ( debug_is_on() )
    {
        printLabels (&table);
    }

    // Rewind the file pointer to the beginning of the file, before passing it into pass2
    rewind(fptr);
    pass2(fptr,table);

    (void) fclose(fptr);
    return 0;
}
