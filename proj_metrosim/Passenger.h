/*
 *  Passenger.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/28/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Declaration of the Passenger class and its function
 *           that is used in the MetroSim program, which is print. 
 * 
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif
