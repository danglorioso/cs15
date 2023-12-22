/*
 *  CharLinkedList.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/21/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  PURPOSE: Implementation of the CharLinkedList class, which includes
 *           variables and functions for a doubly linked list of characters.
 *           This file contains the implementation of the functions declared
 *           in CharLinkedList.h
 *
 */

#include "CharLinkedList.h"
#include <iostream>
#include <sstream>

using namespace std;

//Constructors
/* CharLinkedList()
 *    Purpose: Create a new CharLinkedList object with no parameters
 * Parameters: None
 *    Returns: None
 */
CharLinkedList::CharLinkedList() {
    front = NULL;
    back = NULL;
    currSize = 0;
}

/* CharLinkedList(char c)
 *    Purpose: Create a new CharLinkedList object with a single character
 * Parameters: char c - the character to be stored in the list
 *    Returns: None
 */
CharLinkedList::CharLinkedList(char c) {
    front = new Node;
    front->data = c;
    front->next = NULL;
    front->previous = NULL;
    back = front;
    currSize = 1;
}

/* CharLinkedList(char arr[], int size)
 *    Purpose: Create a new CharLinkedList object with an array of characters
 *             by using the pushAtBack function
 * Parameters: char arr[] - the array of characters to be stored in the list
 *             int size - the size of the array
 *    Returns: None
 */ 
CharLinkedList::CharLinkedList(char arr[], int size) {
    front = NULL;
    back = NULL;
    currSize = 0;
    for (int i = 0; i < size; i++) {
        pushAtBack(arr[i]);
    }
}

/* CharLinkedList(const CharLinkedList &other)
 * Purpose: Create a new CharLinkedList object with another CharLinkedList
 * Parameters: const CharLinkedList &other - the CharLinkedList to be copied
 *    Returns: None
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other) {
    front = NULL;
    back = NULL;
    currSize = 0;
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(other.elementAt(i));
    }
}

//Destructor
/* ~CharLinkedList()
 *    Purpose: Destroy a CharLinkedList object by using a recursive helper
 *             function to delete all nodes in the list
 * Parameters: None
 *    Returns: None
 */
CharLinkedList::~CharLinkedList() {
    //run the recursive helper function to delete all nodes
    deleteNodeRecursive(front);
}

//Helper Functions
/*deleteNodeRecursive(Node *node)
 *    Purpose: Delete all nodes in the list recursively
 * Parameters: Node *node - the node to be deleted
 *    Returns: None
 */
void CharLinkedList::deleteNodeRecursive(Node *node) {
    if (node == NULL) {
        return;
    }
    deleteNodeRecursive(node->next);
    delete node;
}

/*elementAtRecursive(Node *node, int index, int currIndex)
 *    Purpose: Return the character at the specified index of the 
 *             CharLinkedList object recursively
 * Parameters: Node *node - the node to be deleted
 *             int index - the index of the character to be returned
 *             int currIndex - the current index of the node
 *    Returns: char - the character at the specified index of the
 *             CharLinkedList object
 */
char CharLinkedList::elementAtRecursive(Node *node, int index, 
                                                        int currIndex) const {
    if (currIndex == index) {
        return node->data;
    } else {
        return (elementAtRecursive(node->next, index, currIndex + 1));
    }
}

/*insertAtRecursive(Node *node, char c, int index, int currIndex)
 *   Purpose: Add a character to the CharLinkedList object at the specified
 *            index recursively
 * Parameters: Node *node - the node to be deleted
 *             char c - the character to be added to the CharLinkedList object
 *             int index - the index at which the character will be added
 *             int currIndex - the current index of the node
 *    Returns: None
 *    Effects: The CharLinkedList object will have a new node at the specified
 *             index
 */
void CharLinkedList::replaceAtRecursive(Node *node, char c, int index, 
                                                              int currIndex) {
    if (currIndex == index) {
        node->data = c;
    } else {
        replaceAtRecursive(node->next, c, index, currIndex + 1);
    }
}

//Interface Functions
/* size()
 *    Purpose: Return the size of the CharLinkedList object
 * Parameters: None
 *    Returns: int - the size of the list
 */
int CharLinkedList::size() const {
    return currSize;
}

/* isEmpty() 
 *   Purpose: Determine whether or not the CharLinkedList object is empty.
 * Parameters: None
 *    Returns: bool - true if the list is empty, false otherwise
 */
bool CharLinkedList::isEmpty() const {
    return (currSize == 0);
 }

