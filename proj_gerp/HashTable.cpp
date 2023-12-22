/*
 *  HashTable.cpp
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 11/30/23
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Implementation of HashTable class which is a hash table that
 *           stores words and their locations. The hash table is dynamically
 *           resized when the load factor exceeds 0.7. The hashVector is a
 *           vector of linked lists that stores Value structs. The Value struct
 *           stores the key (word), a set of wordVar structs, and a set of
 *           wordLocations. The wordVar struct stores the word variations
 *           (capitalization) and a set of wordLocations. The wordLocation
 *           struct stores the line number and file index of the word.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <functional>

#include "HashTable.h"

using namespace ::std;

/*
 * name:      default constructor
 * purpose:   initializes private member variables
 * arguments: none
 * returns:   none
 * effects:   numBuckets is set to 0
 */
HashTable::HashTable()
{
    numBucketsFilled = 0;
}

/*
 * name:      destructor
 * purpose:   deletes all dynamically allocated memory
 * arguments: none
 * returns:   none
 * effects:   deletes all dynamically allocated memory
 */
HashTable::~HashTable()
{
    // traverse through hashVector and delete all dynamically allocated memory
    int size = hashVector.size();
    for (int i = 0; i < size; i++)
    {
        if (hashVector[i] != nullptr)
        {
            for (list<Value *>::iterator val = hashVector[i]->begin(); val != 
                hashVector[i]->end(); val++)
            {
                if (*val != nullptr)
                {
                    for (wordVar *wordVarIns : (*val)->wordVars)
                    {
                        delete wordVarIns;
                    }
                }
                delete *val;
            }
        }
        delete hashVector[i];
    }
}

/*
 * name:      print_ValStruct
 * purpose:   prints the contents of a Value struct
 * arguments: Value *val - pointer to Value struct
 * returns:   none
 * effects:   prints the contents of a Value struct
 */
void HashTable::print_ValStruct(Value *val)
{
    cout << "printing val struct" << endl;
    cout << "key: " << val->key << endl;
    for (auto const &wordVar : val->wordVars)
    {
        cout << "word: " << wordVar->word << endl;
        for (auto const &wordLocation : wordVar->wordLocations)
        {
            cout << "lineNum: " << wordLocation.first << endl;
            cout << "fileIndex: " << wordLocation.second << endl;
        }
    }
}

/*
 * name:      insertWord
 * purpose:   inserts a word into the hash table
 * arguments: string word - word to insert, int lineNum - line number of word,
 *            int fileIndex - file index of word
 * returns:   none
 * effects:   inserts a word into the hash table
 */
void HashTable::insertWord(string word, int lineNum, int fileIndex)
{
    string lowerWord = makeLower(word);     // convert to lowercase
    // if hashVector is empty or load factor exceeds 0.7, expand
    if (hashVector.size() == 0 or getLoadFactor() > 0.7)
        expand();    
        
    // find the bucket index of the word
    int bucket = getBucket(lowerWord, hashVector.size());
    list<Value *> *currLL;
    if (hashVector[bucket] == nullptr) {   // if bucket is empty, create new LL
        hashVector[bucket] = new list<Value *>();
        currLL = hashVector[bucket];
    } else     // the bucket must already have at least one word in it
        currLL = hashVector[bucket];    
    
    Value *currVal = traverseLL(currLL, lowerWord); // traverse LL to find key
    
    // if LL is currently empty or if the bucket is not empty but
    // no matching word
    if (currVal == nullptr)
        currVal = createValHelper(word, lowerWord, lineNum, fileIndex, currLL);
    // else the bucket must already have at least one word in it
    else {
        wordVar *currWordVar = traverseWordVars(currVal, word);
        if (currWordVar == nullptr) {   // new word variation (capitalization)
            currWordVar = createWordVar(currVal, word);
            createWordLocation(currWordVar, currVal, lineNum, fileIndex);
        } else  // word variation already exists
            createWordLocation(currWordVar, currVal, lineNum, fileIndex);
    }
    numBucketsFilled++;     // increment numBucketsFilled
}

