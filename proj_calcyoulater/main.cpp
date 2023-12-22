/*
 *  main.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/15/2023
 *
 *  CS 15 PROJECT 2: CalcYouLater
 *
 *  PURPOSE: Main function for the CalcYouLater program. The program is the
 *           implementation of a Reverse Polish Notation (RPN) calculator that
 *           can perform basic arithmetic operations on integers, bools, and
 *           strings.
 *
 */

#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include "RPNCalc.h"

using namespace std;

int main(int argc, char *argv[])
{
    // create an RPNCalc object
    RPNCalc calc;

    // call the run function in RPNCalc
    calc.run();

    return 0;
}