/* elementAt(int index)
 *    Purpose: Return the character at the specified index of the 
 *             CharLinkedList object by calling a recursive helper function. 
 * Parameters: int index - the index of the character to be returned
 *    Returns: char - the character at the specified index of the
 *             CharLinkedList object
 */
char CharLinkedList::elementAt(int index) const {
    if (index < 0 or index >= currSize)
    {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + ")");
    }
    return elementAtRecursive(front, index, 0);
}

/*toString()
 *   Purpose: Return a string representation of the CharLinkedList object
 * Parameters: None
 *    Returns: string - the string representation of the CharLinkedList
 *             object.
 */
std::string CharLinkedList::toString() const {
    stringstream ss;
    ss << "[CharLinkedList of size " << currSize << " <<";
    Node *currNode = front;
    while (not(currNode == NULL)) {
        ss << currNode->data;
        currNode = currNode->next;
    }
    ss << ">>]";
    return ss.str();
}

/* pushAtBack(char c)
*    Purpose: Add a character to the back of the CharLinkedList object
* Parameters: char c - the character to be added to the end of the
*             CharLinkedList object. 
*    Returns: None
*    Effects: The CharLinkedList object will have a new node at the end of 
*             the list
*/
void CharLinkedList::pushAtBack(char c) {
    Node *newNode = new Node;
    newNode->data = c;
    newNode->next = NULL;
    newNode->previous = back;
    if (isEmpty()) {
        front = newNode;
    } else {
        back->next = newNode;
    }
    back = newNode;
    currSize++;
}

/* pushAtFront(char c)
 *    Purpose: Add a character to the front of the CharLinkedList object
 * Parameters: char c - the character to be added to the front of the
 *             CharLinkedList object.
 *    Returns: None
 *    Effects: The CharLinkedList object will have a new node at the front of
 *             the list
 */
 void CharLinkedList::pushAtFront(char c) {
    Node *newNode = new Node;
    newNode->data = c;
    newNode->next = front;
    newNode->previous = NULL;
    if (isEmpty()) {
        back = newNode;
    } else {
        front->previous = newNode;
    }
    front = newNode;
    currSize++;
 }


/* insertAt(char c, int index)
*    Purpose: Add a character to the CharLinkedList object at the specified
*            index
* Parameters: char c - the character to be added to the CharLinkedList object
*             int index - the index at which the character will be added
*    Returns: None
*    Effects: The CharLinkedList object will have a new node at the specified
*             index
*/
void CharLinkedList::insertAt(char c, int index) {
    if (index < 0 or index > currSize) {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + "]");
    }
    if (index == 0) {
        pushAtFront(c);
    } else if (index == currSize) {
        pushAtBack(c);
    } else {
        Node *newNode = new Node;
        newNode->data = c;
        Node *currNode = front;
        for (int i = 0; i < index; i++) {
            currNode = currNode->next;
        }
        newNode->next = currNode;
        newNode->previous = currNode->previous;
        currNode->previous->next = newNode;
        currNode->previous = newNode;
        currSize++;
    }
}

/*popFromFront()
 *    Purpose: Remove a character from the CharLinkedList object at the front
 * Parameters: None
 *    Returns: None
 *    Effects: The CharLinkedList object will have a node removed at the front
 *             of the list
 */ 
void CharLinkedList::popFromFront() {
    if (currSize == 0 or isEmpty()) {
        throw runtime_error("cannot pop from empty LinkedList");
    }

    if (currSize == 1) {
        delete front;
        front = NULL;
        back = NULL;
        currSize--;
    } else {
        Node *temp = front;
        front = front->next;
        front->previous = NULL;
        delete temp;
        currSize--;
    }
}

/*popFromBack()
*    Purpose: Remove a character from the CharLinkedList object at the back
* Parameters: None
*    Returns: None
*    Effects: The CharLinkedList object will have a node removed at the back
*             of the list
*/
void CharLinkedList::popFromBack() {
    if (currSize == 0 or isEmpty()) {
        throw runtime_error("cannot pop from empty LinkedList");
    }
    if (currSize == 1) {
        delete front;
        front = NULL;
        back = NULL;
        currSize--;
        return;
    } else {
        Node *temp = back;
        back = back->previous;
        back->next = NULL;
        delete temp;
        currSize--;
    }
}

/*removeAt(int index)
 *    Purpose: Remove a character from the CharLinkedList object at the 
 *             specified index
 * Parameters: int index - the index at which the character will be removed
 *    Returns: None
 *    Effects: The CharLinkedList object will have a node removed at the 
 *             specified index
 */
