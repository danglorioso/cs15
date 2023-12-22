/*
 *  parser.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/15/2023
 *
 *  CS 15 PROJECT 2: CalcYouLater
 *
 *  PURPOSE: Implementation of the parseRString function that will parse an
 *           istream for a string in RPN format.
 *
 */

#include <iostream>
#include <istream>
#include "parser.h"

using namespace std;

/* parseRSTring(istream &input)
 *    Purpose: Takes a reference to an instream as a parameter to continue 
 *             reading the input stream until all curly braces have been 
 *             matched or the end of the file is reached. Parses the input
 *             stream and returns a string containing the contents of the
 *             input stream up until the final matching curly brace.
 * Parameters: istream &input - input stream
 *    Returns: A string containing the contents of the input stream surrounded
 *             by curly braces.
 */
std::string parseRString(std::istream &input) {
    string rstring = "{";
    int braceCounter = 1;
    bool run = true;
    string temp_string;
    string in;

    // read in the input until end of input stream or final matching brace
    while (input >> in and run) {
        temp_string += " ";
        temp_string += in;
        if (in == "{") {
            braceCounter++;
        } else if (in == "}") {
            braceCounter--;
            if (braceCounter == 0) {
                run = false;
            }
        }
    }

    // if the braces are unbalanced, thrown an exception
    if (not(braceCounter == 0)) {
        throw std::runtime_error("unbalanced braces");
    }

    rstring = "{" + temp_string;
    return rstring;
}
