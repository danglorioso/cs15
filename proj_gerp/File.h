/*
 *  File.h
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 12/04/23
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Implementation of the File class which represents a file in the
 *           FSTree. Each file contains a vector of strings which represent the
 *           lines of the file. The File class contains getters and setters for
 *           the file name, path, and lines. It also contains a function to add
 *           a line to the vector of lines and a function to print the lines.
 *
 */

#ifndef _FILE
#define _FILE

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "DirNode.h"
#include "File.h"
#include "FSTree.h"

using namespace ::std;

class File
{
public:
    // Constructors
    File();
    File(string fileName, string filePath);

    // Getters
    string getFileName();
    string getPath();
    string getLine(int lineNum);
    int getNumLines();

    // Setters
    void setFileName(string file);
    void setPath(string filePath);

    // Utility functions
    void addLine(string line);

    // Tester functions
    void printLines();

private:
    // Private member variables
    string file;
    string path;
    vector<string> lines;
};

#endif