/*
 * name:      getBucket
 * purpose:   returns the bucket index of a word
 * arguments: string key - word to hash, int size - size of hashVector
 * returns:   int - bucket index of word
 * effects:   none
 */
int HashTable::getBucket(string key, int size)
{
    // find the bucket index of the word
    int slot = hash<string>{}(key) % size;
    return slot;
}

/*
 * name:      getLoadFactor
 * purpose:   returns the load factor of the hash table
 * arguments: none
 * returns:   float of load factor
 * effects:   none
 */
float HashTable::getLoadFactor()
{
    // if hashVector is empty, return -1
    if (hashVector.size() == 0)
        return -1;
    return float(numBucketsFilled) / hashVector.size();
}

/*
 * name:      expand
 * purpose:   expands the hash table when the load factor exceeds 0.7
 * arguments: none
 * returns:   none
 * effects:   expands the hash table
 */
void HashTable::expand()
{
    // create new hashVector with double the size
    vector<list<Value *> *> *newHashVector = new vector<list<Value *> *>();
    newHashVector->resize(hashVector.size() * 2 + 2);
    list<Value *> *newList = nullptr;

    // traverse through old hashVector and rehash all words
    int size = hashVector.size();
    for (int i = 0; i < size; i++)
    {
        newList = hashVector[i];
        if (newList != nullptr)
        {
            for (list<Value *>::iterator val = hashVector[i]->begin(); val != 
                hashVector[i]->end(); val++)
            {
                if (*val != nullptr)
                {
                    int bucket = getBucket((*val)->key, newHashVector->size());
                    if ((*newHashVector)[bucket] == nullptr)
                    {
                        (*newHashVector)[bucket] = new list<Value *>();
                    }
                    (*newHashVector)[bucket]->push_back(*val);
                }
            }
        }
    }
    expandHelper();
    hashVector = *newHashVector;
    delete newHashVector;
}

/*
 * name:      expandHelper
 * purpose:   deletes all the old LLs in the old hashVector
 * arguments: none
 * returns:   none
 * effects:   deletes all dynamically allocated memory in hashVector
 */
void HashTable::expandHelper()
{
    int size = hashVector.size();
    for (int i = 0; i < size; i++)
    {
        if (hashVector[i] != nullptr)
        {
            delete hashVector[i];
        }
    }
}

/*
 * name:      traverseLL
 * purpose:   traverses through a linked list to find a word
 * arguments: list<Value *> *currLL - linked list to traverse,
 *            string lowerWord - word to find
 * returns:   Value * - pointer to Value struct
 * effects:   none
 */
HashTable::Value *HashTable::traverseLL(list<Value *> *currLL,
                                        string lowerWord)
{
    // if LL is empty, return nullptr
    if (currLL->empty())
        return nullptr;
    // traverse through LL to find correct word/key
    for (auto it = currLL->begin(); it != currLL->end(); it++)
    {
        if ((*it)->key == lowerWord)
            return *it;
    }
    // if no matching word
    return nullptr;
}

/*
 * name:      traverseWordVars
 * purpose:   traverses through a set of wordVars to find a word
 * arguments: Value *currVal - pointer to Value struct,
 *            string word - word to find
 * returns:   wordVar * - pointer to wordVar struct
 * effects:   none
 */
HashTable::wordVar *HashTable::traverseWordVars(Value *currVal, string word)
{
    for (auto const &wordVar : currVal->wordVars)
    {
        if (wordVar->word == word)
        {
            return wordVar;
        }
    }
    // if no matching word
    return nullptr;
}

/*
 * name:      createValHelper
 * purpose:   creates a Value struct and its wordVar and wordLocation structs
 * arguments: string word - word to insert, string lowerWord - lowercase word,
 *            int lineNum - line number of word, int fileIndex - file index of
 *            word, list<Value *> *currLL - linked list to insert into
 * returns:   Value * - pointer to Value struct
 * effects:   creates a Value struct and its wordVar and wordLocation structs
 */
