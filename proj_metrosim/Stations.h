/*
 *  Stations.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Declaration of the Stations class and its functions that are used
 *           in the MetroSim program, which are addPassengers, clearStation,
 *           addStation, getNumStations, getStationName, getStationQueue, and
 *           print.
 *
 */

#ifndef _STATIONS_H_
#define _STATIONS_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Stations
{
public:
    // constructors
    Stations();

    // destructor
    ~Stations();
    
    // interface functions
    void addPassengers(int station, Passenger passenger);
    void clearStation(int station);
    void addStation(int station_index, string name);

    // getters
    int getNumStations(); 
    string getStationName(int station); 
    PassengerQueue getStationQueue(int station);
    void print(int index, std::ostream &output);

private:
    // struct for each station
    struct Station {
        string name;
        PassengerQueue queue;
    };

    // vector of stations
    vector<Station *> stationList;
};

#endif
