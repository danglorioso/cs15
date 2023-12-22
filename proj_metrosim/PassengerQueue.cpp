/*
 *  PassengerQueue.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/29/2023
 *
 *  CS 15 PROJECT 1: MetroSim
 *
 *  PURPOSE: Implementation of the PassengerQueue class and its functions
 *           that are used in the MetroSim program, including enqueue, dequeue,
 *           size, and print.
 *
 */

#include "PassengerQueue.h"
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

/* front()
 *    Purpose: Returns the first passenger in the PassengerQueue
 * Parameters: None
 *    Returns: Passenger
 */
Passenger PassengerQueue::front()
{
    //throws error if function is called on an empty queue
    if (data.empty()) {
        throw range_error("front() called on empty queue");
    } else {
        std::list<Passenger>::iterator it = data.begin();
        return *it;
    }
}

/* dequeue()
 *    Purpose: Removes the first passenger in the PassengerQueue
 * Parameters: None
 *    Returns: None
 *     Effect: Removes the first passenger in the PassengerQueue and decrements
 *             the count
 */
void PassengerQueue::dequeue()
{
    if (data.empty()) {
        throw range_error("dequeue() called on empty queue");
    } else {
        std::list<Passenger>::iterator it = data.begin();
        data.erase(it);
        count--;
    }
}

/* enqueue()
 *    Purpose: Adds a passenger to the end of the PassengerQueue
 * Parameters: Passenger passenger
 *    Returns: None
 *     Effect: Adds a passenger to the end of the PassengerQueue and increments
 *             the count
 */
void PassengerQueue::enqueue(const Passenger &passenger)
{
    data.push_back(passenger);
    count++;
}

/* size()
 *    Purpose: Returns the size of the PassengerQueue 
 * Parameters: None
 *    Returns: int count
 */
int PassengerQueue::size()
{
    return data.size();
}

/* print()
 *    Purpose: Prints the PassengerQueue
 * Parameters: ostream output
 *    Returns: None
 */
void PassengerQueue::print(std::ostream &output)
{
    std::list<Passenger>::iterator it = data.begin();
    while (not(it == data.end()))
    {
        it->print(output);
        it++;
    }
}
