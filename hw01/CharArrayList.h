/*
 *  CharArrayList.h
 *  Created by: Dan Glorioso
 *  Date: 09/15/2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  PURPOSE: Declaration of the CharArrayList class, which includes variables
 *           and functions for a dynamic array of characters. The role is this
 *           class is to store a sequence of characters and provide functions
 *           to manipulate the sequence. Functions include adding, removing,
 *           and replacing characters, as well as concatenating 
 *           two CharArrayLists.
 *
 */

#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H
#include <iostream>
#include <sstream>

class CharArrayList {

public:
    //Constructor
    CharArrayList();
    CharArrayList(char c);
    CharArrayList(char arr[], int size);
    CharArrayList(const CharArrayList &other);

    //Destructor
    ~CharArrayList();

    //interface functions
    int size() const;
    CharArrayList &operator=(const CharArrayList &other);
    bool isEmpty() const;
    void clear();
    char first() const;
    char last() const;
    char elementAt(int index) const;
    std::string toString() const;
    std::string toReverseString() const;
    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharArrayList *other);

private:
    void expand();
    int currSize;
    int capacity;
    char *data;
};

#endif
