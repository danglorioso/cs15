/*
 *  CharArrayList.cpp
 *  Created by: Dan Glorioso
 *  Date: 09/15/2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 * 
 *  PURPOSE: Implementation of the CharArrayList class, which includes 
 *          variables and functions for a dynamic array of characters. This
 *          file contains the implementation of the functions declared in
 *          CharArrayList.h.
 *
 */

#include "CharArrayList.h"
#include <iostream>
#include <sstream>

using namespace std;

//Constructors
/* CharArrayList()
 *    Purpose: Default constructor for CharArrayList class. Initializes
 *             member variables.
 * Parameters: None
 *    Returns: None
 */
CharArrayList::CharArrayList()
{
    currSize = 0;
    data = nullptr;
    capacity = 0;
}
/* CharArrayList(char c)
 *    Purpose: Constructor for CharArrayList class. Initializes member
 *             variables and sets the first element of the array to the
 *             character passed in.
 * Parameters: char c - character to be set as the first element of the array
 *    Returns: None
 */
CharArrayList::CharArrayList(char c)
{
    capacity = 1;
    data = new char[1];
    data[0] = c;
    currSize = 1;
}

/* CharArrayList(char arr[], int size)
 *    Purpose: Constructor for CharArrayList class. Initializes member
 *             variables and sets the array to the array passed in.
 * Parameters: char arr[], an array of characters to be set as the array and
    *             int size, the size of the array. 
 *    Returns: None
 */
CharArrayList::CharArrayList(char arr[], int size)
{
    capacity = size;
    data = new char[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = arr[i];
    }
    currSize = size;
}

/* CharArrayList(const CharArrayList &other)
 *    Purpose: Copy constructor for CharArrayList class that makes a deep copy
 *             of the CharArrayList object passed in.
 * Parameters: const CharArrayList &other, a reference to another
 *             CharArrayList object to be copied.
 *    Returns: None
 */
CharArrayList::CharArrayList(const CharArrayList &other)
{
    capacity = other.capacity;
    currSize = other.currSize;
    data = new char[capacity];
    for (int i = 0; i < other.currSize; i++)
    {
        data[i] = other.data[i];
    }
}

//Destructor
/* ~CharArrayList()
 *    Purpose: Destructor for CharArrayList class. Deallocates memory for the
 *             array.
 * Parameters: None
 *    Returns: None
 */
CharArrayList::~CharArrayList() 
{
    delete [] data;
}

/* toString()
 *    Purpose: Returns a string representation of the CharArrayList object.
 * Parameters: None
 *    Returns: string, a string representation of the CharArrayList object.
 */
std::string CharArrayList::toString() const
{
    std::string str = "[CharArrayList of size " + std::to_string(currSize) 
                        + " <<";
    for (int i = 0; i < currSize; i++)
    {
        str += data[i];
    }
    str += ">>]";
    
    return str;
}

/* toReverseString()
 *    Purpose: Returns a string representation of the CharArrayList object
 *             in reverse order.
 * Parameters: None
 *    Returns: string, a string representation of the CharArrayList object
 *             in reverse order.
 */
std::string CharArrayList::toReverseString() const
{
    std::string str = "[CharArrayList of size " + std::to_string(currSize) 
                        + " <<";
    for (int i = currSize - 1; i >= 0; i--)
    {
        str += data[i];
    }
    str += ">>]";
    
    return str;
}

/* size()
 *    Purpose: Returns the size of the CharArrayList object.
 * Parameters: None
 *    Returns: int, the size of the CharArrayList object.
 */
int CharArrayList::size() const
{
    return currSize;
}

/* isEmpty()
 *    Purpose: Determine whether or not the CharArrayList object is empty.
 * Parameters: None
 *    Returns: bool, true if the CharArrayList object is empty, false if not.
 */
bool CharArrayList::isEmpty() const
{
    return (currSize == 0);
}

/* elementAt(int index)
 *    Purpose: Returns the character at the specified index of the
 *             CharArrayList object. 
 * Parameters: int index, the index of the character to be returned.
 *    Returns: char, the character at the specified index of the
 *             CharArrayList object.
 */
