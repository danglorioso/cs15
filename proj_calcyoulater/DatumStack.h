/*
 *  DatumStack.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/15/2023
 *
 *  CS 15 PROJECT 2: CalcYouLater
 *
 *  PURPOSE: Declaration of the DatumStack class that includes a vector
 *           of Datum objects and functions to manipulate the stack.
 *
 */

#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include <vector>
#include "Datum.h"

class DatumStack
{
public:
    // // constructors
    DatumStack();
    DatumStack(Datum [], int size);

    // // interface functions
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum d);

private:
    std::vector<Datum> stack;
};

#endif