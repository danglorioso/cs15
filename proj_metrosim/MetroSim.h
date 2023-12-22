/*
 *  MetroSim.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Declaration of the MetroSim class and its functions that are
 *           used in the MetroSim program, which include prompt_and_execute
 *           functions for both cin and file inputs, initalize, getStations, 
 *           printSimulation, finishSim, addPassengers, moveTrain, and getters.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include "Stations.h"
#include "Train.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

// Put any other necessary includes here


// Put any other structs you need here

class MetroSim
{
public:
    // constructor
    MetroSim();

    // prompt and execute commands
    void prompt_and_execute_CIN(std::ostream &output);
    void prompt_and_execute_FILE(std::ostream &output, 
                                std::ifstream &commandstream);
    
    // // interface functions
    void initalize(std::ifstream &instream);
    void printSimulation();
    void finishSim();

    // getters
    void getStations(std::ifstream &instream);
    int getNumStations(istream &instream);

private:
    int passengerID;
    int trainLocation;
    int numStations;
    Train train;
    Stations stations;

    // add Passenegrs
    void addPassengers(int fromStation, int toStation);

    // metro move 
    void moveTrain(std::ostream &output);

    // getters
    int getTrainLocation();
};

#endif
