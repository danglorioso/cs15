/*
 *  HashTable.h
 *  Author: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 11/30/2023
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Declaration of the HashTable class. This class is used to store
 *           all of the words and their locations in the files. It is used to
 *           search for words and their locations in the files. Functions
 *           include: insertWord, getBucket, makeLower, createValHelper, 
 *           createValue, createWordVar, createWordLocation, traverseLL,
 *           traverseWordVars, getLoadFactor, expand, expandHelper, and
 *           print_ValStruct.
 *
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <set>
#include <list>
#include <utility>

#include "File.h"

using namespace ::std;

class HashTable
{
public:
    // Constructor
    HashTable();
    // Destructor
    ~HashTable();

    // Functions used by Gerp
    set<pair<int, int>> *getWordLocation(string word, bool sensitive);
    void insertWord(string word, int lineNum, int fileIndex);

private:
    // Private member variables
    // word variations and their locations as a set of pairs:
    // (lineNum, fileIndex)
    struct wordVar
    {
        string word;
        set<pair<int, int>> wordLocations;
    };

    // Value struct for the hash table to deal with collisions and finding
    // the correct word
    struct Value
    {
        string key;
        set<wordVar *> wordVars;
        set<pair<int, int>> wordLocationsInsen;
    };

    int numBucketsFilled;
    // hash table
    vector<list<Value *> *> hashVector;

    int getBucket(string key, int size);
    string makeLower(string word);

    // Add object to hash functions
    Value *createValHelper(string word, string lowerWord, int lineNum,
                           int fileIndex, list<Value *> *currLL);
    Value *createValue(list<Value *> *currLL, string lowerWord);
    wordVar *createWordVar(Value *newVal, string word);
    pair<int, int> createWordLocation(wordVar *newWordVar, Value *newVal,
                                      int lineNum, int fileIndex);

    // traversing hash table functions
    Value *traverseLL(list<Value *> *currLL, string lowerWord);
    wordVar *traverseWordVars(Value *currVal, string word);

    // background hash table operations
    float getLoadFactor();
    void expand();
    void expandHelper();

    // tester functions
    void print_ValStruct(Value *val);
};

#endif