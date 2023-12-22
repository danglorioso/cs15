/*
 *  DatumStack.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/15/2023
 *
 *  CS 15 PROJECT 2: CalcYouLater
 *
 *  PURPOSE: Implementation of the DatumStack class which include functions
 *           to manipulate a stack of Datum objects.
 *
 */

#include "DatumStack.h"
#include <istream>
#include <vector>
#include <string>

using namespace std;

/* DatumStack()
 *    Purpose: Default constructor for DatumStack - initializes an empty stack
 * Parameters: None
 *     Return: None 
 */
DatumStack::DatumStack() {
    stack = vector<Datum>();
}

/* DatumStack(Datum [], int size)
 *    Purpose: Constructor for DatumStack - initializes a stack with the given
 *             array of Datum objects
 * Parameters: Datum [] - array of Datum objects whth which to initialize the 
 *             stack
 *             int size - size of the array
 *     Return: None 
 */
DatumStack::DatumStack(Datum d[], int size) {
    stack = vector<Datum>();
    for (int i = 0; i < size; i++)
    {
        stack.push_back(d[i]);
    }
}

/* isEmpty()
 *    Purpose: Returns whether or not the stack is empty
 * Parameters: None
 *     Return: bool - true if the stack is empty, false if not empty
 */
bool DatumStack::isEmpty() {
    return stack.empty();
}

/* clear()
 *    Purpose: Clears the stack
 * Parameters: None
 *     Return: None
 *     Effect: The stack is cleared afterward
 */
void DatumStack::clear() {
    stack.clear();
}

/* size()
 *    Purpose: Retrieve the size of the stack
 * Parameters: None
 *     Return: int - size of the stack
 */
int DatumStack::size() {
    return stack.size();
}

/* top()
 *    Purpose: Returns the top Datum object on the stack
 * Parameters: None
 *     Return: Datum - top Datum object on the stack
 */
Datum DatumStack::top() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    return stack.back();
}

/* pop()
 *    Purpose: Removes the top Datum object from the stack
 * Parameters: None
 *     Return: None
 */
void DatumStack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    stack.pop_back();
}

/* push(Datum d)
 *    Purpose: Pushes the given Datum object onto the stack
 * Parameters: Datum d - Datum object to push onto the stack
 *     Return: None
 */
void DatumStack::push(Datum d) {
    stack.push_back(d);
}
