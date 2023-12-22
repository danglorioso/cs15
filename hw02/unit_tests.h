/*
 *  unit_tests.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/21/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  PURPOSE:  To test the CharLinkedList class and its function using the 
 *            unit_test framework. 
 *
 */

#include "CharLinkedList.h"
#include <cassert>

/*Dummy Test*/
// Tests that the unit_tests is working
void dummy_test() {
    assert(true);
}

/*CharLinkedList()*/
// Tests that the default constructor creates an empty list.
void default_constructor_empty() {
    CharLinkedList list;
    assert(list.isEmpty());
} 

/*CharLinkedList(char c)*/
// Tests the constructor with a single variable
void single_variable_constructor() {
    CharLinkedList test_list('a');
    assert(not test_list.isEmpty());
}

/*CharLinkedList(char arr[], int size)*/
// Tests the constructor with an array of characters
void constructor_array_test() {
    char arr[] = {'a', 'b', 'c'};
    CharLinkedList test_list(arr, 3);
    assert(not test_list.isEmpty());
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.size() == 3);
}

// Tests the construcotr with an empty array
void constructor_array_empty() {
    char arr[] = {};
    CharLinkedList test_list(arr, 0);
    assert(test_list.isEmpty());
}

/*CharLinkedList(const CharLinkedList &other)*/
// Tests if the copy constructor creates a new list with the same elements
void copy_constructor() {
    char arr[] = {'a', 'b', 'c'};
    CharLinkedList test_list(arr, 3);
    CharLinkedList test_list_copy(test_list);
    assert(test_list_copy.elementAt(0) == 'a');
    assert(test_list_copy.elementAt(1) == 'b');
    assert(test_list_copy.elementAt(2) == 'c');
    assert(test_list_copy.size() == 3);
}

// Tests if the copy constructor creates a new list with the same elements,
// starting with an empty list
void copy_constructor_emptylist() {
    CharLinkedList test_list;
    CharLinkedList test_list_copy(test_list);
    assert(test_list_copy.isEmpty());
}

/*int size()*/
// Tests that size() returns 0 when the list is empty
void size_test_empty() {
    CharLinkedList test_list;
    assert(test_list.size() == 0);  
}

// Tests that size() returns the correct size when the list is not empty
void size_test_not_empty() {
    CharLinkedList test_list('a');
    assert(test_list.size() == 1);
}

/*bool isEmpty()*/
// Tests that isEmpty() returns true when the list is empty
void isEmpty_test_empty() {
    CharLinkedList test_list;
    assert(test_list.isEmpty());
}

//Tests that isEmpty() returns false when the list is not empty
void isEmpty_test_fail() {
    CharLinkedList test_list('a');
    assert(not test_list.isEmpty());
}

/*char elementAt(int index)*/
// Tests the elementAt function by creating a list of one element and then 
// calling elementAt
void elementAt_test() {
    CharLinkedList test_list('a');
    assert(test_list.elementAt(0) == 'a');
}

// Tests the elemenAt function by creating a list and then calling elementAt
// at an index that is out of range
void elementAt_out_of_range_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.elementAt(6);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..5)");
}

// Tests the element at function with a list of one element and then calling
// elementAt at an index that is out of range
void elementAt_singleton_out_of_range_test() {
    CharLinkedList test_list('a');
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.elementAt(2);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..1)");
}

// Tests the elementAt function with an empty list and then calling elementAt
// at an index that is out of range
void elementAt_empty_test() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.elementAt(2);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..0)");
}   

// Tests the elementAt function by creating a list of multiple element and
// then calling elementAt
void elementAt_many_test() {
    // CharLinkedList list('a');
    // list.pushAtBack('b');
    // list.pushAtBack('c');
    // assert(list.elementAt(0) == 'a');
    // assert(list.elementAt(1) == 'b');
    // assert(list.elementAt(2) == 'c');
}

/*std::string toString()*/
// Tests the toString function by creating a list of one element and then
// calling toString
void toString_one_test() {
    CharLinkedList test_list('d');
    assert(test_list.toString() == "[CharLinkedList of size 1 <<d>>]");
}

