 /*
 * Test Driver to test the functions to access and manipulate a label table.
 * 
 * It includes the following tests for a static label table:
 * 
 *      All test cases test printLabels and findLabels (through testSearch)
 * 
 *      Test 1). Testing with initial testTable1 (with one entry)
 *      Standard Output should print the entries in the label table and should 
 *      print the address of the searched "label", if the label exists in the 
 *      label table.
 * 
 *      Test 2). Testing with testTable1 -> no lables (empty table)
 *      Standard Output should print allocated error - ERROR0.
 * 
 *      Test 3). Testing testTable1 with the addition of four more entries
 *      Standard Output should print all labels with their corresponding addresses and
 *      should print the address of the search "label", if the label exists in 
 *      the label table.
 * 
 * It includes the following tets for a dynamic label table:
 *      Test 1). Testing printLabels and findLabel (through testSearch) with an initial 
 *      dynamic label table (after initialization). 
 *      Standard Output should print an error for both functions, yet be able to identify 
 *      that the dynamic label table exists. 
 * 
 *      Test 2). Testing the addLabel and tableResize functions. 
 *      Using printLabels to see if addition + resize of the table was sucessful. 
 *      Standard Output should print the newly added label.
 * 
 *      Test 3). Testing the addLabel, tableResize, findLabel and printLabel functions.
 *      Standard Output should print all the newly added labels and print the searched 
 *      labels' address if it exists in the label table. 
 * 
 *      Test 4). Testing the addLabel function with a label which already exists in the 
 *      label table. 
 *      Standard Output should print ERROR1 - duplicate label. 
 *              
 *
 * Author:  Nikhil Sodemba
 *
 * Creation Date: January, 25th, 2020
 * 
 */

#include "assembler.h"

static void testSearch(LabelTable * table, char * searchLabel);

int main(int argc, char * argv[])
{
    /* Process command-line argument (if provided) for
     *    debugging indicator (1 = on; 0 = off).
     */
    (void) process_arguments(argc, argv);

    /* Can turn debugging on or off here (debug_on() or debug_off())
     * if not specified on the command line.
     */

    /* Create 2 tables, one static and one dynamic, for testing purposes */
    printf("\n===== Testing with static table =====\n");
    LabelEntry staticEntries[5];
    staticEntries[0].label = "Label1";
    staticEntries[0].address = 1000;
    LabelTable testTable1;      /* will be a table with static entries */
    LabelTable testTable2;      /* will be a table with dynamic entries */

    /* Initialize testTable1 with a static array of a given size. */
    testTable1.capacity = 5;
    testTable1.nbrLabels = 1;
    testTable1.entries = staticEntries;

    /* Test printLabels and findLabel with static testTable1.
     *      DO NOT TEST tableInit, addLabel, or tableResize WITH STATIC TABLE!
     * Use testSearch to test findLabel, for example:
     *      testSearch(&testTable1, "Label1");
     * Examples of basic boundary testing:
     *     Set nbrLabels to 0 and test on empty table.
     *     Put four more entries in staticEntries, set nbrLabels to 5,
     *     and test.  (Don't go beyond the max unless you want to crash the
     *     program.)
     */

    /* Test for printLabels */
    printf("\nTesting printLabels..\n");
    printLabels(&testTable1);

    /* Test for findLabels using testSearch */
    printf("\nTesting findLabels..\n");
    testSearch(&testTable1, "Label1");


    /* The following segment of code will test the basic boundary testings. */
    printf("\nTesting with nbrLabels = 0 and empty table..\n");
    testTable1.nbrLabels = 0;
    printLabels(&testTable1);
    testSearch(&testTable1, "Label1");

    printf("\nTesting with four more entries..\n");
    staticEntries[1].label = "Label2";
    staticEntries[1].address = 1000;
    staticEntries[2].label = "Label3";
    staticEntries[2].address = 1004;
    staticEntries[3].label = "Label4";
    staticEntries[3].address = 1008;
    staticEntries[4].label = "Label5";
    staticEntries[4].address = 1010;
    testTable1.nbrLabels = 5;
    printLabels(&testTable1);
    testSearch(&testTable1, "Label4");


    printf("\n===== Testing with dynamic table =====\n");

    /* Initialize testTable2 as a dynamic (changeable size) table. */
    tableInit(&testTable2);

    /* All test cases here on will be subjected to dynamic label table - testTable2 */

    /* Test printLabels, findLabel, and addLabel.
     * Include appropriate boundary testing.
     */

    /* Test for printLabels, after initialization of testTable2, currently it is an empty table. */
    printf("\nTesting for printLabels and findLabel, after initializing of dynamic label table.\n");
    printLabels(&testTable2);
    testSearch(&testTable2, "Invalid Search");

    /* Test for addLabel, will be testing the tableResize function as the current label table 
     * has a capacity which is lower than the nbrLabels - 0. The initiated capacity value is 
     * of a negative value, thus, the addLabel function will resize the label table in order to 
     * add the respective label + address, if the logistics are satisfied.
    */
    printf("\nTesting addLabel and in turn tableResize..\n");
    addLabel(&testTable2, "Main", 1000);
    printLabels(&testTable2);

    /* Sucessfully added label and address into the label table, the labels and address have been 
     * printed out to standard output. Will add five more labels and searching for a specific label.
     * The current capacity of the table is 5 (due to the logic of my addLabel and tableResize functions).
     * After the addition of these 5 labels, the new table capacity will be 10, will be printing the 
     * capacity of the label table to standard output, should be equal to 10.
     */
    printf("\nTesting addition of multiple labels + addresses, and then searching for a specific address..\n");
    addLabel(&testTable2, "LP", 1415);
    addLabel(&testTable2, "Add", 1418);
    addLabel(&testTable2, "JW", 2000);
    addLabel(&testTable2, "TQ", 2004);
    addLabel(&testTable2, "OP", 2028);
    printLabels(&testTable2);
    testSearch(&testTable2, "JW");
    printf("\nThe capacity of the label table after addition of labels is: %d\n", testTable2.capacity);

    /* Testing for trying to add a label which already exists in the given table. 
     * Should see an ERROR1 when trying to add an existing label to the table.
    */
    printf("\nTesting addLabel function, trying to add a label with already exists in label table..\n");
    addLabel(&testTable2, "TQ", 2008);

}

/*
 * testSearch tests the findLabel function, printing out the label being
 * searched for and either the address where it was found or, if it was
 * not found, an address of -1 and a message that the label was not in
 * the table.  
 *  @param  table        a pointer to the table through which to search
 *  @param  searchLabel  the label to search for
 */
static void testSearch(LabelTable * table, char * searchLabel)
{
    int address;
    
    printf("\nLooking for %s...\n", searchLabel);
    
    if(table->nbrLabels == 0)
    {
        printf("\nError: label table is a NULL pointer, invalid search..\n");
    }else
    {
        address = findLabel(table, searchLabel);

        if ( address == -1 )
        {
            printf("\tThe label you're looking for does not exist.\n");
        }else
        {
            printf("\tThe address is %d.\n", address);
        }   
    }
}
