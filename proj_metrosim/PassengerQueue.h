/*
 *  PassengerQueue.h
 *  Created by: Dan Glorioso
 *  Date: 09/29/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Declaration of the PassengerQueue class and its functions
 *           that are used in the MetroSim program, including enqueue, dequeue,
 *           size, and print.
 *
 */

#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include "Passenger.h"
#include <iostream>
#include <list>

class PassengerQueue
{
public:
    //interface functions
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);

private:
    std::list <Passenger> data;
    int count;
};

#endif