// Tests the toString function with an empty list
void toString_empty_test() {
    CharLinkedList test_list;
    assert(test_list.toString() == "[CharLinkedList of size 0 <<>>]");
}

// Tests the toString function with a list of multiple elements
void toString_test_words() {
    char arr[] = { 'A', 'l', 'i', 'c', 'e' };
    CharLinkedList test_list(arr, 5);
    assert(test_list.toString() == "[CharLinkedList of size 5 <<Alice>>]");
}

/*void pushAtBack(char c)*/
// Tests the pushAtBack function by creating a list of one element and then
// calling pushAtBack
void pushAtBack_one_test() {
    CharLinkedList test_list('a');
    test_list.pushAtBack('b');
    assert(test_list.elementAt(1) == 'b');
}

// Tests the pushAtBack function by creating a list of multiple elements and
// then calling pushAtBack
void pushAtBack_multiple_test() {
    CharLinkedList test_list('a');
    test_list.pushAtBack('b');
    test_list.pushAtBack('c');
    assert(test_list.elementAt(2) == 'c');
}

// Tests the pushAtBack function by creating an empty list and then calling
// pushAtBack
void pushAtBack_empty_test() {
    CharLinkedList test_list;
    test_list.pushAtBack('a');
    assert(test_list.elementAt(0) == 'a');
}

// Tests the pushAtBack function by adding an element to the end of the list
// and then trying to access an element out of range
void pushAtBack_test_outofrange() {
    char arr[] = {'a', 'b', 'c'};
    CharLinkedList test_list(arr, 3);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.pushAtBack('d');
        test_list.elementAt(7);
    } catch (std::range_error &e) {
        //if implementation is correct, a range_error will be thrown
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (7) not in range [0..4)");
}

// Tests the pushAtBack function by adding multiple elements to the end of the
// list and ensuring they are in the correct order. Start with an empty list.
void pushAtBack_multiple_startEmpty() {
    CharLinkedList test_list;
    test_list.pushAtBack('a');
    test_list.pushAtBack('b');
    test_list.pushAtBack('c');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.size() == 3);
}

// Tests the pushAtBack function by adding multiple elements to the end of the
// list and ensuring they are in the correct order. Start with existing
// elements in the list. 
void pushAtBack_mutliple_startExisting() {
    char arr[] = {'a', 'b', 'c'};
    CharLinkedList test_list(arr, 3);
    test_list.pushAtBack('d');
    test_list.pushAtBack('e');
    test_list.pushAtBack('f');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

/*void pushAtFront(char c)*/
// Test the pushAtFront function by creating a list and then
// calling pushAtFront to add an element to the front of the list
void pushAtFront_test_valid() {
    char arr[] = {'b', 'c', 'd', 'e', 'f'};
    CharLinkedList test_list(arr, 5);
    test_list.pushAtFront('a');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests the pushAtFront function by creating an empty list and then calling
// pushAtFront to add an element to the front of the list
void pushAtFront_empty_test() {
    CharLinkedList test_list;
    test_list.pushAtFront('a');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.size() == 1);
}

// Tests the pushAtFront function by adding an element to the front of a list
// with one existing element
void pushAtFront_one_test() {
    CharLinkedList test_list('b');
    test_list.pushAtFront('a');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<ab>>]");
    assert(test_list.size() == 2);
}

