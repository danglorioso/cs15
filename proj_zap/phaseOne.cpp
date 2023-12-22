/*
 *  phaseOne.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 11/07/2023
 *
 *  CS 15 PROJECT 3: zap
 *
 *  PURPOSE: Definition of three functions used to count frequencies of
 *           characters in a file, serialize a Huffman tree, and deserialize
 *           a Huffman tree.
 *
 */

#include <istream>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "phaseOne.h"
#include "HuffmanTreeNode.h"

/* count_freqs(std::istream &text)
 *    Purpose: Reads characters from the input stream and counts the number of
 *             occurances for each character in the stream, including spaces 
 *             and line break, and then prints the results to cout. 
 * Parameters: istream &text - the input stream to read from
 *     Return: None
 */
void count_freqs(std::istream &text) {
    std::unordered_map<char, int> freqs;
    char c;

    // for the entire input, increment frequency of each character
    while (text.get(c)) {
        freqs[c]++;
    }

    // print the frequencies of each character
    for (const auto entry : freqs) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

/* serialize_tree(HuffmanTreeNode *root)
 *    Purpose: Serializes a Huffman tree into a string using a preorder 
 *             traversal with "I" to represent an internal node and "L" 
 *             followed by a char to represent a leaf node. The resulting 
 *             string is returned.
 * Parameters: HuffmanTreeNode *root - the root of the Huffman tree to 
 *             serialize as input
 *     Return: std::string - the serialized Huffman tree
 */
std::string serialize_tree(HuffmanTreeNode *root) {
    // initalize empty string
    std::string s = "";

    // call recursive function
    serialize_recursive(root, s);

    // return full serialized string
    return s;
}

/*serialize_recursive(HuffmanTreeNode *root, std::string &s)
 *    Purpose: Recursive helper function for serialize_tree. Used to traverse 
 *             the tree and add the appropriate characters to the string.
 * Parameters: HuffmanTreeNode *root - the root of the Huffman tree to 
 *             serialize as input
 *             std::string &s - the string to append the serialized tree to
 *     Return: std::string - the serialized Huffman tree
 */
void serialize_recursive(HuffmanTreeNode *root, std::string &s) {
    if (root == nullptr) { 
        return;
    }
    // if leaf node, then L followed by char
    if (root->isLeaf()) {
        s += "L";
        s += root->get_val();
        return;
    } else {
        // if right and left chlid exist, then internal node
        s += "I";
        serialize_recursive(root->get_left(), s);
        serialize_recursive(root->get_right(), s);
    }
}

/* deserialize_tree(const std::string &s)
 *    Purpose: Deserializes a Huffman tree from a string by reconstructing the
 *             tree from the string and reutrning a pointer to its root. 
 *             Allocates memory on the heap for the new nodes. 
 * Parameters: const std::string &s - a serialized tree as a the string to 
 *             deserialize
 *     Return: HuffmanTreeNode * - the root of the deserialized Huffman tree
 */
HuffmanTreeNode *deserialize_tree(const std::string &s) {
    std::istringstream in(s);
    return deserialize_recursive(in);
}

/* deserialize_recursive(istringstream &in)
 *    Purpose: Recursive helper function for deserialize_tree. Used to traverse
 *             the string and reconstruct the tree.
 * Parameters: istringstream &in - the string to deserialize
 *     Return: HuffmanTreeNode * - the root of the deserialized Huffman tree
 */
HuffmanTreeNode *deserialize_recursive(std::istringstream &in) {
    char c;

    // if end of string, return nullptr
    if (not(in.get(c))) {
        return nullptr;
    }
    // if leaf node, create new node and set value to next char in string
    if (c == 'L') {
        in.get(c);
        HuffmanTreeNode *node = new HuffmanTreeNode(c, 0);
        return node;
    } else {
        // if internal node, create new node and set left and right
        HuffmanTreeNode *node = new HuffmanTreeNode('\0', 0);
        node->set_left(deserialize_recursive(in));
        node->set_right(deserialize_recursive(in));
        return node;
    }
}
