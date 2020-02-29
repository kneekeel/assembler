/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady 
 * Modified by: Nikhil Sodemba
 *
 * Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  4/19/2013    Modernized call to fprintf for errors.
 *   Modified:  5/25/2015    Updated to use printError function.
 *   Modified:  1/28/2020    Programming Project: Label Table
 *   Modified:  1/25/2020    Programming Project: Label Table
 * 
 * Detailed modifications for modication date - 1/25/2020:
 * 
 * Completed functions tableInit, findLabel, addLabel and printLabels, 
 * following the correct documentation and error handling with the 
 * rubric standard for this programming project - Label Table. 
 *
*/

#include "assembler.h"

// internal global variables (global to this file only)
static const char * ERROR0 = "Error: label table is a NULL pointer.\n";
static const char * ERROR1 = "Error: a duplicate label was found.\n";
static const char * ERROR2 = "Error: cannot allocate space in memory.\n";

// internal function (visible to this file only)
static int verifyTableExists(LabelTable * table);

void tableInit (LabelTable * table)
  /* Postcondition: table is initialized to indicate that there
   *       are no label entries in it.
   */
{
    /* verify that table exists */
    if ( ! verifyTableExists (table) )
    {
        return;           /* fatal error: table doesn't exist */
    }else
    {
        table->nbrLabels = 0;
        table->capacity = 0;
        table->entries = NULL;
    }
}

void printLabels (LabelTable * table)
  /* Postcondition: all the labels in the table, with their
   *      associated addresses, have been printed to the standard
   *      output.
   */
{
    int i;

    /* verify that table exists */
    if ( ! verifyTableExists (table) )
        return;           /* fatal error: table doesn't exist */

    if (table->nbrLabels == 0)
    {
        printf("%s",ERROR0);
        return;
    }

    (void) printf ("There are %d labels in the table:\n",
                            table->nbrLabels);
    int num_labels = table->nbrLabels;
    printf("\nLabel: \t\t\t Address: \n");
    /* Will print all the corresponding labels with their addresses to the standard output. */
    for (i = 0; i < num_labels; i++)
    {
        printf("%s \t\t\t %d\n", table->entries[i].label, table->entries[i].address);
    }
}

int findLabel (LabelTable * table, char * label)
  /* Returns the address associated with the label; -1 if label is
   *      not in the table or table doesn't exist
   */
{
    if ( ! verifyTableExists(table))
    {
        printf("\nInvalid table does not exist..\n");
        return -1;
    }
    int num_labels = table->nbrLabels;
    int i;
    for (i = 0; i < num_labels; i++)
    {
        if (strcmp (table->entries[i].label, label) == SAME)
        {
            return table->entries[i].address;
        }
    }

    /* Will return -1 if label does not exist in table */
    return -1;    
}


int addLabel (LabelTable * table, char * label, int progCounter)
  /* Postcondition: if label was already in table, the table is 
   *      unchanged; otherwise a new entry has been added to the 
   *      table with the specified label name and instruction address
   *      (program counter) and the table has been resized if necessary.
   * Returns 1 if no fatal errors occurred; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
    char * labelDuplicate;
    int currentCapacity;
    int newSize;

    /* verify that table exists */
    if ( ! verifyTableExists (table) )
    {
        return 0;           /* fatal error: table doesn't exist */
    }

    /* Was the label already in the table? */
    if (findLabel(table, label) != -1)
    {
        /* This is an error (ERROR1), but not a fatal one.
            * Report error; don't add the label to the table again. 
            */
        printf("%s",ERROR1);
        return 1;
    }

    /* Create a dynamically allocated version of label that will persist. */
    /*   NOTE: on some machines you may need to make this _strdup !  */
    if ((labelDuplicate = strdup (label)) == NULL)
    {
        printError ("%s", ERROR2);
        return 0;           /* fatal error: couldn't allocate memory */
    }

    /* Resize the table if necessary. */
    if ( table->nbrLabels >= table->capacity )
    {
        currentCapacity = table->capacity;
        if (currentCapacity <= 0)
        {
            newSize = 5;
        }
        else
        {
            newSize = currentCapacity*2;
        }
        int resize = tableResize(table, newSize);
        if (resize == 0)
        {
            printError("\t%s\t",ERROR2);
            return 0;
        }

    }

    /* Add the label */
    LabelEntry new_entry;
    new_entry.label = labelDuplicate;
    new_entry.address = progCounter;
    table->entries[table->nbrLabels] = new_entry;
    table->nbrLabels = table->nbrLabels + 1;
    return 1;               /* everything worked great! */
    
}

int tableResize (LabelTable * table, int newSize)
  /* Postcondition: table now has the capacity to hold newSize
   *      label entries.  If the new size is smaller than the
   *      old size, the table is truncated after the first
   *      newSize entries.
   * Returns 1 if everything went OK; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        LabelEntry * newEntryList;
        int          smaller;

        /* verify that table exists */
        if ( ! verifyTableExists (table) )
            return 0;           /* fatal error: table doesn't exist */

        /* create a new internal table of the specified size */
        if ((newEntryList = malloc (newSize * sizeof(LabelEntry))) == NULL)
        {
            printError ("%s", ERROR2);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        if ( table->entries )           /* if there were entries */
        {
            /* move contents of internal table to new internal table */
            smaller = table->nbrLabels < newSize ? table->nbrLabels : newSize;
            (void) memcpy (newEntryList, table->entries,
                           smaller * sizeof(LabelEntry));

            /* free the space taken up by the old internal table */
            free (table->entries);
            table->nbrLabels = smaller;
        }

        table->entries = newEntryList;
        table->capacity = newSize;
        return 1;
}

static int verifyTableExists(LabelTable * table)
 /* Returns true (1) if table exists (pointer is non-null); prints an error
  * and returns false (0) otherwise.
  */
{
        /* verify that table exists */
        if ( ! table )
        {
            printError ("%s", ERROR0);
            return 0;
        }

        return 1;
}