char CharArrayList::elementAt(int index) const
{
    //checks if input is within bounds of the array (valid)
    if (index < 0 || index >= currSize)
    {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + ")");
    }
    return data[index];
}

/* pushAtBack(char c)
 *    Purpose: Adds a character to the end of the CharArrayList object.
 * Parameters: char c, the character to be added to the end of the
 *             CharArrayList object.
 *    Returns: None
 *    Effects: Adds a character to the end of the CharArrayList object and 
 *             increments the size of the CharArrayList object.
 */
void CharArrayList::pushAtBack(char c)
{
    if (currSize == capacity)
    {
        expand();
    }
    data[currSize] = c;
    currSize++;
}

/* pushAtFront(char c)
 *    Purpose: Adds a character to the front of the CharArrayList object.
 * Parameters: char c, the character to be added to the front of the
 *    Returns: None
 *    Effects: Adds a character to the front of the CharArrayList object and
 *             increments the size of the CharArrayList object.
 */
void CharArrayList::pushAtFront(char c)
{
    if (currSize == capacity)
    {
        expand();
    }
    for (int i = currSize; i > 0; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = c;
    currSize++;
}

/* insertAt(char c, int index)
 *    Purpose: Inserts a character at the specified index of the 
 *             CharArrayList object.
 * Parameters: char c, the character to be inserted into the CharArrayList
 *             object and int index, the index at which the character will be
 *             inserted.
 *    Returns: None
 *    Effects: Increments the size of the CharArrayList object and inserts 
 *             a charter. If the capacity of the CharArrayList object is not
 *             large enough to hold the new character, the capacity is doubled
 *             and the array is expanded. The elements after the specified
 *             index are shifted to the right by one.
 */
void CharArrayList::insertAt(char c, int index)
{
    if (index < 0 || index > currSize)
    {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + "]");
    }
    if (currSize == capacity)
    {
        expand();
    }
    for (int i = currSize; i > index; i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = c;
    currSize++;
}

/* removeAt(int index)
 *    Purpose: Removes a character at the specified index of the 
 *             CharArrayList object.
 * Parameters: int index, the index of the character to be removed.
 *    Returns: None
 *    Effects: Decreases the size of the CharArrayList object and shifts all
 *             elements after the specified index to the left by one.
 */
void CharArrayList::removeAt(int index)
{
    if (index < 0 || index >= currSize)
    {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + ")");
    }
    for (int i = index; i < currSize - 1; i++)
    {
        data[i] = data[i + 1];
    }
    currSize--;
}
/* replaceAt(char c, int index)
 *    Purpose: Replaces a character at the specified index of the 
 *             CharArrayList object with the character passed in.
 * Parameters: char c, the character to be inserted into the CharArrayList
 *             object and int index, the index at which the character will be
 *    Returns: None
 *    Effects: Raises an error if the index is not within the bounds of the
 *             array. Otherwise, replaces the character at the specified index
 *             with the character passed in.
 */
void CharArrayList::replaceAt(char c, int index)
{
    if (index < 0 || index >= currSize)
    {
        throw range_error("index (" + std::to_string(index) + 
                    ") not in range [0.." + std::to_string(currSize) + ")");
    }
    data[index] = c;
}

/* clear()
 *    Purpose: Clears the CharArrayList object by setting the size to 0.
 * Parameters: None
 *    Returns: None
 */
void CharArrayList::clear() 
{
    currSize = 0;    
}

/* first()
 *    Purpose: Returns the first character of the CharArrayList object.
 * Parameters: None
 *    Returns: char, the first character of the CharArrayList object.
 */
char CharArrayList::first() const
{
    // if the array is empty, throw an error
    if (currSize == 0 || isEmpty())
    {
        throw runtime_error("cannot get first of empty ArrayList");
    }
    return data[0];
}

/* last()
 *    Purpose: Returns the last character of the CharArrayList object.
 * Parameters: None
 *    Returns: char, the last character of the CharArrayList object.
 */
char CharArrayList::last() const
{
    if (currSize == 0 || isEmpty())
    {
        throw runtime_error("cannot get last of empty ArrayList");
    }
    return data[currSize - 1];
}

