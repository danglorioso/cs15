/*
 *  main.cpp
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 12/04/23
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Main function for the Gerp program. This program is a search
 *           tool that allows the user to search for words in a directory
 *           of files. The user can search for a word, either case sensitive
 *           or case insensitive, and the program will return the line number
 *           and file name where the word was found.
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Gerp.h"

using namespace ::std;

void usage_error();

/* int main(int argc, char *argv[])
 *   Purpose: initialize gerp, index the files, and call the query loop
 *             to run the program
 * Arguments: argc - number of arguments
 *            argv - array of arguments (directory and output file)
 *   Returns: none
 */
int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 3)
        usage_error();

    string inputDir = argv[1];
    string outputDir = argv[2];

    // Create a Gerp object
    Gerp gerp;

    // Index the given directory
    gerp.Index(inputDir);

    // Run the query loop and execute commands
    gerp.Query(outputDir);

    return 0;
}

/* void usage_error()
 *   Purpose: Print an error message and exit the program
 * Arguments: none
 *   Returns: none
 */
void usage_error()
{
    cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
    exit(EXIT_FAILURE);
}
