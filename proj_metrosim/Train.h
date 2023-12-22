/*
 *  Train.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Declaration of the Train class and its functions that are used
 *           in the MetroSim program, which include the constructor, addQueues,
 *           print, emptyPassengers, and boardPassengers.
 *
 */

#ifndef __TRAIN_H__
#define __TRAIN_H__

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Train
{
public:
    // constructors
    Train();

    //destructor
    ~Train();

    // interface functions
    void addQueues();
    void print(std::ostream &output);
    void emptyPassengers(int station, std::ostream &output, string stationName);
    void boardPassengers(PassengerQueue queue);

private:
    // vector of PassengerQueues
    vector<PassengerQueue> train;
};

#endif
