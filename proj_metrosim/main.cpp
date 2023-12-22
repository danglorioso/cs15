/*
 *  main.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Main function for the MetroSim program. The main driver of the 
 *           program that simulates a train system that has a train that moves 
 *           between stations and passengers that board and exit the train.
 *
 */
 
#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

void abort(string error_message);
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name);

int main(int argc, char *argv[])
{
    //Enforce correct usage (number of parameters in command line)
    if (not ((argc == 3) or (argc == 4))) {
        abort("Usage: ./MetroSim stationsFile outputFile [commandsFile]");
    }
    // Create file streams
    ifstream instream;
    ofstream outstream;
    // Check instream and the file name from command line.
    open_or_die(instream, argv[1]);
    open_or_die(outstream, argv[2]);
    if (argc == 4) {
        ifstream commandstream;
        open_or_die(commandstream, argv[3]);
    }
    // Create a MetroSim object and input stations file from argc[1]
    MetroSim greenline;
    greenline.initalize(instream);
    if (argc == 4) {
        // Call the function to start the query loop
        greenline.prompt_and_execute_FILE(outstream, commandstream);

        // Close the file streams
        commandstream.close();
    } else {
        // Call the function to start the query loop
        greenline.prompt_and_execute_CIN(outstream);
    }
    // Close the file streams
    instream.close();
    outstream.close();
    return 0;
}

/* abort(string error_message)
 *    Purpose: Print the given error message to cerr and exit with 
 *             EXIT_FAILURE.
 * Parameters: string error_message - the error message to print
 *    Returns: None
 */
void abort(string error_message)
{
    std::cerr << error_message << endl;
    exit(EXIT_FAILURE);
}

/* open_or_die(streamtype &stream, string file_name)
 *    Purpose: Check whether a file can be opened successfully or not. If not, 
 *          print an error message and exit with EXIT_FAILURE.
 * Parameters: streamtype &stream - a reference to a file stream
 *            string file_name - the name of the file to open
 *    Returns: None
 */
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not (stream.is_open())) {
        abort("Error: could not open file " + file_name);
    }
}
