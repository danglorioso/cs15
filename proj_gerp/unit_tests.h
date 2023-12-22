/*
 *  unit_tests.h
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 11/30/2023
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: To test the functionality of the PhaseOne functions using the
 *           unit testing framework with a variety of tests that cover
 *           possible cases.
 *
 */

#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>

#include "stringProcessing.h"
#include "Gerp.h"
#include "File.h"
#include "HashTable.h"

using namespace ::std;

/*Dummy Test*/
// Tests that the unit_tests is working
void dummy_test()
{
    assert(true);
}

/********************************************************************\
*                FSTREETRAVERSAL FUNCTIONS                           *
\********************************************************************/

/********************************************************************\
*                STRINGPROCESSING FUNCTIONS                          *
\********************************************************************/
// stringProcessingTest function

// Test leading and trailing non-alphanumeric characters
// void stringProcessing_BothEnds()
// {
//     string test = "%%%%%test!!!";
//     string result = stripNonAlphaNum(test);
//     assert(result == "test");
// }

// // Tests as properly formatted string
// void stringProcessingTest_None()
// {
//     string test = "test";
//     string result = stripNonAlphaNum(test);
//     assert(result == "test");
// }

// // Tests a string with leading non-alphanumeric characters
// void stringProcessingTest_begin()
// {
//     string test = "&&%%test";
//     string result = stripNonAlphaNum(test);
//     assert(result == "test");
// }

// // Tests a string with trailing non-alphanumeric characters
// void stringProcessingTest_end()
// {
//     string test = "test***()((()))";
//     string result = stripNonAlphaNum(test);
//     assert(result == "test");
// }

// // Tests a string with non-alphanumeric characters in the middle
// void stringProcessingTest_middle()
// {
//     string test = "how^dy";
//     string result = stripNonAlphaNum(test);
//     assert(result == "how^dy");
// }

// // Tests a string with non-alphanumeric characters in the middle
// // and at the beginning and end
// void stringProcessingTest_middle_both_ends()
// {
//     string test = "*how^dy!!";
//     string result = stripNonAlphaNum(test);
//     assert(result == "how^dy");
// }

// // Tests a string with numbers in it
// void stringProcessingTest_numbers()
// {
//     string test = "1234";
//     string result = stripNonAlphaNum(test);
//     assert(result == "1234");
// }

// // Tests a string with numbers and non-alphanumeric characters
// void stringProcessingTest_numbers_and_non()
// {
//     string test = "1234!!";
//     string result = stripNonAlphaNum(test);
//     assert(result == "1234");
// }

// // Tests a string with leading characters and numbers
// void stringProcessingTest_begin_numbers()
// {
//     string test = "comp15";
//     string result = stripNonAlphaNum(test);
//     assert(result == "comp15");
// }

// // Tests a string with trailing characters and numbers
// // and non-alphanumeric characters
// void stringProcessingTest_end_numbers()
// {
//     string test = "comp15!!";
//     string result = stripNonAlphaNum(test);
//     assert(result == "comp15");
// }

// // Tests a string with alphanumeric characters in the middle and
// // leading and trailing non-alphanumeric characters
// void stringProcessingTest_middle_both_ends_numbers()
// {
//     string test = "!!comp15!!";
//     string result = stripNonAlphaNum(test);
//     assert(result == "comp15");
// }

// // Tests a string with alphacharacters at the beginning and end
// // and numbers and non-alphanumeric characters in the middle
// void stringProcessingTest_middle_both_ends_numbers_and_non()
// {
//     string test = "comp15comp";
//     string result = stripNonAlphaNum(test);
//     assert(result == "comp15comp");
// }

// // Tests a string with alphacharacters at the beginning and end
// // and numbers and non-alphanumeric characters in the middle
// // and leading and trailing non-alphanumeric characters
// void stringProcessingTest_middle_both_ends_numbers_and_non_all()
// {
//     string test = "&&comp15comp&&";
//     string result = stripNonAlphaNum(test);
//     assert(result == "comp15comp");
// }

// // Tests a string with only non-alphanumeric characters
// void stringProcessingTest_only_non1()
// {
//     string test = "!^%^$&*#*!";
//     string result = stripNonAlphaNum(test);
//     assert(result == "");
// }

// // Tests a string with only non-alphanumeric characters
// void stringProcessingTest_only_non2()
// {
//     string test = "%($&*^&$*#^&*$(*&^$@(#)";
//     string result = stripNonAlphaNum(test);
//     assert(result == "");
// }

// // Tests a string with only non-alphanumeric characters
// void stringProcessingTest_only_non3()
// {
//     string test = "&$&**#()";
//     string result = stripNonAlphaNum(test);
//     assert(result == "");
// }

// // Tests an empty string
// void stringProcessingTest_empty()
// {
//     string test = "";
//     string result = stripNonAlphaNum(test);
//     assert(result == "");
// }


/********************************************************************\
*                         GERP FUNCTIONS                             *
\********************************************************************/
// makeTree function

// // Tests the makeTree function with the Foo directory
// void makeTreeTest_Foo()
// {
//     Gerp gerp;
//     string filePath = "Foo";
//     gerp.makeTree(filePath);
//     assert(not gerp.tree->isEmpty());
//     assert(gerp.tree->getRoot()->getName() == "Foo");
// }

// // Tests the makeTree function with the Bar directory
// void MakeTreeTest_Bar()
// {
//     Gerp gerp;
//     string filePath = "Foo/Bar";
//     gerp.makeTree(filePath);
//     assert(not gerp.tree->isEmpty());
//     assert(gerp.tree->getRoot()->getName() == "Foo/Bar");
// }

// // Tests the number of files in the tree from the Foo directory
// void makeTreeTest_numfiles_Foo()
// {
//     Gerp gerp;
//     string filePath = "Foo";
//     gerp.makeTree(filePath);
//     assert(gerp.tree->getRoot()->numFiles() == 3);
// }

// // Tests the number of files in the tree from the Bar directory 
// void makeTreeTest_numfiles_Bar()
// {
//     Gerp gerp;
//     string filePath = "Foo/Bar";
//     gerp.makeTree(filePath);
//     assert(gerp.tree->getRoot()->numFiles() == 3);
// }

// traverseTree function

// Tests the traverseTree function with the Foo directory
// void traverseTreeTest()
// {
//     Gerp gerp;
//     string filePath = "Foo";
//     gerp.makeTree(filePath);
//     gerp.traverseTree(gerp.tree->getRoot(), filePath);
// }


// parseLines function
// Tests the parseLines function with a l
// void parseLineTest()
// {
//     Gerp gerp;
//     string line = "Hello, my name is Dan.";
//     gerp.parseLine(line);
//     assert(gerp.files[0]->getLine(0) == "Hello, my name is Dan.");
// }