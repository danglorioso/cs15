/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 *
 * Edited by: Dan Glorioso
 * CS15: HW 01
 * Date: 09/15/2023
 * Purpose: To test the CharArrayList class and its functions using the
 *          unit_test framework. 
 *
 */
#include "CharArrayList.h"
#include <cassert>

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */

/*insertAt*/

// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 

    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
    
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 9);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() == "[CharArrayList of size 10 <<yabczdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 10);  

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharArrayList of size 11 <<yabczdefghx>>]"); 

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() == "[CharArrayList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}

/*CharArrayList()*/
// Tests that the default constructor creates an empty list.
void default_constructor_empty() {
    CharArrayList test_list;

    assert(test_list.size() == 0);
    assert(test_list.isEmpty());
}

/*CharArrayList(char c)*/
// Tests the constructor with a single variable
void single_variable_constructor() {
    CharArrayList test_list('a');

    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');
}

/*CharArrayList(char arr[], int size)*/
// Tests the constructor with an array of chars
void array_constructor() {
    char test_arr[6] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    CharArrayList test_list(test_arr, 6);

    assert(test_list.size() == 6);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');    
    assert(test_list.elementAt(5) == 'f');    
}

/*CharArrayList(const CharArrayList &other)*/
// Tests if the copy constructor creates a new list with the same elements
void copy_constructor() {
    char test_arr[6] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    CharArrayList test_list1(test_arr, 6);
    CharArrayList test_list2(test_list1);

    assert(test_list2.size() == 6);
    assert(test_list2.elementAt(0) == 'a');
    assert(test_list2.elementAt(1) == 'b');
    assert(test_list2.elementAt(2) == 'c');
    assert(test_list2.elementAt(3) == 'd');
    assert(test_list2.elementAt(4) == 'e');    
    assert(test_list2.elementAt(5) == 'f');    
}

/*~CharArrayList()*/
// // Tests the destructor by creating a list and then deleting it
// void destructor_test() {
//     // create a list
//     CharArrayList test_list('a');

//     // delete the list
//     test_list.~CharArrayList();

//     assert(test_list.size() == 0);
// }

/*std::string toString()*/
// Tests the toString function by creating a list and then calling toString
void toString_test_word() {
    char test_arr[5] = { 'A', 'l', 'i', 'c', 'e' };
    CharArrayList test_list(test_arr, 5);

    assert(test_list.toString() == "[CharArrayList of size 5 <<Alice>>]");
}

void toString_test_char() {
    CharArrayList test_list('d');

    assert(test_list.toString() == "[CharArrayList of size 1 <<d>>]");
}

// Tests the toString function with an empty list
void toString_empty_test() {
    CharArrayList test_list;

    assert(test_list.toString() == "[CharArrayList of size 0 <<>>]");
}

/*std::string toReverseString()*/
// Tests the toReverseString function by creating a list and then calling
// toReverseString
void toReverseString_test_word() {
    char test_arr[5] = { 'A', 'l', 'i', 'c', 'e' };
    CharArrayList test_list(test_arr, 5);

    assert(test_list.toReverseString() ==
                                     "[CharArrayList of size 5 <<ecilA>>]");
}

// Tests the toReverseString function with an empty list
void toReverseString_empty_test() {
    CharArrayList test_list;

    assert(test_list.toReverseString() == "[CharArrayList of size 0 <<>>]");
}

/*int size()*/
// Tests the size function by creating a list and then calling size
void size_test_valid() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);

    assert(test_list.size() == 5);
}

// Tests the size function with an empty list
void size_test_empty() {
    CharArrayList test_list;

    assert(test_list.size() == 0);
}

/*bool isEmpty()*/
// Tests the isEmpty function by creating a list and then calling isEmpty
void isEmpty_test_valid() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);

    assert(!test_list.isEmpty());
}

// Tests the isEmpty function with an empty list
void isEmpty_test_empty() {
    CharArrayList test_list;

    assert(test_list.isEmpty());
}

/*char elementAt(int index)*/
// Tests the elementAt function by creating a list and then calling elementAt
void elementAt_test_valid() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
}

// Tests the elementAt function with an empty list
void elementAt_test_empty() {
    CharArrayList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.elementAt(2);
    }
    catch (const std::range_error &e) {
    // if elementAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..0)");
}

