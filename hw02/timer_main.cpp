/*
 * timer_main.cpp
 *
 * CS 15 homework 2
 * by Milod Kazerounian, July 2022
 *
 * A driver program for timing various CharLinkedList operations.
 * Once you have completed your CharLinkedList implementation, 
 * from terminal run "make timer" to compile an executable
 * from this driver. Run the executable to view a table of times.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <utility>
#include <chrono>
#include "CharLinkedList.h"

using namespace std;
using namespace std::chrono;


/**************************
 * TABLE FORMAT CONSTANTS *
 **************************/
const int TABLE_WIDTH       = 70;
const int OP_ENTRY_WIDTH    = 0.75 * TABLE_WIDTH;
const int TIME_ENTRY_WIDTH  = TABLE_WIDTH - OP_ENTRY_WIDTH;
const char HORIZONTAL_SEP   = '-';
const char FILL             = ' ';
const string LINE           = string(TABLE_WIDTH, HORIZONTAL_SEP);

/**************************
 * LIST TESTING CONSTANTS *
 **************************/
const int DEFAULT_LIST_SIZE = 10000; // Reduced from 100,000 to avoid stack overflow seg faults
const int DEFAULT_NUM_OPS   = 100;
const char DUMMY_CHAR = 'a';


/**************************
 * FUNCTION DECLARATIONS  *
 **************************/
template<typename T>
void printEntry(const string action, const T time);
CharLinkedList *generateRandList(const int size);
pair<string, int> pushAtFront_test();
pair<string, int> pushAtBack_test();
pair<string, int> insertAtMiddle_test();
pair<string, int> popFromFront_test();
pair<string, int> popFromBack_test();
pair<string, int> removeAtMiddle_test();
pair<string, int> first_test();
pair<string, int> last_test();
pair<string, int> elementAtMiddle_test();

/*
 * name:    main
 * purpose: runs timing tests and prints table
 * returns: exit code of 0 when run to completion
 */
int main()
{
    srand(time(0));    

    /*****   INSERTION TESTS   *****/
    pair<string, int> pushFront = pushAtFront_test();
    pair<string, int> pushBack = pushAtBack_test();
    pair<string, int> insertMiddle = insertAtMiddle_test();
    /*****   REMOVAL TESTS   *****/
    pair<string, int> popFront = popFromFront_test();
    pair<string, int> popBack = popFromBack_test();
    pair<string, int> removeMiddle = removeAtMiddle_test();
    /*****   ACCESS TESTS   *****/
    pair<string, int> first = first_test();
    pair<string, int> last = last_test();
    pair<string, int> middle = elementAtMiddle_test();

    cout << "\nAll operations below are run on a separate, randomly generated\n"
         << "CharLinkedList of size "  << DEFAULT_LIST_SIZE <<".\n\n";

    /*****   PRINT TABLE   *****/
    cout << LINE << endl;
    printEntry("INSERTION OPERATION", "Time (nanoseconds)");
    cout << LINE << endl;
    printEntry(pushFront.first, pushFront.second);
    cout << LINE << endl;
    printEntry(pushBack.first, pushBack.second);
    cout << LINE << endl;
    printEntry(insertMiddle.first, insertMiddle.second);
    cout << LINE << endl;
    printEntry("REMOVAL OPERATION", "Time (nanoseconds)");
    cout << LINE << endl;
    printEntry(popFront.first, popFront.second);
    cout << LINE << endl;
    printEntry(popBack.first, popBack.second);
    cout << LINE << endl;
    printEntry(removeMiddle.first, removeMiddle.second);
    cout << LINE << endl;
    printEntry("ACCESS OPERATION", "Time (nanoseconds)");
    cout << LINE << endl;
    printEntry(first.first, first.second);
    cout << LINE << endl;
    printEntry(last.first, last.second);
    cout << LINE << endl;
    printEntry(middle.first, middle.second);
    cout << LINE << endl;
    
    return 0;
}

/*
 * name:      printEntry
 * purpose:   prints a single line of table
 * arguments: a string action (first entry in line)
 *            an int or string time (second entry in line)
 * notes:     uses table formatting constants defined at top of this file
 */
