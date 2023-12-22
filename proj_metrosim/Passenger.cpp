/*
 *  Passenger.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/28/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Implementation of the Passenger class and its function
 *           that is used in the MetroSim program, which is print.
 * 
 */

#include "Passenger.h"
#include <iostream>

using namespace std;

/* print(std::ostream &output)
 *    Purpose: Constructor for Passenger class
 * Parameters: int id, string from, string to
 *    Returns: None
 */
void Passenger::print(std::ostream &output)
{
       output << "[" << id << ", " << from << "->" << to << "]";
}
