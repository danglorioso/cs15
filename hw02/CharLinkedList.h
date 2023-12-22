/*
 *  CharLinkedList.h
 *  Created by: Dan Glorioso
 *  Date: 09/21/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Purpose: Declaration of the CharLinkedList class, which includes variables
 *           and functions for a doubly linked list of characters. The role of
 *           this class is to store a sequence of characters and provide
 *           functions to manipulate the sequence. Functions include adding,
 *           removing, and replacing characters, as well as concatenating
 *           two CharLinkedLists.
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H
#include <iostream>
#include <sstream>

class CharLinkedList {

public:
    //Constructors
    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);

    //Destructor
    ~CharLinkedList();

    //interface functions
    CharLinkedList &operator=(const CharLinkedList &other);
    bool isEmpty() const;
    void clear();
    int size() const;
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
    void concatenate(CharLinkedList *other);

private:
    struct Node {
        char data;
        Node *next;
        Node *previous;
    };

    Node *front;
    Node *back;

    int currSize;

    void deleteNodeRecursive(Node *node);
    char elementAtRecursive(Node *node, int index, int currIndex) const;
    void replaceAtRecursive(Node *node, char c, int index, int currIndex);
};

#endif