/*void insertAt(char c, int index)*/
// Tests the insertAt function by creating a list and then calling insertAt
void insertAt_test_valid() {
    char arr[] = {'a', 'b', 'd', 'e', 'f'};
    CharLinkedList test_list(arr, 5);
    test_list.insertAt('c', 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests the insertAt function by adding an element to the front of any empty
// list
void insertAt_empty_test() {
    CharLinkedList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.size() == 1);
}

// Tests the isnertAt function by adding an element to the front of an 
// existing list
void insertAt_front_test() {
    char arr[] = {'b', 'c', 'd', 'e', 'f'};
    CharLinkedList test_list(arr, 5);
    test_list.insertAt('a', 0);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests the insertAt function by adding an element to the back of an
// existing list
void insertAt_back_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.insertAt('f', 5);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests the insertAt function by adding an element to the middle of an
// existing list
void insertAt_middle_list() {
    char arr[] = {'a', 'b', 'c', 'd', 'f'};
    CharLinkedList test_list(arr, 5);
    test_list.insertAt('e', 4);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests the insertAt function by adding an element to the front of a list
// with one existing element
void insertAt_front_singleton_list() {
    CharLinkedList test_list('b');
    test_list.insertAt('a', 0);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<ab>>]");
    assert(test_list.size() == 2);
}

// Tests correct error handling by trying to insert an element at an index
// that is out of range of an existing list
void insertAt_outofrange_existing() {
    char arr[] = {'a', 'b', 'd'};
    CharLinkedList test_list(arr, 3);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.insertAt('c', 5);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..3]");
}

// Tests correct error handling by trying to insert an element at an index 
// that is out of range of an empty list
void insertAt_outofrange_empty() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.insertAt('a', 1);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (1) not in range [0..0]");
}

/*void popFromFront()*/
// Tests if popFromFront removes the first element of an existing list
void popFromFront_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.popFromFront();
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.toString() == "[CharLinkedList of size 4 <<bcde>>]");
    assert(test_list.size() == 4);
}

// Tests if popFromFront removes the first element of an empty list
void popFromFront_empty()
{
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromFront();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

// Tests if popFromFront removes the first element of a list with only 
// one element
void popFromFront_singleton() {
    CharLinkedList test_list('a');
    test_list.popFromFront();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

// Tests if popFromFront removes the first element of a list that only
// contains one element that is removed
void popFromFront_removeEmpty() {
    char arr[] = {'a'};
    CharLinkedList test_list (arr, 1);
    test_list.removeAt(0);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromFront();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

/*void popFromBack()*/
// Tests if popFromBack removes the last element of an existing list
void popFromBack_existing() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.popFromBack();
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.size() == 4);
}

// Tests if popFromBack removes the last element of an empty list
void popFromBack_empty() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromBack();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

// Tests if popfromBack removes the last element of a list with only
// one element to start
void popFromBack_singleton() {
    CharLinkedList test_list('a');
    test_list.popFromBack();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

// Tests if popFromBack removes the last element of a list with only one
// elements to start
void popFromBack_single() {
    CharLinkedList test_list('a');
    test_list.popFromBack();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

// Tests if popFromBack removes the last element of a list that only 
// contains one element that is removed
void popFromBack_removeEmpty() {
    CharLinkedList test_list('a');
    test_list.removeAt(0);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromBack();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

/*void removeAt(int index)*/
// Tests if removeAt removes the element at the front of an existing list
void removeAt_first_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.removeAt(0);

    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.size() == 4);
}

// Tests if removeAt removes the element in the middle of an existing list
void removeAt_middle_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.removeAt(2);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.size() == 4);
}

// Tests if removeAt removes the element at the back of an existing list
void removeAt_back_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.removeAt(4);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.size() == 4);
}

// Tests if removeAt removes an element that doesn't exist in an empty list
void removeAt_nonexistent() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.removeAt(0);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

// Tests if removeAt removes an element that is out of the range of the
// existing list. 
void removeAt_beyondRange() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.removeAt(5);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (5) not in range [0..5)");
}

/*void replaceAt(char c, int index)*/
// Tests if replaceAt replaces the element at the front of an existing list
void replaceAt_front() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.replaceAt('z', 0);

    assert(test_list.elementAt(0) == 'z');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if replaceAt replaces the element in the middle of an existin list
void replaceAt_middle() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.replaceAt('z', 2);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'z');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.size() == 5);
}

// Tests if replaceAt replaces the last element in an exisitng list
void replaceAt_last() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.replaceAt('z', 4);

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'z');
    assert(test_list.size() == 5);
}

