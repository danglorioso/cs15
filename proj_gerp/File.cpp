/*
 *  File.cpp
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 11/30/23
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Implementation of the File class that stores the name of the file
 *           and the path to the file as well as a vector of string
 *           representing the lines of the file. Functions include getters and
 *           setters for the file name and path, a function to add a line to
 *           the vector of lines, a function to print the lines, and a
 *           function to return the number of lines in the file.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "File.h"

using namespace ::std;

/* File()
 *   Purpose: Constructor for the File class that sets the file and path to
 *            empty strings
 * Arguments: none
 *   Returns: none
 */
File::File()
{
    file = "";
    path = "";
}

/* File(string fileName, string filePath)
 *   Purpose: Constructor for the File class that sets the file and path to
 *            the given strings
 * Arguments: string fileName - the name of the file
 *            string filePath - the path to the file
 *   Returns: none
 */
File::File(string fileName, string filePath)
{
    file = fileName;
    path = filePath;
}

/* getFileName()
 *   Purpose: Returns the name of the file
 * Arguments: none
 *   Returns: string - the name of the file
 */
string File::getFileName()
{
    return file;
}

/* getPath()
 *   Purpose: Returns the path to the file
 * Arguments: none
 *   Returns: string - the path to the file
 */
string File::getPath()
{
    return path;
}

/* getLine(int lineNum)
 *   Purpose: Returns the line at the given index
 * Arguments: int lineNum - the index of the line to return
 *   Returns: string - the line at the given index
 */
string File::getLine(int lineNum)
{
    return lines[lineNum];
}

/* getNumLines()
 *   Purpose: Returns the number of lines in the file
 * Arguments: none
 *   Returns: int - the number of lines in the file
 */
int File::getNumLines()
{
    return lines.size();
}

/* setFileName(string fileName)
 *   Purpose: Sets the name of the file to the given string
 * Arguments: string fileName - the name of the file
 *   Returns: none
 */
void File::setFileName(string fileName)
{
    file = fileName;
}

/* setPath(string filePath)
 *   Purpose: Sets the path to the file to the given string
 * Arguments: string filePath - the path to the file
 *   Returns: none
 */
void File::setPath(string filePath)
{
    path = filePath;
}

/* addLine(string line)
 *   Purpose: Adds the given string to the vector of lines
 * Arguments: string line - the line to add to the vector
 *   Returns: none
 */
void File::addLine(string line)
{
    lines.push_back(line);
}

/* printLines()
 *   Purpose: Prints the lines of the file. This function is used for testing.
 * Arguments: none
 *   Returns: none
 */
void File::printLines()
{
    int numLines = lines.size();
    for (int i = 0; i < numLines; i++)
    {
        cout << lines[i] << endl;
    }
}
