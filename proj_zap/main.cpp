/*
 *  main.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 11/07/2023
 *
 *  CS 15 PROJECT 3: zap
 *
 *  PURPOSE: Main function for the zap program. This file processes the command
 *           line arguments, ensures they are valid, and calls the 
 *           appropriate functions in the HuffmanCoder class. This function is
 *           the main driver for the zap program.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanCoder.h"
#include "HuffmanTreeNode.h"

using namespace std;

// Function declarations
void abort_prog();

int main(int argc, char *argv[]) {
    // check for correct number of arguments
    if (not(argc == 4)) {
        abort_prog();
    }

    // call appropriate zap/unzap function from HuffmanCoder class
    HuffmanCoder coder;
    if (string(argv[1]) == "zap") {
        // call the encoder function in HuffmanCoder class
        coder.encoder(string(argv[2]), string(argv[3])); 
    } else if (string(argv[1]) == "unzap") {
        // call the decoder function in HuffmanCoder class
        coder.decoder(string(argv[2]), string(argv[3]));
    } else {
        abort_prog();
    }

    return 0;
}

/*abort_prog()
 *    Purpose: Prints the usage message and exits the program with EXIT_FAILURE
 * Parameters: None
 *     Return: None
 */
void abort_prog() {
    std::cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
    exit(EXIT_FAILURE);
}