// Tests if replaceAt replaces an element that doesn't exist in an empty list
void replaceAt_nonexistent() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.replaceAt('z', 6);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..0)");
}

// Tests if replaceAt replaces an element that is out of the range of the
void replaceAt_beyondRange() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.replaceAt('z', 6);
    } catch (std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (6) not in range [0..5)");
}

/*void clear()*/
// Tests if clear clears an existing list
void clear_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.clear();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

// Tests if clear clears an empty list
void clear_empty_test() {
    CharLinkedList test_list;
    test_list.clear();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

// Tests if isEmpty returns true after clear is called on an existing list
void clear_isEmpty_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.clear();
    assert(test_list.isEmpty());
}

// Tests if isEmpty returns true after clear is called on an empty list
void clear_isEmpty_emptyList() {
    CharLinkedList test_list;
    test_list.clear();
    assert(test_list.isEmpty());
}

/*char first()*/
// Tests if first returns the first element of an existing list
void first_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);

    assert(test_list.first() == 'a');
}

// Tests if first returns the first element of an empty list
void first_test_empty() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.first();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

// Tests if first returns the first element of any empty lsit when a one 
// element list is created and then removed
void first_test_removeEmpty() {
    CharLinkedList test_list('a');
    test_list.removeAt(0);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.first();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

/*char last()*/
// Tests if last returns the last element of an existing list
void last_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);

    assert(test_list.last() == 'e');
}

// Tests if last returns the last element of an empty list
void last_test_empty() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.last();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
}

// Tests if last returns the alst element of any empty list when a one element
// list is created and then removed
void last_test_removeEmpty() {
    CharLinkedList test_list('a');
    test_list.removeAt(0);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.last();
    } catch (std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
}

/*std::string toReverseString()*/
// Tests if toReverseString returns the correct string for an existing list
void toReverseString_test() {
    char arr[] = {'A', 'l', 'i', 'c', 'e'};
    CharLinkedList test_list(arr, 5);

    assert(test_list.toReverseString() == 
                                    "[CharLinkedList of size 5 <<ecilA>>]");
}
// Tests the toReverseString function by creating a list of one element and
// then calling toReverseString
void toReverseString_test_one() {
    CharLinkedList test_list('a');
    assert(test_list.toReverseString() == "[CharLinkedList of size 1 <<a>>]");
}

// Tests if toReverseString returns the correct string for an empty list
void toReverseString_empty_test() {
    CharLinkedList test_list;
    assert(test_list.toReverseString() == "[CharLinkedList of size 0 <<>>]");
}

