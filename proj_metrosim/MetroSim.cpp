/*
 *  MetroSim.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Implementation of the MetroSim class and its functions that are
 *           used in the MetroSim program, which include prompt_and_execute
 *           functions for both cin and file inputs, initalize, getStations, 
 *           printSimulation, finishSim, addPassengers, moveTrain, and getters.
 *
 */

#include "MetroSim.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

using namespace std;
/* MetroSim() 
 *    Purpose: Default constructor for the MetroSim class
 * Parameters: None
 *    Returns: None
 */
MetroSim::MetroSim()
{
    passengerID = 1;
    trainLocation = 0;
}

/* prompt_and_execute_CIN()
 *    Purpose: Prompts the user for input and executes the command
 * Parameters: None
 *    Returns: None
 *     Effect: The program will continue to prompt the user for input until
 *             the user enters "m f"
 */
void MetroSim::prompt_and_execute_CIN(std::ostream &output) 
{
    bool run = true;
    string command;
    while (run and cin.eof()) {
        std::cin >> command ;
        if (command == "m") {
            string command2;
            std::cin >> command2;
            if (command2 == "m") {
                moveTrain(output);
            } else if (command2 == "f") {
                run = false;
            }
        } else if (command == "p") {
            int fromStation, toStation;
            std::cin >> fromStation;
            std::cin >> toStation;
            addPassengers(fromStation, toStation);
        } else {
            std::cout << "Note: students do not need to handle invalid" 
                    << "commands." << endl;
        }
    }
    // finish the program
    finishSim();
}

void MetroSim::prompt_and_execute_FILE(std::ostream &output, 
                                       std::ifstream &commandstream) 
{
    string line;
    bool run = true;
    while (run and (std::getline(commandstream, line))) {
        istringstream iss(line);
        string command1;
        int fromStation, toStation;
        
        if (iss >> command1) {
            if (command1 == "m") {
                string command2;
                if (iss >> command2) {
                    if (command2 == "m") {
                        moveTrain(output);
                    } else if (command2 == "f") {
                        run = false;
                    }
                }
            } else if (command1 == "p") {
                if (iss >> fromStation >> toStation) {
                    addPassengers(fromStation, toStation);
                }
            }
        } else {
                std::cout << "Note: students do not need to handle invalid" 
                        << "commands." << endl;
        }
    }
    // finish the program
    finishSim();
}

/* finishSim
 *    Purpose: Prints the goodbye message
 * Parameters: None
 *    Returns: None
 */
void MetroSim::finishSim()
{
    std::cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/* initalize(ifstream &instream)
 *    Purpose: Read in the stations file and update the stations list
 * Parameters: ifstream &instream - a reference to the stations file stream
 *    Returns: None
 */
void MetroSim::initalize(std::ifstream &instream)
{
    //call getStations to read in the stations file
    getStations(instream);

    //initalize train at the first station
    trainLocation = 0;

    //print the stations
    printSimulation();
}

/* getNumStations()
 *   Purpose: Returns the number of stations
 * Parameters: None
 *    Returns: int numStations
 */
int MetroSim::getNumStations(istream &instream) {
    int numStationLines = 0;
    string line;
    
    // for each line in the instream, count the number of lines
    while (std::getline(instream, line)) {
        numStationLines++;
    }
    return numStationLines;
}

/* getStations(ifstream &instream)
 *    Purpose: Read in the stations file and update the stations list
 * Parameters: ifstream &instream - a reference to the stations file stream
 *    Returns: None
 */
void MetroSim::getStations(std::ifstream &instream) {
    string stationName;
    int stationCounter= 0; // counter for the station index
    // create new station for each station and add it to the stationList vector
    while (std::getline(instream, stationName)) {
        // create a new station object for each station
        stations.addStation(stationCounter, stationName);

        // create a new PassengerQueue in train
        train.addQueues();

        // increment the count
       stationCounter++;
    }
}

/* printSimulation(ofstream &outstream)
 *    Purpose: Prints the current simulation to the outstream file
 * Parameters: ofstream &outstream - a reference to the outstream file stream
 *    Returns: None
 */
void MetroSim::printSimulation()
{
    std::cout << "Passengers on the train: {";
    train.print(std::cout);
    std::cout << "}" << endl;

    // iterate through all PassengerQueues and print them
    int stationListSize = stations.getNumStations() - 1;
    for (int i = 0; i < stationListSize; i++)
    {
        if (i == trainLocation) {
            std::cout << "TRAIN: ";
        } else {
            std::cout << "       ";
        }
        stations.print(i, std::cout);
    }
    std::cout << "Command? ";
}

/* moveTrain(ostream &output)
 *    Purpose: Moves the train to the next station
 * Parameters: ostream &output - a reference to the output stream
 *    Returns: None
 */
void MetroSim::moveTrain(std::ostream &output)
{
    // pick up all passengers at the current station
    train.boardPassengers(stations.getStationQueue(trainLocation));

    // clear the current station queue
    stations.clearStation(trainLocation);

    // incremene the train location
    if (trainLocation < stations.getNumStations() - 1) {
        trainLocation++;
        if (trainLocation == stations.getNumStations() - 1) {
            trainLocation = 0;
        }  
    }

    // dequeue all passengers who's destination is the current station
    train.emptyPassengers(trainLocation, output, 
                          stations.getStationName(trainLocation));

    // print the simulation
    printSimulation();
}

/* addPassengers(int fromStation, int toStation)
 *    Purpose: Adds a passenger to the station queue
 * Parameters: int fromStation - the station the passenger is at
 *             int toStation - the station the passenger is going to
 *    Returns: None
 */
void MetroSim::addPassengers(int fromStation, int toStation)
{
    // create a passenger
    Passenger passenger(passengerID, fromStation, toStation);

    // add the passenger to the station queue
    stations.addPassengers(fromStation, passenger);

    // increment the passengerID
    passengerID++;

    // print the simulation
    printSimulation();
}