// Test the elementAt function with an out of range index
void elementAt_test_outofrange() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    //check for element at index 6
    try {
        test_list.elementAt(6);
    }
    catch (const std::range_error &e) {
    // if elementAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..5)");
}

/*void pushAtBack(char c)*/
// Tests the pushAtBack function by creating a list and then calling pushAtBack
void pushAtBack_test_valid() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.pushAtBack('f');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 6);
}

// Test the pushAtBack function to add a character to the end of an empty list
void pushAtBack_empty_test() {
    CharArrayList test_list;
    test_list.pushAtBack('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.size() == 1);
}

// Tests the pushAtBack function by adding an element to the end of the list
// and then trying to access an element out of range
void pushAtBack_test_outofrange() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    //check for element at index 6
    try {
        test_list.pushAtBack('f');
        test_list.elementAt(6);
    }
    catch (const std::range_error &e) {
    // if elementAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..6)");
}

// Tests the pushAtBack function by adding multiple elements to the 
// end of the list and ensuring they are in the correct order. Start with
// an empty list.
void pushAtBack_multiple_startEmpty() {
    CharArrayList test_list;
    test_list.pushAtBack('a');
    test_list.pushAtBack('b');
    test_list.pushAtBack('c');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.size() == 3);
}

// Tests the pushAtBack function by adding multiple elements to the 
// end of the list and ensuring they are in the correct order. Start with
// exising elements in the list.
void pushAtBack_multiple_startExisting() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.pushAtBack('f');
    test_list.pushAtBack('g');
    test_list.pushAtBack('h');

    assert(test_list.elementAt(5) == 'f');
    assert(test_list.elementAt(6) == 'g');
    assert(test_list.elementAt(7) == 'h');
    assert(test_list.size() == 8);
}

/*void pushAtFront(char c)*/
// Tests the pushAtFront function by creating a list and then 
// calling pushAtFront to add an element to the front of the list
void pushAtFront_test_valid() {
    char test_arr[5] = { 'b', 'c', 'd', 'e', 'f' };
    CharArrayList test_list(test_arr, 5);
    test_list.pushAtFront('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.size() == 6);
}

// Tests the pushAtFront function by adding an element to the front of
// an empty list
void pushAtFront_empty_test() {
    CharArrayList test_list;
    test_list.pushAtFront('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.size() == 1);
}

// Tests the pushAtFront function by adding an element to the front of
// a list with existing elements
void pushAtFront_exisiting_test() {
    char test_arr[5] = { 'b', 'c', 'd', 'e', 'f' };
    CharArrayList test_list(test_arr, 5);
    test_list.pushAtFront('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.size() == 6);
}

/*void insertAt(char c, int index)*/
// Tests the insertAt function by creating a list and then calling insertAt
void insertAt_test_valid() {
    char test_arr[4] = { 'a', 'b', 'd', 'e' };
    CharArrayList test_list(test_arr, 4);
    test_list.insertAt('c', 2);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests the insertAt function by adding an element to the front of
// an empty list
void insertAt_empty_test() {
    CharArrayList test_list;
    test_list.insertAt('a', 0);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.size() == 1);
}

// Tests the insertAt function by adding an element to the front of an
// existing list
void insertAt_front_test() {
    char test_arr[4] = { 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 4);
    test_list.insertAt('a', 0);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.size() == 5);
}

// Tests the insertAt function by adding an element to the back of an 
// existing list
void insertAt_back_test() {
    char test_arr[4] = { 'a', 'b', 'c', 'd' };
    CharArrayList test_list(test_arr, 4);
    test_list.insertAt('e', 4);

    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

/*void removeAt(int index)*/
// Tests if removeAt removes the element in the middle of an existing list
void removeAt_middle_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.removeAt(2);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.size() == 4);
}

// Tests if removeAt removes the element at the front of an existing list
void removeAt_first_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.removeAt(0);

    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.size() == 4);
}

// Tests if removeAt removes the element at the back of an exisitng list
void removeAt_last_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.removeAt(4);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.size() == 4);
}

// Tests if removeAt removes an element that doesn't exist in an empty list
void removeAt_nonexistent() {
    CharArrayList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.removeAt(2);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..0)");
}

