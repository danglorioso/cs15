/*
 *  phaseOne.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 11/07/2023
 *
 *  CS 15 PROJECT 3: zap
 *
 *  PURPOSE: Declaration of three functions used to count frequencies of 
 *           charactersin a file, serialize a Huffman tree, and deserialize 
 *           a Huffman tree.
 *
 */

#include <istream>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "HuffmanTreeNode.h"

// Function declarations
void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);

// Helper functions
void serialize_recursive(HuffmanTreeNode *root, std::string &s);
HuffmanTreeNode *deserialize_recursive(std::istringstream &in);
