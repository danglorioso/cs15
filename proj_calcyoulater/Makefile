###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author: Dan Glorioso (dglori02)

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Default rule that incorporates all .o files and compiles CalcYouLater
CalcYouLater: main.o Datum.o DatumStack.o DatumStack.o RPNCalc.o
	${CXX} ${LDFLAGS} -o $@ $^

# This rule builds main.o
main.o: main.cpp Datum.h DatumStack.h
	${CXX} ${CXXFLAGS} -c main.cpp

# This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h Datum.h DatumStack.h
	${CXX} ${CXXFLAGS} -c RPNCalc.cpp

# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	${CXX} ${CXXFLAGS} -c DatumStack.cpp

# This rule builds Parser.o
# Although not used in CalcYouLater since copied into RPNCalc.cpp as function, 
# included for unit_testing purposes
parser.o: parser.cpp parser.h Datum.h DatumStack.h
	${CXX} ${CXXFLAGS} -c parser.cpp

## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

# The below rule will be used by unit_test.
# Please add any other .o files that are needed by PassengerQueue,
# and any other .o files you wish to test. 
unit_test: unit_test_driver.o Datum.o DatumStack.o RPNCalc.o parser.o
	$(CXX) $(CXXFLAGS) $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

