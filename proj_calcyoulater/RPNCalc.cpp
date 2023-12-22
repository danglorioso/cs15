/*
 *  RPNCalc.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/15/2023
 *
 *  CS 15 PROJECT 2: CalcYouLater
 *
 *  PURPOSE: Implementation of the RPNCalc class that includes a DatumStack
 *           object and functions to manipulate the stack. Functions include
 *           run, run_operation, run_inequality, got_int, parseRString,
 *           divide, mod, numIn, boolIn, not_command, print, dup, swap,
 *           printError, checkEmpty, rstring_command, exec. This implementation
 *           also contains a query loop that reads in commands from an istream.
 *
 */

#include "RPNCalc.h"
#include <iostream>
#include <istream>
#include <sstream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

/* RPNCalc()
 *    Purpose: Default constructor for the RPNCalc class that initalizes the
 *             RPNCalc object
 * Parameters: None
 *     Return: None 
 */
RPNCalc::RPNCalc() {
    // initialize the stack
    datum_stack = DatumStack();
}

/* ~RPNCalc()
 *    Purpose: Destructor for the RPNCalc class that destroys/deletes/recycles
 *             any heap-allocated data used in the the RPNCalc instance
 * Parameters: None
 *     Return: None 
 */
RPNCalc::~RPNCalc() {

}

/* run()
 *    Purpose: Reads in commands from standard input as a string and if the 
 *          command is not a quit, executes the run helper query function.
 * Parameters: None
 *     Return: None 
 */
void RPNCalc::run() {
    // open input stream
    string input;

    // while there is input and run is true, call the query loop
    run_helper(std::cin);

    // print the closing message
    std::cerr << "Thank you for using CalcYouLater.\n";
}

/* run_helper(istream &input)
 *    Purpose: A helper function for the run function that takes in the input 
 *             from istream input and run the appropriate function(s).
 * Parameters: istream &input - the input stream to read from
 *     Return: bool - true if the program should continue running, false if
 *                    the program should quit 
 */
bool RPNCalc::run_helper(std::istream &input) {
    string in;
    bool run = true;
    // while there is input, call the query loop
    while (run and input >> in) {
        try {
            if (in == "quit") {
                return false;
            } else {
                run = run_query(input, in);
            }
        } catch (const std::runtime_error &e) {
            printError(e.what());
        }
    }
    return true;
}

/* run_query(std::string input)
 *    Purpose: A helper function for the run function that takes in the input 
 *             from istream input and run the appropriate function(s).
 * Parameters: istream &input - the input stream to read from
 *     Return: bool - true if the program should continue running, false if
 *                    the program should quit 
 */
bool RPNCalc::run_query(std::istream &in, std::string input) {
    int value;
    bool run = true;
    // execute the query loop and execute the appropriate function(s)
    if (got_int(input, &value)) {
        numIn(value);
    } else if (input == "#t" or input == "#f") {
        boolIn(input);
    } else if (input == "#") {
        printError("invalid boolean #");
    } else if (input == "not") {
        not_command();
    } else if (input == "print") {
        print();
    } else if (input == "clear") {
        datum_stack.clear();
    } else if (input == "drop") {
        datum_stack.pop();
    } else if (input == "dup") {
        dup();
    } else if (input == "swap") {
        swap();
    } else if (input == "+" or input == "-" or input == "*" or input == "/" 
                or input == "mod") {
        run_operation(input);
    } else if (input == "==" or input == "<" or input == ">" 
                or input == "<=" or input == ">=") {
        run_inequiality(input);
    } else if (input == "{") {
        rstring_command(in); //send the istream input to rstring_command
    } else if (input == "exec") {
        run = exec();
    } else if (input == "file") {
        run = file();
        if (not run) {
            // means quit called within inputted file
            return false;
        }
    } else if (input == "if") {
        if_command();
    } else {
        std::cerr << input << ": unimplemented" << std::endl;
    }
    return true;
}

/* run_operation(std::string input)
 *    Purpose: A helper function for the run function that takes in the input 
 *             from standard input as a string and run the mathmetical  
 *             opeartion on the first and second integers on the stack.
 * Parameters: string input - the input stream to read from
 *     Return: None 
 */
void RPNCalc::run_operation(std::string input) {
    // pop off the first two elements
    Datum first_el = datum_stack.top();
    datum_stack.pop();
    Datum second_el = datum_stack.top();
    datum_stack.pop();

    // run getInt on each element to check if they are integers
    int first = first_el.getInt();
    int second = second_el.getInt();

    // perform the operation and push the result onto the stack
    if (input == "+") {
            numIn(first + second);
    } else if (input == "-") {
        numIn(second - first);
    } else if (input == "*") {
        numIn(first * second);
    } else if (input == "/") {
        divide(second, first);
    } else if (input == "mod") {
        mod(second, first);
    }
}

/* run_inequality(istream &input)
 *   Purpose: A helper function for the run function that reads in an inequality
 *          as a string and pop the top two elements off the stack and perform
 *          the appropriate inequality operation, pushing the result as a
 *          boolean onto the stack.
 * Parameters: istream &input - the input stream to read from
 *     Return: None 
 */
