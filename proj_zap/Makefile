###
### Makefile
### Author: Dan Glorioso (dglori02)
### Date: 11/07/2023
###
###  CS 15 PROJECT 3: zap
###
###  PURPOSE: Makefile for zap Project. zap is a compression/decompression
###           program for text files using the Huffman coding algorithm.
###

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Default rule that incorporates all .o files and compiles zap
zap: main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o
	${CXX} ${LDFLAGS} -o $@ $^

# This rule builds main.o
main.o: main.cpp HuffmanCoder.h BinaryIO.o
	${CXX} ${CXXFLAGS} -c main.cpp

# This rule builds phaseOne.o
# Note this rule has been commented out because it is not used in the final
# phaseOne.o: phaseOne.cpp phaseOne.h
# 	${CXX} ${CXXFLAGS} -c phaseOne.cpp

# This rule builds HuffmanCoder.o
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryIO.o
	${CXX} ${CXXFLAGS} -c HuffmanCoder.cpp

# The below rule will be used by unit_test.
# unit_test: unit_test_driver.o phaseOne.o HuffmanTreeNode.o ZapUtil.o
unit_test: unit_test_driver.o HuffmanTreeNode.o ZapUtil.o
	$(CXX) $(CXXFLAGS) $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
