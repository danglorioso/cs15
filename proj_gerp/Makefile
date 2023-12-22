###
### Makefile
### Authors: Dan Glorioso (dglori02), Holden Kittelberger (hkitte01)
### Date: 11/30/2023
###
###  CS 15 PROJECT 4: gerp
###
###  PURPOSE: Makefile for gerp Project. gerp is a program that searches
###  through a directory of files for a given word or phrase.
###

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -O2 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -O2 

# Default rule that incorporates all .o files and compiles gerp
gerp: main.o Gerp.o File.o DirNode.o FSTree.o HashTable.o
	${CXX} ${LDFLAGS} -o $@ $^

# This rule builds main.o
main.o: main.cpp Gerp.h

# This rule builds Gerp.o
Gerp.o: Gerp.cpp Gerp.h DirNode.o FSTree.o File.o HashTable.o

# This rule builds File.o
File.o: File.cpp File.h

# This rule builds HashTable.o
HashTable.o: HashTable.cpp HashTable.h File.o

# This rule builds treeTraversal executable
treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o $@ $^

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h

# This rule builds stringProcessing.o
stringProcessing.o: stringProcessing.cpp stringProcessing.h

# The below rule will be used by unit_test.
# unit_test: unit_test_driver.o phaseOne.o HuffmanTreeNode.o ZapUtil.o
unit_test: unit_test_driver.o stringProcessing.o Gerp.o File.o DirNode.o FSTree.o HashTable.o
	$(CXX) $(CXXFLAGS) $^

hashExample: hashExample.o
	${CXX} ${LDFLAGS} -o $@ $^

hashExample.o: hashExample.cpp

hashTest: hash_test.o
	${CXX} ${LDFLAGS} -o $@ $^

hash_test.o: hash_test.cpp

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm stringProcessing.o FSTreeTraversal.o main.o *~ a.out