/*void insertInOrder(char c)*/
// Tests if insertInOrder inserts an element into the middle of an existing 
// list that is in alphabetical order
void insertInOrder_middle_test() {
    char arr[] = {'a', 'b', 'd', 'e', 'f'};
    CharLinkedList test_list(arr, 5);
    test_list.insertInOrder('c');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests if insertInOrder inserts an element at the front of an existing list
void insertInOrder_front_test() {
    char arr[] = {'b', 'c', 'd', 'e', 'f'};
    CharLinkedList test_list(arr, 5);
    test_list.insertInOrder('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests if insertInOrder inserts an element at the back of an existing list
void insertInOrder_back_test() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    CharLinkedList test_list(arr, 5);
    test_list.insertInOrder('f');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'd');
    assert(test_list.elementAt(4) == 'e');
    assert(test_list.elementAt(5) == 'f');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(test_list.size() == 6);
}

// Tests if insertInOrder inserts an element into an existing list that is not
// in alphabetical order
void insertInOrder_unordered() {
    char arr[] = {'Z', 'E', 'D'};
    CharLinkedList test_list(arr, 3);
    test_list.insertInOrder('A');

    assert(test_list.elementAt(0) == 'A');
    assert(test_list.elementAt(1) == 'Z');
    assert(test_list.elementAt(2) == 'E');
    assert(test_list.elementAt(3) == 'D');
    assert(test_list.toString() == "[CharLinkedList of size 4 <<AZED>>]");
    assert(test_list.size() == 4);
}

// Tests if insertInOrder inserts an element into an empty list
void insertInOrder_empty() {
    CharLinkedList test_list;
    test_list.insertInOrder('a');

    assert(test_list.elementAt(0) == 'a');
    assert(test_list.toString() == "[CharLinkedList of size 1 <<a>>]");
    assert(test_list.size() == 1);
}

/*CharLinkedList &operator=(const CHarLinkedList &other)*/
// Tests if the assignment operator works with two different lists
void copy_operator_different_test() {
    //CharLinkedListOne contains "cat"
    char arr[] = {'c', 'a', 't'};
    CharLinkedList CharLinkedListOne(arr, 3);
    //CharLinkedListTwo contains "CHESHIRE"
    char arr2[] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharLinkedList CharLinkedListTwo (arr2, 8);

    CharLinkedListOne = CharLinkedListTwo;
    assert(CharLinkedListOne.toString() == 
                                    "[CharLinkedList of size 8 <<CHESHIRE>>]");

}

// Tests if the assignment operator works with two identical lists
void copy_operator_same_test() {
    //CharLinkedListOne contains "cat"
    char arr[] = {'c', 'a', 't'};
    CharLinkedList CharLinkedListOne(arr, 3);

    CharLinkedListOne = CharLinkedListOne;
    assert(CharLinkedListOne.toString() == 
                                        "[CharLinkedList of size 3 <<cat>>]");
}

/*void concatenate(CharLinkedList *other)*/
// Tests if concatenate concatenates two lists together
void concatenate_basic_test() {
    //CharLinkedListOne contains "cat"
    char arr[] = {'c', 'a', 't'};
    CharLinkedList CharLinkedListOne(arr, 3);
    //CharLinkedListTwo contains "CHESHIRE"
    char arr2[] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharLinkedList CharLinkedListTwo (arr2, 8);

    //assert that the concatenated list is "catCHESHIRE" and 
    //that the size is 11
    CharLinkedListOne.concatenate(&CharLinkedListTwo);
    assert(CharLinkedListOne.toString() == 
                                "[CharLinkedList of size 11 <<catCHESHIRE>>]");
}

// Tests if concatenate concatenates an empty array list with a second list
void concatenate_second_empty_test() {
    //CharLinkedListOne is empty
    CharLinkedList CharLinkedListOne;
    //CharLinkedListTwo is "CHESHIRE"
    char arr2[] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharLinkedList CharLinkedListTwo (arr2, 8);

    //assert that the concatenated list is "cat" and that the size is 3
    CharLinkedListOne.concatenate(&CharLinkedListTwo);
    assert(CharLinkedListOne.toString() == 
                                    "[CharLinkedList of size 8 <<CHESHIRE>>]");
}

// Tests if concatenate concatenates two empty array lists
void concatenate_two_empty() {
    CharLinkedList CharLinkedListOne;
    CharLinkedList CharLinkedListTwo;

    CharLinkedListOne.concatenate(&CharLinkedListTwo);
    assert(CharLinkedListOne.toString() == "[CharLinkedList of size 0 <<>>]");
}

// Tests if concatenate concatenates an array list with an empty array list
void concaternate_first_empty_test() {
    //CharLinkedListOne contains "cat"
    char arr[] = {'c', 'a', 't'};
    CharLinkedList CharLinkedListOne(arr, 3);
    //CharLinkedListTwo is empty
    CharLinkedList CharLinkedListTwo;

    CharLinkedListOne.concatenate(&CharLinkedListTwo);
    assert(CharLinkedListOne.toString() == 
                                        "[CharLinkedList of size 3 <<cat>>]");
}

// Tests if concatenate concatenates two of the same array
void concatenate_same_list() {
    //CharLinkedListOne contains "CHESHIRE"
    char arr[] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharLinkedList CharLinkedListOne(arr, 8);

    CharLinkedListOne.concatenate(&CharLinkedListOne);
    assert(CharLinkedListOne.toString() == 
                         "[CharLinkedList of size 16 <<CHESHIRECHESHIRE>>]");
}
