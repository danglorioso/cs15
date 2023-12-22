/*
 *  RPNCalc.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/15/2023
 *
 *  CS 15 PROJECT 2: CalcYouLater
 *
 *  PURPOSE: Declaration of the RPNCalc class that includes a DatumStack
 *           object and functions to manipulate the stack and perform 
 *           operations on the stack from the commands.
 *
 */

#ifndef _RPNCALC_H_
#define _RPNCALC_H_

#include <string>
#include <istream>
#include <sstream>
#include <cstdio>
#include <string>
#include <fstream>
#include "DatumStack.h"

class RPNCalc
{
public:
    // constructor
    RPNCalc();

    // destructor
    ~RPNCalc();

    // interface function
    void run();
    bool run_helper(std::istream &input);
    bool run_query(std::istream &in, std::string input);
    void run_operation(std::string input);
    void run_inequiality(std::string input);
    bool got_int(std::string s, int *resultp);
    std::string parseRString(std::istream &input);

    // operation helpers
    void divide(int second, int first);
    void mod(int second, int first);

    // simple commands
    void numIn(int input);
    void boolIn(std::string input);
    void not_command();
    void print();
    void dup();
    void swap();

    // helper function
    void printError(std::string message);
    bool checkEmpty();

    // // complex commands
    void rstring_command(std::istream &input);
    void exec();
    bool file();
    void if_command();
    
private:
    DatumStack datum_stack;

};

#endif