HashTable::Value *HashTable::createValHelper(string word, string lowerWord,
                                             int lineNum, int fileIndex, 
                                             list<Value *> *currLL)
{
    //create a new val with a new word variation, and new word location
    Value *newVal = createValue(currLL, lowerWord);
    wordVar *newWordVar = createWordVar(newVal, word);
    createWordLocation(newWordVar, newVal, lineNum, fileIndex);
    return newVal;
}

/*
 * name:      createValue
 * purpose:   creates a Value struct and adds it to a linked list
 * arguments: list<Value *> *currLL - linked list to insert into,
 *            string lowerWord - lowercase word
 * returns:   Value * - pointer to Value struct
 * effects:   creates a Value struct and adds it to a linked list
 */
HashTable::Value *HashTable::createValue(list<Value *> *currLL,
                                         string lowerWord)
{
    //crate boiler plate new val
    Value *newVal = new Value();
    newVal->key = lowerWord;
    currLL->push_back(newVal);
    return newVal;
}

/*
 * name:      createWordVar
 * purpose:   creates a wordVar struct and adds it to a Value struct
 * arguments: Value *newVal - pointer to Value struct,
 *            string word - word to insert
 * returns:   wordVar * - pointer to wordVar struct
 * effects:   creates a wordVar struct and adds it to a Value struct
 */
HashTable::wordVar *HashTable::createWordVar(Value *newVal, string word)
{
    // create a new word variation
    wordVar *newWordVar = new wordVar();
    newWordVar->word = word;
    newVal->wordVars.insert(newWordVar);
    return newWordVar;
}

/*
 * name:      createWordLocation
 * purpose:   creates a wordLocation struct and adds it to a wordVar struct
 * arguments: wordVar *newWordVar - pointer to wordVar struct,
 *            Value *newVal - pointer to Value struct,
 *            int lineNum - line number of word, int fileIndex - file index of
 *            word
 * returns:   pair<int,int> - pair of line number and file index
 * effects:   creates a wordLocation struct and adds it to a wordVar struct
 */
pair<int, int> HashTable::createWordLocation(wordVar *newWordVar, 
                                    Value *newVal,  int lineNum, int fileIndex)
{
    // create a new word location
    pair<int, int> wordLocation;
    wordLocation.first = lineNum;
    wordLocation.second = fileIndex;

    newWordVar->wordLocations.insert(wordLocation);
    newVal->wordLocationsInsen.insert(wordLocation);
    return wordLocation;
}

/*
 * name:      makeLower
 * purpose:   converts a string to lowercase
 * arguments: string word - word to convert
 * returns:   string - lowercase word
 * effects:   converts a string to lowercase
 */
string HashTable::makeLower(string word)
{
    // go through evey character in the word and convert it to lowercase
    int length = word.length();
    for (int i = 0; i < length; i++)
    {
        word[i] = tolower(word[i]);
    }
    return word;
}

/*
 * name:      getWordLocation
 * purpose:   returns a set of wordLocations for a given word
 * arguments: string word - word to find, bool sensitive - case sensitivity
 * returns:   set<pair<int,int>> * - pointer to set of wordLocations
 * effects:   none
 */
set<pair<int, int>> *HashTable::getWordLocation(string word, bool sensitive)
{
    // convert to lowercase for getting bucket
    string lowerWord = makeLower(word);
    int bucket = getBucket(lowerWord, hashVector.size());
    list<Value *> *currLL = hashVector[bucket];
    // if LL is empty, return nullptr
    if (currLL == nullptr)
        return nullptr;
    Value *currVal = traverseLL(currLL, lowerWord);
    // if no matching word
    if (currVal == nullptr)
        return nullptr;
    // if case sensitive return wordLocations, else return wordLocationsInsen
    if (sensitive)
    {
        wordVar *currWordVar = traverseWordVars(currVal, word);
        if (currWordVar == nullptr)
            return nullptr;
        set<pair<int, int>> *locations = &currWordVar->wordLocations;
        return locations;
    }
    else
    {
        set<pair<int, int>> *locations = &currVal->wordLocationsInsen;
        return locations;
    }
}