/* popFromFront()
 *    Purpose: Removes the first character of the CharArrayList object.
 * Parameters: None
 *    Returns: None
 *    Effects: Decreases the size of the CharArrayList object and shifts all
 *             elements after the first element to the left by one.
 */
void CharArrayList::popFromFront()
{
    if (currSize == 0 || isEmpty())
    {
        throw runtime_error("cannot pop from empty ArrayList");
    }
    for (int i = 0; i < currSize - 1; i++)
    {
        data[i] = data[i + 1];
    }
    currSize--;
}   

/* popFromBack()
 *    Purpose: Removes the last character of the CharArrayList object.
 * Parameters: None
 *    Returns: None
 *    Effects: Decreases the size of the CharArrayList object, and if the
 *             CharArrayList object is not within range, throws an error.
 */
void CharArrayList::popFromBack() 
{
    if (currSize == 0 || isEmpty())
    {
        throw runtime_error("cannot pop from empty ArrayList");
    }
    currSize--;
}

/* insertInOrder(char c)
 *    Purpose: Inserts a character into the CharArrayList object in order.
 * Parameters: char c, the character to be inserted into the CharArrayList
 *    Returns: None
 *    Effects: Raises an error if the index is not within the bounds of the
 *             array. Otherwise, replaces the character at the specified index
 *             with the character passed in.
 */
void CharArrayList::insertInOrder(char c)
{
    if (currSize == 0 || isEmpty())
    {
        pushAtBack(c);
    }
    else
    {
        int index = 0;
        while (index < currSize && c > data[index])
        {
            index++;
        }
        insertAt(c, index);
    }
}

/* operator=(const CharArrayList &other)
 *    Purpose: Overloads the assignment operator to make a deep copy of the
 *             CharArrayList object passed in.
 * Parameters: const CharArrayList &other, a reference to another
 *             CharArrayList object to be copied.
 *    Returns: CharArrayList, a reference to the CharArrayList object that was
 *             copied.
 *    Effects: Recycles memory for the left hand side and allocates memory for
 *             the right hand side. Copies the member variables of the right
 *             hand side to the left hand side.
 */
CharArrayList &CharArrayList::operator=(const CharArrayList &other) 
{
    if (this == &other) {
        return *this;
    }

    // Recycle memory for left hand side
    delete [] data;
    capacity = other.capacity;
    currSize = other.currSize;

    // Allocate memory for left hand side.
    data = new char[capacity];

    // Copy member variables of rhs.
    // For heap allocated array: Copy *each element** of the array.
    for (int i = 0; i < other.currSize; i++)
    {
        data[i] = other.data[i];
    }

    return *this;
}

/* concatenate(CharArrayList *other)
 *    Purpose: Concatenates the CharArrayList object passed in to the end of
 *             the CharArrayList object.
 * Parameters: CharArrayList *other, a pointer to another CharArrayList object
 *             to be concatenated to the end of the CharArrayList object.
 *    Returns: None
 */
void CharArrayList::concatenate(CharArrayList *other)
{
    int newSize = currSize + other->currSize;
    int newCapacity = capacity + other->capacity;
    char *newData = new char[newCapacity];
    for (int i = 0; i < currSize; i++)
    {
        newData[i] = data[i];
    }
    for (int i = 0; i < other->currSize; i++)
    {
        newData[i + currSize] = other->data[i];
    }
    delete [] data;
    data = newData;
    currSize = newSize;
    capacity = newCapacity;
}
 
/* expand() 
 *    Purpose: Expands the CharArrayList object by doubling the capacity of
 *             the array and copying the elements over to the new array.
 * Parameters: None 
 *    Returns: None 
 *    Effects: Doubles the capacity of the CharArrayList object. 
 */
void CharArrayList::expand()
{
    //allocate a new, larger array on heap
    char *newData = new char[2 * capacity + 2];
    //copy over elements to new array
    for (int i = 0; i < currSize; i++)
    {   
        newData[i] = data[i];
    }
    //recycle the old array
    delete [] data;
    //update any relevent member variables
    data = newData;
    capacity = 2 * capacity + 2;
}
