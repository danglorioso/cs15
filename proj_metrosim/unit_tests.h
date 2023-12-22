/*
 *  unit_tests.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 09/28/2023
 * 
 *  CS 15 PROJECT 1: MetroSim
 * 
 *  PURPOSE:  To test the Passenger, PassengerQueue class and its function 
 *            using the unit_test framework. 
 * 
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"
#include "Train.h"
#include "Stations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

/*Dummy Test*/
// Tests that the unit_tests is working
void dummy_test() {
    assert(true);
}

/********************************************************************\
*                       PASSENGER CLASS                              *
\********************************************************************/
/*Constructor*/
// Tests that the Passenger class is working
void test_passenger() {
    Passenger p(1, 2, 3);
    assert(p.id == 1);
    assert(p.from == 2);
    assert(p.to == 3);
}

/*void Passenger::print(std::ostream &output)*/
// Tests that the Passenger class is printing correctly with one passenger
void test_passenger_print() {
    Passenger p(1, 2, 3);
    std::stringstream ss;
    p.print(ss);
    assert(ss.str() == "[1, 2->3]");
}

// Tests that the Passenger class is printing correctly with multiple 
// passengers
void test_passenger_print_multiple() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    std::stringstream ss;
    p1.print(ss);
    p2.print(ss);
    assert(ss.str() == "[1, 2->3][2, 3->4]");
}

/********************************************************************\
*                       PASSENGERQUEUE CLASS                         *
\********************************************************************/
/*Constructor*/
// Tests that the PassengerQueue class is working
void test_passenger_queue() {
    PassengerQueue pq;
    assert(pq.size() == 0);
}

// Tests that the PassengerQueue class is working with one passenger
void test_passenger_one() {
    PassengerQueue pq;
    Passenger p(1, 2, 3);
    pq.enqueue(p);
    assert(pq.size() == 1);
    assert(pq.front().id == 1);
    assert(pq.front().from == 2);
    assert(pq.front().to == 3);
}

// Tests that the PassengerQueue class is working with multiple passengers
void test_passenger_multiple() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    Passenger p3(3, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    assert(pq.size() == 3);
    assert(pq.front().id == 1);
    assert(pq.front().from == 2);
    assert(pq.front().to == 3);
}

/*PassengerQueue::front()*/
// Tests that the PassengerQueue class is returning the front passenger 
// correctly in a queue with one passenger
void test_queue_front_one() {
    PassengerQueue pq;
    Passenger p(1, 2, 3);
    pq.enqueue(p);
    assert(pq.front().id == 1);
    assert(pq.front().from == 2);
    assert(pq.front().to == 3);
}

// Tests that the PassengerQueue class is returning the front passenger
void test_queue_front_many() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    Passenger p3(3, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    assert(pq.front().id == 1);
    assert(pq.front().from == 2);
    assert(pq.front().to == 3);
}

// Tests that the PassengerQueue class on an empty queue
void test_queue_front_empty() {
    PassengerQueue pq;
    try {
        pq.front();
        assert(false);
    } catch (std::range_error &e) {
        assert(true);
    }
}

/*PassengerQueue::dequeue()*/
// Tests that the PassengerQueue class is removing the front passenger 
// of a list with one passenger
void test_dequeue_one() {
    PassengerQueue pq;
    Passenger p(1, 2, 3);
    pq.enqueue(p);
    pq.dequeue();
    assert(pq.size() == 0);
}

// Tests that the PassengerQueue class is removing the front passenger
// of a list with multiple passengers
void test_dequeue_multiple() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    Passenger p3(3, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    pq.dequeue();
    assert(pq.size() == 2);
    assert(pq.front().id == 2);
    assert(pq.front().from == 3);
    assert(pq.front().to == 4);
}

// Tests that the PassengerQueue class is removing the front passenger
// of a list with no passengers
void test_dequeue_empty() {
    PassengerQueue pq;
    try {
        pq.dequeue();
        assert(false);
    } catch (std::range_error &e) {
        assert(true);
    }
}

/*PassenegrQueue::size*/
// Tests that the PassengerQueue class is returning the correct size of a list
// with one passenger
void test_queue_size_one() {
    PassengerQueue pq;
    Passenger p(1, 2, 3);
    pq.enqueue(p);
    assert(pq.size() == 1);
}

// Tests that the PassengerQueue class is returning the correct size of a list
// with multiple passengers
void test_queue_size_multiple() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    Passenger p3(3, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    assert(pq.size() == 3);
}

// Tests that the PassengerQueue class is returning the correct size of a list
// with no passengers
void test_queue_size_none() {
    PassengerQueue pq;
    assert(pq.size() == 0);
}

/*PassengerQueue::print(std::ostream &output)*/
// Tests that the PassengerQueue class is printing correctly with one passenger
void test_queue_print_one() {
    PassengerQueue pq;
    Passenger p(1, 2, 3);
    pq.enqueue(p);
    std::stringstream ss;
    pq.print(ss);
    assert(ss.str() == "[1, 2->3]");
}

// Tests that the PassengerQueue class is printing correctly with 
// multiple passengers
void test_queue_print_multiple() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    Passenger p3(3, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    std::stringstream ss;
    pq.print(ss);
    assert(ss.str() == "[1, 2->3][2, 3->4][3, 4->5]");
}

// Tests that the PassengerQueue class is printing correctly with no passengers
void test_queue_print_none() {
    PassengerQueue pq;
    std::stringstream ss;
    pq.print(ss);
    assert(ss.str() == "");
}
