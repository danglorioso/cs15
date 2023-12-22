/*
 *  Stations.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Implementation of the Stations class and its functions
 *           that are used in the MetroSim program, which include addStation,
 *           addPassengers, clearStation, getNumStations, getStationName,
 *           getStationQueue, and print.
 *
 */

#include "Stations.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/* Stations() 
 *    Purpose: Default constructor for the Stations class
 * Parameters: None
 *    Returns: None
 */
Stations::Stations()
{
    // initialize the station
    PassengerQueue queue;
    Station *newStation = new Station;
    newStation->name = "";
    newStation->queue = queue;
    stationList.push_back(newStation);
}

/* ~Stations() 
 *    Purpose: Destructor for the Stations class
 * Parameters: None
 *    Returns: None
 */
Stations::~Stations()
{
    // delete the stations
    int stationListSize = stationList.size();
    for (int i = 0; i < stationListSize; i++)
    {
        delete stationList[i];
    }
}

/* addStation()
 *    Purpose: Adds a station name to the stationList
 * Parameters: int station, string name 
 *    Returns: None
 */
void Stations::addStation(int station_index, string name)
{
    PassengerQueue queue;
    stationList[station_index]->name = name;
    Station *newStation = new Station;
    newStation->name = name;
    newStation->queue = queue;
    stationList.push_back(newStation);
}

/* print(ostream &output) 
 *    Purpose: Prints the stations and their queues
 * Parameters: ostream &output
 *    Returns: None
 */
void Stations::print(int index, std::ostream &output)
{
    // print the stations
    output << "[" << index << "] " << stationList[index]->name << " {";
    stationList[index]->queue.print(output);
    output << "}" << endl;
}

/* getNumStations()
 *    Purpose: Returns the number of stations
 * Parameters: None
 *    Returns: int numStations
 */
int Stations::getNumStations()
{
    return stationList.size();
}

/* getStationName()
 *    Purpose: Returns the name of the station
 * Parameters: int station
 *    Returns: string name
 */
string Stations::getStationName(int station)
{
    return stationList[station]->name;
}

/* addPassengers()
 *    Purpose: Adds a passenger to the station queue
 * Parameters: int station, Passenger passenger
 *    Returns: None
 */
void Stations::addPassengers(int station, Passenger passenger)
{
    stationList[station]->queue.enqueue(passenger);
}

/* getStationQueue()
 *   Purpose: Returns the station queue
 * Parameters: int station
 *    Returns: PassengerQueue queue
 */
PassengerQueue Stations::getStationQueue(int station)
{
    return stationList[station]->queue;
}

/* clearStation()
 *   Purpose: Clears the station queue
 * Parameters: int station
 *    Returns: None
 */
void Stations::clearStation(int station)
{
    // dequeue for each passenger in the queue
    int queueSize = stationList[station]->queue.size();
    for (int i = 0; i < queueSize; i++)
    {
        stationList[station]->queue.dequeue();
    }
}
