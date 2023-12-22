/*
 *  Gerp.h
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 12/04/23
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Declaration of the Gerp class which will be used to index and
 *           search through files in a directory tree and run the program
 *           query loop. Functions include a constructor, destructor, and
 *           functions to index the files in a directory tree and take in
 *           user queries.
 *
 */

#ifndef GERP_H
#define GERP_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "FSTree.h"
#include "DirNode.h"
#include "File.h"
#include "HashTable.h"

using namespace ::std;

class Gerp
{
public:
    // Constructor
    Gerp();

    // Destructor
    ~Gerp();

    // Functions used by main
    void Index(string &inputDir);
    void Query(string outputFile);

private:
    // Private member variables
    DirNode *root;
    FSTree *tree;
    vector<File *> files;
    HashTable *hashTable;

    // Index helpers
    void makeTree(string &inputDir);
    void traverseTree(DirNode *node, string &path);
    void readLines(string &filePath, File *fileInstance, int fileIndex);
    void parseLine(string &line, int lineNum, int fileIndex);
    string stripNonAlphaNum(string &word);

    // Query helpers
    void prompt_and_execute(string &outputFile);
    void searchWord(string func, bool sensitive, ostream &output);
    void printLocations(set<pair<int, int>> *locations, bool sensitive, 
                        string word, ostream &out);

    // Testing functions
    void printFiles();

    // File reading helpers
    template <typename streamtype>
    void open_or_die(streamtype &stream, string &fileName);
};

#endif