// Tests if removeAt removes an element that is beyond the range of an existing
// list
void removeAt_beyondRange() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.removeAt(5);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..5)");
}

/*void replaceAt(char c, int index)*/
// Tests if replaceAt replaces the element in the middle of an existing list
void replaceAt_middle_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.replaceAt('f', 2);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'f');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if replaceAt replaces the first element in an existing list
void replaceAt_first_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.replaceAt('f', 0);

    assert(test_list.elementAt(0) == 'f');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if replaceAt replaces the last element in an existing list
void replaceAt_last_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);
    test_list.replaceAt('f', 4);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'f');
    assert(test_list.size() == 5);
}

// Tests if replaceAt replaces an element that doesn't exist in an empty list
void replaceAt_nonexistent() {
    CharArrayList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.replaceAt('a', 2);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..0)");
}

// Tests if replaceAt replaces an element that is beyond the range of an 
// existing list
void replaceAt_beyondRange() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.replaceAt('f', 5);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..5)");
}

/*void clear()*/
// Tests if clear clears an existing list
void clear_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);

    test_list.clear();

    assert(test_list.size() == 0);
}

// Tests if clear clears an empty list
void clear_emptyList_test() {
    CharArrayList test_list;

    test_list.clear();

    assert(test_list.size() == 0);
}

// Tests if isEmpty is true after clearing an existing list
void clear_isEmpty_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 5);

    test_list.clear();

    assert(test_list.isEmpty());
}

// Tests if isEmpty is true after clearing an empty list
void clear_isEmpty_emptyList() {
    CharArrayList test_list;

    test_list.clear();

    assert(test_list.isEmpty());
}

/*char first()*/
// Tests if first returns the first element of an existing list
void first_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr,5);

    assert(test_list.first() == 'a');
}

// Tests if first returns the first element of an empty list
void first_test_empty() {
    CharArrayList test_list;

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.first();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");
}

// Tests if the first returns the first element of any empty list when a
// one element list is created and then removed
void first_test_removeEmpty() {
    CharArrayList test_list('a');
    test_list.removeAt(0);

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.first();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");
}

/*char last()*/
// Tests if last returns the last element of an existing list
void last_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr,5);

    assert(test_list.last() == 'e');
}

// Tests if last returns the last element of an empty list
void last_test_empty() {
    CharArrayList test_list;

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");
}

// Tests if the last returns the last element of any empty list when a
// one element list is created and then removed
void last_test_removeEmpty() {
    CharArrayList test_list('a');
    test_list.removeAt(0);

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");
}

/*void popFromFront()*/
// Tests if popFromFront removes the first element of an existing list
void popFromFront_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr,5);

    test_list.popFromFront();

    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.size() == 4);
}