void CharLinkedList::removeAt(int index) {
    if (index < 0 or index >= currSize) {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + ")");
    }
    if (index == 0) {
        popFromFront();
    } else if (index == currSize - 1) {
        popFromBack();
    } else {
        Node *currNode = front;
        for (int i = 0; i < index; i++) {
            currNode = currNode->next;
        }
        currNode->previous->next = currNode->next;
        currNode->next->previous = currNode->previous;
        delete currNode;
        currSize--;
    }
}

/*replaceAt(char c, int index)
 *   Purpose: Replace a character from the CharLinkedList object at the
 *            specified index with a new character by calling a recursive
 *            helper function replaceAtRecursive
 * Parameters: char c - the character to be added to the CharLinkedList object
 *             int index - the index at which the character will be added
 *    Returns: None
 *    Effects: The CharLinkedList object will have a node replaced at the
 *             specified index
 */
void CharLinkedList::replaceAt(char c, int index) {
    if (index < 0 or index >= currSize) {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + ")");
    }
    replaceAtRecursive(front, c, index, 0);
}

/* clear()
 *   Purpose: Clear the CharLinkedList object by deleting all nodes
 * Parameters: None
 *    Returns: None
 */
void CharLinkedList::clear() {
    deleteNodeRecursive(front);
    front = NULL;
    back = NULL;
    currSize = 0;
}

/* first()
 *    Purpose: Return the first character of the CharLinkedList object
 * Parameters: None
 *    Returns: char - the first character of the CharLinkedList object
 */
char CharLinkedList::first() const {
    if (isEmpty()) {
        throw runtime_error("cannot get first of empty LinkedList");
    }
    return front->data;
}

/* last()
 *   Purpose: Return the last character of the CharLinkedList object
 * Parameters: None
 *    Returns: char - the last character of the CharLinkedList object
 */
char CharLinkedList::last() const {
    if (isEmpty()) {
        throw runtime_error("cannot get last of empty LinkedList");
    }
    return back->data;
}

/* toReverseString()
 *    Purpose: Return a string representation of the CharLinkedList object
 *             in reverse order
 * Parameters: None
 *    Returns: string - the string representation of the CharLinkedList
 *             object in reverse order.
 */
std::string CharLinkedList::toReverseString() const {
    stringstream ss;
    ss << "[CharLinkedList of size " << currSize << " <<";
    Node *currNode = back;
    while (not(currNode == NULL)) {
        ss << currNode->data;
        currNode = currNode->previous;
    }
    ss << ">>]";
    return ss.str();
}

/* insertInOrder(char c)
 *   Purpose: Add a character to the CharLinkedList object in alphabetical
*            order
* Parameters: char c - the character to be added to the CharLinkedList object
*    Returns: None
*    Effects: The CharLinkedList object will have a new node added in
*             alphabetical order
*/
void CharLinkedList::insertInOrder(char c) {
    if (isEmpty()) {
        pushAtFront(c);
        return;
    }
    Node *currNode = front;
    int index = 0;
    while (not(currNode == NULL)) {
        if (c < currNode->data) {
            insertAt(c, index);
            return;
        }
        currNode = currNode->next;
        index++;
    }
    pushAtBack(c);
}

/* CharLinkedList &operator=(const CharLinkedList &other)
 *    Purpose: Overload the assignment operator to make a deep copy of the
 *             CharLinkedList object passed in.
 * Parameters: const CharLinkedList &other - the CharLinkedList to be copied
 *    Returns: CharLinkedList - a reference to the CharLinkedList object that
 *             was copied
 *    Effects: Recycles memory for the left hand side and allocates memory for
 *             the right hand side. Copies the member variables of the right
 *             hand side to the left hand side. 
 */ 
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other) {
    if (not(this == &other)) {
        //Recycle memory for the left hand side
        clear();

        //Copy member variables of the right hand side
        for (int i = 0; i < other.size(); i++) {
            pushAtBack(other.elementAt(i));
        }
    }
    return *this;
}

/* concatenate(CharLinkedList *other)
 *    Purpose: Concatenate two CharLinkedList objects together by adding the
 *             second list to the end of the first list
 * Parameters: CharLinkedList *other - a point to another CharLinkedList to be
 *             added to the end of the first list
 *    Returns: None
 *    Effects: The first CharLinkedList object will have the second list added
 *             to the end of it
 */
void CharLinkedList::concatenate(CharLinkedList *other) {
    if (this == other) {
        CharLinkedList *temp = new CharLinkedList(*other);
        concatenate(temp);
        delete temp;
        return;
    }
    for (int i = 0; i < other->size(); i++) {
        pushAtBack(other->elementAt(i));
    }
}
