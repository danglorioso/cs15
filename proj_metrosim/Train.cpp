/*
 *  Train.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 10/07/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Implementation of the Train class and its functions that are used
 *           in the MetroSim program, which include the constructor, addQueues,
 *           print, emptyPassengers, and boardPassengers.
 *
 */

#include "Train.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/* Train() 
 *    Purpose: Default constructor for the Train class
 * Parameters: None
 *    Returns: None
 */
Train::Train()
{
    PassengerQueue queue;
    train.push_back(queue);
}

/* ~Train() 
 *    Purpose: Destructor for the Train class
 * Parameters: None
 *    Returns: None
 */
Train::~Train()
{
    // delete the queues
    int trainSize = train.size();
    for (int i = 0; i < trainSize; i++)
    {
        train.pop_back();
    }
}

/* addQueues()
 *    Purpose: Adds a queue to the train
 * Parameters: int numStations
 *    Returns: None
 */
void Train::addQueues()
{
    // create a queue
    PassengerQueue queue;
    train.push_back(queue);
}

/* print()
 *    Purpose: Prints the train
 * Parameters: ostream &output
 *    Returns: None
 */
void Train::print(std::ostream &output)
{
    int trainSize = train.size();
    for (int i = 0; i < trainSize; i++)
    {
        train[i].print(output);
    }
}

/* emptyPassengers()
 *    Purpose: Empties the passengers from the train who are at their station
 * Parameters: int station, ostream &output
 *    Returns: None
 */
void Train::emptyPassengers(int station, std::ostream &output, 
                            string stationName)
{
    // empty the passengers from the train
    int trainSize = train.size();
    for (int i = 0; i < trainSize; i++)
    {
        int queueSize = train[i].size();
        for (int j = 0; j < queueSize; j++)
        {
            if (train[i].front().to == station)
            {
                // print to the output stream that the passenger left
                output << "Passenger " << train[i].front().id;
                output << " left train at station " << stationName << endl;
                train[i].dequeue();
            }
        }
    }
}

/* boardPassengers()
 * Purpose: Boards passengers onto the train
 * Parameters: int station, Passenger passenger
 *    Returns: None
 */
void Train::boardPassengers(PassengerQueue queue)
{
    // board passengers onto the train
    int queueSize = queue.size();

    // board passengers into queues based on their destination
    for (int i = 0; i < queueSize; i++)
    {

        train[queue.front().to].enqueue(queue.front());
        queue.dequeue();
    }
}