template<typename T>
void printEntry(const string action, const T time)
{
    cout << left << setw(OP_ENTRY_WIDTH) << setfill(FILL) << action;
    cout << left << setw(TIME_ENTRY_WIDTH) << setfill(FILL) << time << endl;
}

/*
 * name:      generateRandList
 * purpose:   generates a CharLinkedList of random elements
 * arguments: const int size of list to generate
 * returns:   pointer to the new heap-allocated CharLinkedList
 * effects:   allocates CharLinkedList on heap
 */
CharLinkedList *generateRandList(const int size)
{
    CharLinkedList *list = new CharLinkedList;

    for(int i = 0; i < size; i++) {
        // rand() will generate a random int. The mod operation will
        // put it in range [0, 255]. In C++, ints translate into chars
        // of the corresponding ASCII number.
        list->pushAtBack(rand() % 256);
    }

    return list;
}

/*
 * name:    pushAtFront_test
 * purpose: time how long it takes to push DEFAULT_NUM_OPS elements 
 *          to front of list
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> pushAtFront_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->pushAtFront(DUMMY_CHAR);
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("pushAtFront " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    pushAtBack_test
 * purpose: time how long it takes to push DEFAULT_NUM_OPS elements 
 *          to back of list
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> pushAtBack_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->pushAtBack(DUMMY_CHAR);
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("pushAtBack " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    insertAtMiddle_test
 * purpose: time how long it takes to insert DEFAULT_NUM_OPS elements 
 *          into middle of list
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> insertAtMiddle_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    // keep track of list size separately so we don't
    // rely on calling size() function, which could impact time complexity
    int curr_size = DEFAULT_LIST_SIZE;

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->insertAt(DUMMY_CHAR, curr_size / 2);
        curr_size++;
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("insertAt middle of list " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    first_test
 * purpose: time how long it takes to call first() on list DEFAULT_NUM_OPS times
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> first_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    // For each list access test, calling once before timing
    // to control for caching.
    list->first();

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->first();
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("call first() " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    first_test
 * purpose: time how long it takes to call last() on list DEFAULT_NUM_OPS times
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> last_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    // For each list access test, calling once before timing
    // to control for caching.
    list->last();
    
    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->last();
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("call last() " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    elementAtMiddle_test
 * purpose: time how long it takes to access middle list element 
 *          DEFAULT_NUM_OPS times
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> elementAtMiddle_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    // For each list access test, calling once before timing
    // to control for caching.    
    list->elementAt(DEFAULT_LIST_SIZE / 2);

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for(int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->elementAt(DEFAULT_LIST_SIZE / 2);
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("call elementAt() for middle of list " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    popFromFront_test
 * purpose: time how long it takes to pop DEFAULT_NUM_OPS elements 
 *          from front of list
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> popFromFront_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->popFromFront();
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("popFromFront " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    popFromBack_test
 * purpose: time how long it takes to pop DEFAULT_NUM_OPS elements 
 *          from back of list
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> popFromBack_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->popFromBack();
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("popFromBack " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}

/*
 * name:    removeAtMiddle_test
 * purpose: time how long it takes to remove DEFAULT_NUM_OPS elements 
 *          from middle of list
 * returns: pair<string, int> where first element is an operation description
 *          for the table, and second element is operaiton time in nanoseconds
 */
pair<string, int> removeAtMiddle_test()
{
    CharLinkedList *list = generateRandList(DEFAULT_LIST_SIZE);

    // keep track of list size separately so we don't
    // rely on calling size() function, which could impact time complexity
    int curr_size = DEFAULT_LIST_SIZE;

    time_point<high_resolution_clock> start = high_resolution_clock::now();
    for (int i = 0; i < DEFAULT_NUM_OPS; i++) {
        list->removeAt(curr_size / 2);
        curr_size--;
    }
    time_point<high_resolution_clock> stop = high_resolution_clock::now();

    pair<string, int> res("removeAt middle of list " +
                          to_string(DEFAULT_NUM_OPS) + " times",
                          duration_cast<nanoseconds>(stop - start).count());
    delete list;
    return res;
}
