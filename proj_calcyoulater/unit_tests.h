/*
 *  unit_tests.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/28/2023
 * 
 *  CS 15 PROJECT 2: CalcYouLater
 * 
 *  PURPOSE: To test the functionality of the DatumStack and parser classes
 *           using the unit_test testing framework.
 * 
 */

#include <iostream>
#include <cassert>
#include <sstream>
#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"
#include "parser.h"

/*Dummy Test*/
// Tests that the unit_tests is working
void dummy_test() {
    assert(true);
}

/********************************************************************\
*                       DATUMSTACK CLASS                              *
\********************************************************************/
/*Default Constuctor*/
// Tests that the default constructor works
void test_DS_default_constr() {
    DatumStack ds;
    assert(ds.isEmpty());
}

/*Array Constuctor*/
// Tests the array constructor with an array of size 1
void test_DS_array_one() {
    Datum data[] = {Datum(1)};
    DatumStack ds(data, 1);
    assert(not ds.isEmpty());
}

// Tests the array constructor with an array of multiple elements
void test_DS_array_multiple() {
    Datum data[] = {Datum(1), Datum(2), Datum(3), Datum(4)};
    DatumStack ds(data, 4);
    assert(not(ds.isEmpty()));
}

// Tests the array constructor with an empty array
void test_DS_array_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);
    assert(ds.isEmpty());
}

/*isEmpty*/
// Tests that isEmpty returns true when the stack is empty
void test_DS_isEmpty_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);
    assert(ds.isEmpty());
}

// Tests that isEmpty returns false when the stack is not empty
void test_DS_isEmpty_not_empty() {
    Datum data[] = {Datum(1), Datum(2)};
    DatumStack ds(data, 2);
    assert(not (ds.isEmpty()));
}

/*clear*/
// Tests that clear empties the stack
void test_DS_clear() {
    Datum data[] = {Datum(1), Datum(2)};
    DatumStack ds(data, 2);
    ds.clear();
    assert(ds.isEmpty());
}

// Tests that clear empties the stack when the stack is empty
void test_DS_clear_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);
    ds.clear();
    assert(ds.isEmpty());
}

/*size*/
// Tests that size returns the correct size of the stack
void test_DS_size() {
    Datum data[] = {Datum(1), Datum(2)};
    DatumStack ds(data, 2);
    assert(ds.size() == 2);
}

// Tests that the size returns the correct size of the stack when the stack 
// is empty
void test_DS_size_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);
    assert(ds.size() == 0);
}

// Tests that the size returns correct when the stack has one element
void test_DS_size_one() {
    Datum data[] = {Datum(1)};
    DatumStack ds(data, 1);
    assert(ds.size() == 1);
}

// Tests that the size returns correct when the stack has multiple elements
void test_DS_size_multiple() {
    Datum data[] = {Datum(6), Datum(2), Datum(3), Datum(4), Datum(5)};
    DatumStack ds(data, 5);
    assert(ds.size() == 5);
}

/*top*/
// Tests that top returns the correct top element
void test_DS_top() {
    Datum data[] = {Datum(1), Datum(2)};
    DatumStack ds(data, 2);
    assert(ds.top().getInt() == Datum(2).getInt());
}

// Tests that top returns the correct top element in a stack with only 
// one element
void test_DS_top_one() {
    Datum data[] = {Datum(1)};
    DatumStack ds(data, 1);
    assert(ds.top().getInt() == Datum(1).getInt());
}

// Tests that top returns the correct top element in a stack of many elements
void test_DS_top_multiple() {
    Datum data[] = {Datum(1), Datum(2), Datum(3), Datum(4), Datum(5)};
    DatumStack ds(data, 5);
    assert(ds.top().getInt() == Datum(5).getInt());
}

// Tests that the correct error message is thrown for an empty stack
void test_DS_top_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        ds.top().getInt();
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

/*pop*/
// Tests that pop removes the top element from the stack
void test_DS_pop() {
    Datum data[] = {Datum(1), Datum(2)};
    DatumStack ds(data, 2);
    ds.pop();
    assert(ds.top().getInt() == Datum(1).getInt());
}

// Tests that pop removes the top element from the stack when the stack has
// only one element
void test_DS_pop_one() {
    Datum data[] = {Datum(1)};
    DatumStack ds(data, 1);
    ds.pop();
    assert(ds.isEmpty());
}

// Tests that pop removes the top element from the stack when the stack has
// multiple elements
void test_DS_pop_multiple() {
    Datum data[] = {Datum(1), Datum(2), Datum(3), Datum(4), Datum(5)};
    DatumStack ds(data, 5);
    ds.pop();
    assert(ds.top().getInt() == Datum(4).getInt());
}

// Tests that the correct error message is thrown for an empty stack
void test_DS_pop_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        ds.pop();
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