void RPNCalc::run_inequiality(std::string input) {
    // pop and store the top two element off the stack
    Datum first = datum_stack.top();
    datum_stack.pop();
    Datum second = datum_stack.top();
    datum_stack.pop();

    // perform the operation and push the result onto the stack
    if (input == "==") {
        bool result = (first == second);
        Datum data = Datum(result);
        datum_stack.push(data);
    } else if (input == "<") {
        Datum data = Datum((second < first));
        datum_stack.push(data);
    } else if (input == ">") {
        Datum data = Datum((not(second < first) and not(second == first)));
        datum_stack.push(data);
    } else if (input == "<=") {
        Datum data = Datum(((second < first) and (second == first)));
        datum_stack.push(data);
    } else if (input == ">=") {
        Datum data = Datum((not((second < first))));
        datum_stack.push(data);
    }
}

/* got_int(string s, int *resultp)
 *    Purpose: Determines whether a string can be interpreted as an integer
 *             number, and if so, gives the value.
 * Parameters: string s - the string to check
 *             int *resultp - a pointer to the integer to store the value in
 *    Returns: bool - true if the string s can be interpreted as an integer
 *             number, placing the associated integer into the location
 *             pointed to by resultp. False if string s cannot be interpreted
 *             as an integer, leaving the location pointed to by resultp
 *             unmodified.
 */