// Tests if popFromFront removes the first element of an empty list
void popFromFront_empty() {
    CharArrayList test_list;

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

// Tests if popFromFront removes the first element of a list with only
// one element
void popFromFront_single() {
    CharArrayList test_list('a');
    test_list.popFromFront();

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

// Tests if popFromFront removes the only element of a list that only
// contains one element that is removed
void popFromFront_removeEmpty() {
    CharArrayList test_list('a');
    test_list.removeAt(0);

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

/*void popFromBack()*/
// Tests if popFromBack removes the last element of an existing list
void popFromBack_test() {
    char test_arr[5] = { 'a', 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr,5);

    test_list.popFromBack();

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.size() == 4);
}

// Tests if popFromBack removes the last element of an empty list
void popFromBack_empty() {
    CharArrayList test_list;

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

// Tests if popFromBack removes the last element of a list with only
// one element to start
void popFromBack_single() {
    CharArrayList test_list('a');
    test_list.popFromBack();

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

// Test if popFromBack removes the only element of a list that only
// contains one element that is removed
void popFromBack_removeEmpty() {
    CharArrayList test_list('a');
    test_list.removeAt(0);

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

/*void insertInOrder(char c)*/
// Tests if insertInOrder inserts an element in the middle of an existing list
// that is in alphebtical order
void insertInOrder_middle_test() {
    char test_arr[4] = { 'a', 'b', 'd', 'e' };
    CharArrayList test_list(test_arr, 4);
    test_list.insertInOrder('c');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if insertInOrder inserts an element at the front of an existing list
void insertInOrder_first_test() {
    char test_arr[4] = { 'b', 'c', 'd', 'e' };
    CharArrayList test_list(test_arr, 4);
    test_list.insertInOrder('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if insertInOrder inserts an element at the end of an existing list
void insertInOrder_end_test() {
    char test_arr[4] = { 'a', 'b', 'c', 'd' };
    CharArrayList test_list(test_arr, 4);
    test_list.insertInOrder('e');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if insertInOrder inserts an element into an empty list
void insertInOrder_empty() {
    CharArrayList test_list;
    test_list.insertInOrder('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.size() == 1);
}

 /*concatenate(CharArrayList *other)*/
 // Tests if concatenate concatenates two lists together
 void concatenate_basic_test() {
        //CharArrayListOne contains "cat"
        char test_arr1[3] = {'c', 'a', 't'};
        CharArrayList CharArrayListOne(test_arr1, 3);
        //CharArrayListTwo contains "CHESHIRE"
        char test_arr2[8] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
        CharArrayList CharArrayListTwo(test_arr2, 8);

        //asert that the concatenated list is "catCHESHIRE"
        //and that the size is 11
        CharArrayListOne.concatenate(&CharArrayListTwo);
        assert(CharArrayListOne.toString() == 
                                "[CharArrayList of size 11 <<catCHESHIRE>>]");
 }

 // Tests if concatenate concatenates an empty array list with a second array 
 // list 
void concatenate_second_empty_test() {
    CharArrayList CharArrayListOne;
    
    //CharArrayListTwo contains "CHESHIRE"
    char test_arr2[8] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharArrayList CharArrayListTwo(test_arr2, 8);

    CharArrayListOne.concatenate(&CharArrayListTwo);
    assert(CharArrayListOne.toString() ==
                                     "[CharArrayList of size 8 <<CHESHIRE>>]");
}

// Tests if concatenate concatenates two empty array lists
void concatenate_two_empty() {
    CharArrayList CharArrayListOne;
    CharArrayList CharArrayListTwo;

    CharArrayListOne.concatenate(&CharArrayListTwo);
    assert(CharArrayListOne.toString() == "[CharArrayList of size 0 <<>>]");
}

// Tests if concatenate concatenates an array list with an empty array list
void concaternate_first_empty_test() {
    //CharArrayListOne contains "cat"
    char test_arr1[3] = {'c', 'a', 't'};
    CharArrayList CharArrayListOne(test_arr1, 3);

    CharArrayList CharArrayListTwo;

    CharArrayListOne.concatenate(&CharArrayListTwo);
    assert(CharArrayListOne.toString() == 
                                    "[CharArrayList of size 3 <<cat>>]");
}

//Tests if concatenate concatenates two of the same array
void concaternate_same_list() {
    char test_arr1[8] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharArrayList CharArrayListTwo(test_arr1, 8);

    CharArrayListTwo.concatenate(&CharArrayListTwo);
    assert(CharArrayListTwo.toString() == 
                            "[CharArrayList of size 16 <<CHESHIRECHESHIRE>>]");
}

/*&operator=(const CharArrayList &other)*/
// Tests if the assignment operator works with two different lists
void copy_operator_different_test() {
    //CharArrayListOne contains "cat"
    char test_arr1[3] = {'c', 'a', 't'};
    CharArrayList CharArrayListOne(test_arr1, 3);
    //CharArrayListTwo contains "CHESHIRE"
    char test_arr2[8] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharArrayList CharArrayListTwo(test_arr2, 8);

    CharArrayListOne = CharArrayListTwo;
    assert(CharArrayListOne.toString() == 
                                    "[CharArrayList of size 8 <<CHESHIRE>>]");
}

// Tests if the assignment operator works with two of the same lists
void copy_operator_same_test() {
    //CharArrayListOne contains "cat"
    char test_arr1[3] = {'c', 'a', 't'};
    CharArrayList CharArrayListOne(test_arr1, 3);

    CharArrayListOne = CharArrayListOne;
    assert(CharArrayListOne.toString() == 
                                    "[CharArrayList of size 3 <<cat>>]");
}