/*push*/
// Tests that push adds an element to the stack
void test_DS_push() {
    Datum data[2] = {Datum(1), Datum(2)};
    DatumStack ds(data, 2);
    ds.push(Datum(3));
    assert(ds.top().getInt() == Datum(3).getInt());
}

// Tests that push adds an element to the stack when the stack is empty
void test_DS_push_empty() {
    Datum data[] = {};
    DatumStack ds(data, 0);
    ds.push(Datum(1));
    assert(ds.top().getInt() == Datum(1).getInt());
}

// Tests that push adds an element to the stack when the stack has one element
void test_DS_push_one() {
    Datum data[] = {Datum(1)};
    DatumStack ds(data, 1);
    ds.push(Datum(2));
    assert(ds.top().getInt() == Datum(2).getInt());
}

// Tests that push adds an element to the stack when the stack has multiple
// elements
void test_DS_push_multiple() {
    Datum data[] = {Datum(1), Datum(2), Datum(3), Datum(4), Datum(5)};
    DatumStack ds(data, 5);
    ds.push(Datum(6));
    assert(ds.top().getInt() == Datum(6).getInt());
}

/********************************************************************\
*                            PARSER CLASS                            *
\********************************************************************/
/*string parseRString(std::isteam &input)*/
// Tests that parseRString returns the correct RString with a space in front
void test_parseRString() {
    std::istringstream input(" 1 2 3 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 2 3 }");
}

// Tests that parseRString returns the correct RString with no space in front
void test_parseRString_nospace() {
    std::istringstream input("1 2 3 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 2 3 }");
}

// Tests that parseRString return the correct RString when the input has 
// multiple braces
void test_parseRString_many_braces() {
    std::istringstream input(" 1 { 2 3 } }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 3 } }");
}

// Tests that parseRString returns the correct RRstring when the input has 
// multiple braces and no space in front
void test_parseRString_many_braces_nospace() {
    std::istringstream input("1 { 2 3 } }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 3 } }");
}

// Tests parseRString on an input with complex braces 1
void test_parseRString_complex_1() {
    std::istringstream input(" 1 { 2 { 3 4 } 5 } }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 { 3 4 } 5 } }");
}

// Tests parseRString on an input with complex braces 1 and more braces
void test_parseRString_complex_1_extrabrace() {
    std::istringstream input(" 1 { 2 { 3 4 } 5 } } }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 { 3 4 } 5 } }");
}

// Tests parseRString on an input with complex braces 2
void test_parseRString_complex_2() {
    std::istringstream input(" 1 { 2 { 3 4 } 5 } 6 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 { 3 4 } 5 } 6 }");
}

// Tests parseRString on an input with complex braces 3
void tests_parseRString_complex_3() {
    std::istringstream input(" 1 { 2 { 3 4 } 5 } 6 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 { 3 4 } 5 } 6 }");
}

// Tests parseRString on an input that doesn't have a balance set of braces
// and catch the error message
void test_parseRString_unbalanced() {
    std::istringstream input(" 1 { 2 { 3 4 } 5 6 ");

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        string rstring = parseRString(input);
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "unbalanced braces");
}

// Tests parseRString on an input with no closing braces
void test_parseRString_no_closing_braces() {
    std::istringstream input(" 1 2 3 ");

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        string rstring = parseRString(input);
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "unbalanced braces");
}

// Tests parseRString on an empty Rstring input with just a closing braket
void test_parseRString_one_braces() {
    std::istringstream input(" }");
    string rstring = parseRString(input);
    assert(rstring == "{ }");
}

// Tests parseRString on a completely empty input
void test_parseRString_empty() {
    std::istringstream input(" ");

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        string rstring = parseRString(input);
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "unbalanced braces");
}

// Tests parseRString on an empty input that's a space
void test_parseRString_space() {
    std::istringstream input(" ");

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        string rstring = parseRString(input);
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "unbalanced braces");
}

// Tests parseRString on an input that closes the braces before the end of the
// input
void test_parseRString_mid_end() {
    std::istringstream input (" 1 { 2 3 } 4 } 5 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 3 } 4 }");
}

// Tests parseRString on an input that closes the braces before all of the
// integers are inputted
void test_parseRString_mid_end_2() {
    std::istringstream input (" 1 } 2 3 } 4 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 }");
}

// Tests parseRString on an input with a line break
void test_parseRString_linebreak() {
    std::istringstream input (" 1 \n { 2 3 } 4 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 { 2 3 } 4 }");
}

// Tests parseRString on an input with spaces (whitespace)
void test_parseRString_whitespace() {
    std::istringstream input ("      1     2         3 }");
    string rstring = parseRString(input);
    assert(rstring == "{ 1 2 3 }");
}