bool RPNCalc::got_int(std::string s, int *resultp)
{
    /* Holds the first non-whitespace character after the integer */
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* parseRSTring(istream &input)
 *    Purpose: Takes a reference to an instream as a parameter to continue 
 *             reading the input stream until all curly braces have been 
 *             matched or the end of the file is reached. Parses the input
 *             stream and returns a string containing the contents of the
 *             input stream up until the final matching curly brace.
 * Parameters: istream &input - input stream
 *    Returns: A string containing the contents of the input stream surrounded
 *             by curly braces.
 */
string RPNCalc::parseRString(std::istream &input) {
    string rstring = "{";
    int braceCounter = 1;
    bool run = true;
    string temp_string;
    string in;

    // read in the input until end of input stream or final matching brace
    while (run and input >> in) {
        temp_string += " ";
        temp_string += in;
        if (in == "{") {
            braceCounter++;
        } else if (in == "}") {
            braceCounter--;
            if (braceCounter == 0) {
                run = false;
            }
        }
    }

    // if the braces are unbalanced, thrown an exception
    if (not(braceCounter == 0)) {
        throw std::runtime_error("rstring braces don't match");
    }

    rstring = "{" + temp_string;
    return rstring;
}

/* divide(int first, int second)
 *    Purpose: Creates a Datum object with the quotient of the two integers and
 *             pushes it onto the stack.
 * Parameters: int first - the first integer from the top of the stack to
 *             divide
 *             int second - the second integer on the stack to divide
 *     Return: None 
 */
void RPNCalc::divide(int second, int first) {
    // check for divide by 0
    if (first == 0 ) {
        printError("division by 0.");
    } else {
        // push the quotient onto the stack
        numIn(second / first);
    }
}

/* mod(int first, int second)
 *    Purpose: Creates a Datum object with the remainder of the two integers
 *             and pushes it onto the stack.
 * Parameters: int first - the first integer from the top of the stack to
 *                         mod
 *             int second - the second integer on the stack to mod
 *     Return: None 
 */
void RPNCalc::mod(int second, int first) {
    if (first == 0) {
        printError("division by 0.");
    } else {
        // push the remainder onto the stack
        numIn(second % first);
    }
}

/* numIn
 *    Purpose: Push a number onto the stack in the form of a Datum object
 * Parameters: string input - the number to push onto the stack
 *     Return: None 
 */
void RPNCalc::numIn(int input) {
    //create a Datum object from the string
    Datum data = Datum(input);
    //push the Datum object onto the stack
    datum_stack.push(data);
}

/* boolIn
 *    Purpose: Push a boolean onto the stack in the form of a Datum object
 * Parameters: string input - the boolean to push onto the stack
 *     Return: None 
 */
void RPNCalc::boolIn(std::string input) {
    //create a Datum object from the string input and push onto stack
    if (input == "#t") {
        Datum data = Datum(true);
        datum_stack.push(data);
    } else {
        Datum data = Datum(false);
        datum_stack.push(data);
    }
}

/* not_command()
 *    Purpose: Reads and pops the top element off the stack, a boolean, and
 *             causes a Datum with the opposite boolean value of the popped
 *             element to be pushed onto the stack.
 * Parameters: None
 *     Return: None 
 */
void RPNCalc::not_command() {
    // pop first element off the stack
    Datum first_el = datum_stack.top();
    datum_stack.pop();

    // check if it is a boolean
    bool first = first_el.getBool();

    // push the opposite boolean onto the stack
    if (first) {
        Datum data = Datum(false);
        datum_stack.push(data);
    } else {
        Datum data = Datum(true);
        datum_stack.push(data);
    }
}

/* print()
 *    Purpose: Prints the value on the top of the stack to std::count (without
 *             popping it) followed by a new line.
 * Parameters: None
 *     Return: None 
 */
void RPNCalc::print() {
    //if the stack is empty, print error message
    if (not checkEmpty()) {
        // print top of stack
        std::cout << datum_stack.top().toString() << std::endl;
    }
}

/* dup()
 *    Purpose: Duplicates the top Datum object on the stack and pushes the
 *             duplicate onto the stack.
 * Parameters: None
 *     Return: None
 */
void RPNCalc::dup() {
    //if the stack is empty, print error message
    if (not checkEmpty()) {
        //duplicate the top of the stack
        datum_stack.push(datum_stack.top());
    }
}

/* swap()
 *    Purpose: Swaps the top two Datum objects on the stack
 * Parameters: None
 *     Return: None
 */
void RPNCalc::swap() {
    //if the stack is empty, print error message
    if (not checkEmpty()) {
        //swap the top two objects on the stack
        Datum top = datum_stack.top();
        datum_stack.pop();
        Datum temp = datum_stack.top();
        datum_stack.pop();
        datum_stack.push(top);
        datum_stack.push(temp);
    }
}

/* printError(string message)
 *    Purpose: Print an error message to standard error
 * Parameters: string message - the error message to print
 *     Return: None 
 */
void RPNCalc::printError(std::string message) {
    cerr << "Error: " << message << endl;
}

/* checkEmpty()
 *    Purpose: Check if the stack is empty and print an error message if it is
 * Parameters: None
 *     Return: None 
 */
bool RPNCalc::checkEmpty() {
    //if the stack is empty, print error message
    if (datum_stack.isEmpty()) {
        printError("empty_stack");
        return true;
    } else {
        return false;
    }
}

/* rstring_command(istream &input)
 *    Purpose: Reads in an rString from the input stream and pushes it onto the
 *             stack.
 * Parameters: istream &input - the input stream to read from
 *     Return: None 
 */
void RPNCalc::rstring_command(std::istream &input) {
    // send the istream input to parseRString
    std::string rstring = parseRString(input);

    // create a Datum object from the rString and push onto the stack
    Datum data = Datum(rstring);
    datum_stack.push(data);
}

/* exec()
 *    Purpose: Takes the topmost element on the stack, which must be an
 *             rString, and processes its content as a sequence of commands.
 * Parameters: None
 *     Return: None 
 */
void RPNCalc::exec() {
    // pop the top element off the stack
    Datum first_el = datum_stack.top();
    datum_stack.pop();

    // create an input stream from the rString
    if (first_el.isRString()) {
        string rstring = first_el.getRString();
        // remove the curly braces from the rString
        rstring.erase(0, 1);
        int size = rstring.size();
        rstring.erase(size - 1);

        // send in the contents on the string to run_helper through an istream
        std::istringstream iss(rstring);
        run_helper(iss);
    } else {
        printError("cannot execute non rstring");
    }
}

/* file()
 *    Purpose: Pops the top element off of the stack, which must be an rstring
 *             and treats its contents as if it is commands that have been
 *             typed into the command loop.
 * Parameters: None
 *     Return: bool - true if the program should continue running, false if
 *                    the program should quit 
 */
bool RPNCalc::file() {
    // pop the top element off the stack
    Datum first_el = datum_stack.top();
    datum_stack.pop();
    bool run = true;

    // create an input stream from the rString
    if (first_el.isRString()) {
        string rstring = first_el.getRString();
        // remove the curly braces and spaces from the rString
        rstring.erase(0, 1);
        rstring.erase(0, 1);
        int size = rstring.size();
        rstring.erase(size - 1);
        rstring.erase(size - 2);

        // open the file and send in the contents on the string to run_helper
        std::ifstream instream(rstring);
        if (not (instream.is_open())) {
            std::cerr << "Unable to read " << rstring << std::endl;
        } else {
            run = run_helper(instream);
            // if run_helper bool is false, quit the program
            if (not run) {
                return false;
            }
        }
    } else {
        printError("file operand not rstring");
    }
    return true;
}

/* if_command()
 *    Purpose: Pops an rstring off the stack (executed if false), then pops a 
 *             another rstring off the stack (executed if true), and then pops
 *             a boolean off the stack, that is the condition to test. 
 * Parameters: None
 *     Return: None 
 */
void RPNCalc::if_command() {
    // pop the top element off the stack
    Datum first_el = datum_stack.top();
    datum_stack.pop();
    // pop the next element off the stack
    Datum second_el = datum_stack.top();
    datum_stack.pop();

    // checks if the second element is an rString
    if (not first_el.isRString() or not second_el.isRString()) {
        printError("expected rstring in if branch");
    }

    // pop the next element off the stack
    Datum third_el = datum_stack.top();
    datum_stack.pop();

    // checks if the third element is a boolean
    if (not third_el.isBool()) {
        printError("expected boolean in if test");
    } else {
        bool test = third_el.getBool();
        if (test) {
            // push the trueCase onto the stack
            Datum data = Datum(second_el.getRString());
            datum_stack.push(data);
            exec();
        } else {
            // push the falseCase onto the stack
            Datum data = Datum(first_el.getRString());
            datum_stack.push(data);
            exec();
        }
    }
}
