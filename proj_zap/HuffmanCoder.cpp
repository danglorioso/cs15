/*
 *  HuffmanCoder.cpp
 *  Author: Dan Glorioso (dglori02)
 *  Date: 11/07/2023
 *
 *  CS 15 PROJECT 3: zap
 *
 *  PURPOSE: Implementation of the HuffmanCoder class, which is used to encode
 *           and decode text files using Huffman coding. This class also stores
 *           member variables for the Huffman tree and character codes. This
 *           class contains a constructor, destructor, and functions including
 *           encoder, decoder, and helper functions. Helper functions include
 *           functions to open files, check if files are empty, count 
 *           frequencies of characters, build a Huffman tree, generate 
 *           character codes, encode text, serialize a Huffman tree, 
 *           deserialize a Huffman tree, and decode text. 
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <utility>
#include "HuffmanCoder.h"
#include "BinaryIO.h"

using namespace std;

/* HuffmanCoder()
 *    Purpose: Initializes the root of the Huffman tree to nullptr
 * Parameters: None
 *     Return: None
 */
HuffmanCoder::HuffmanCoder() {
    // set root to nullptr
    root_node = nullptr;
}

/* ~HuffmanCoder()
 *    Purpose: Deletes the Huffman tree from memory by calling the recursive
 *             delete_tree function
 * Parameters: None
 *     Return: None
 */
HuffmanCoder::~HuffmanCoder() {
    // delete Huffman tree by calling recursive function
    delete_tree(root_node);
}

/* encoder(const std::string &inputFile, const std::string &outputFile)
 *    Purpose: Encodes a given ASCII text file into compressed binary code. 
 *             This function uses a series of helper functions to count the
 *             frequencies of characters in the input file, build a Huffman
 *             tree, generate character codes, encode the text, and serialize
 *             the Huffman tree. The resulting serialized tree and encoded
 *             text are saved in a binary file.
 * Parameters: const std::string &inputFile - the name of the input file
 *             const std::string &outputFile - the name of the output file
 *     Return: None
 */
void HuffmanCoder::encoder(const std::string &inputFile, 
                                               const std::string &outputFile) {
    // Open input and output files
    ifstream input;
    open_or_die(input, inputFile);

    if (file_empty(input)) {
        std::cout << inputFile << " is empty and cannot be compressed." 
                  << std::endl;
    } else {
        // Count frequencies of each character in input file (stream)
        count_freqs(input);
        // Build Huffman tree from frequencies
        build_tree();
        // Generate character codes from Huffman tree
        make_char_codes(root_node, "");
        // Reset input file stream
        input.close();
        open_or_die(input, inputFile);
        // Encode input file using Huffman tree
        std::string encoded_s = encode_text(input);
        // Serialize Huffman tree
        std::string serialized_s = serialize_tree(root_node);
        // Save the serialize tree and encoded text in the file
        BinaryIO binary;
        binary.writeFile(outputFile, serialized_s, encoded_s);
        // Print confirmation message
        std::cout << "Success! Encoded given text using " << encoded_s.size() 
                << " bits." << std::endl;
    }
    // Close file and recycle memory
    input.close();
}

/* decoder(const std::string &inputFile, const std::string &outputFile)
 *    Purpose: Decodes a given compressed binary file into an ASCII text file.
 *             This function uses a series of helper functions to read the
 *             serialized Huffman tree and encoded binary string from the
 *             input file, deserialize the Huffman tree, decode the binary
 *             string into ASCII text, and save the ASCII text to an output
 *             file.
 * Parameters: const std::string &inputFile - the name of the input file
 *             const std::string &outputFile - the name of the output file
 *     Return: None
 */
void HuffmanCoder::decoder(const std::string &inputFile, 
                                               const std::string &outputFile) {
    // Open input and output files
    ifstream input;
    open_or_die(input, inputFile);

    // Read zap file to get the serialized tree and encoded binary string
    BinaryIO binary;
    std::pair<std::string, std::string> zap = binary.readFile(inputFile);

    // Deserialize Huffman tree
    std::istringstream serialize_in(zap.first); // open stringstream
    root_node = deserialize_recursive(serialize_in);

    // Use tree to decode the binary string into ASCII text
    std::istringstream encoded_in(zap.second); // open stringstream
    std::string decoded_s = decode_text(root_node, encoded_in);

    // Save the ASCII text to an output file
    ofstream output;
    open_or_die(output, outputFile);
    output << decoded_s;

    // Close files
    input.close();
    output.close();
}

/* open_or_die(streamtype &stream, std::string filename)
 *    Purpose: Opens the input files and checks for errors. 
 *             If the file cannot be opened, the program exits with an error
 *             message.
 * Parameters: streamtype &stream - the input file stream
 *             std::string filename - the name of the input file
 *     Return: None
 */
template<typename streamtype>
void HuffmanCoder::open_or_die(streamtype &stream, std::string filename) {
    // open input file
    stream.open(filename);

    // check if filestream is open
    if (not stream.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }
}

/* file_empty(std::ifstream &input)
 *    Purpose: Checks if the input file is empty
 * Parameters: std::ifstream &input - the input file stream
 *     Return: bool - true if file is empty, false otherwise
 */
bool HuffmanCoder::file_empty(std::ifstream &input) {
    // check if file is empty
    if (input.peek() == std::ifstream::traits_type::eof()) {
        return true;
    }
    return false;
}

/* delete_tree(HuffmanTreeNode *root)
 *    Purpose: Deletes the Huffman tree from memory using recursive calls.
 * Parameters: HuffmanTreeNode *root - the root of the Huffman tree
 *     Return: None
 */
void HuffmanCoder::delete_tree(HuffmanTreeNode *root) {
    // Base case: if root is nullptr, return
    if (root == nullptr) {
        return;
    }
    // Recursive case: delete left and right children
    delete_tree(root->get_left());
    delete_tree(root->get_right());
    // delete root
    delete root;
    root = nullptr;
}

/* count_freqs(std::istream &text)
 *    Purpose: Reads characters from the input stream and counts the number of
 *             occurances for each character in the stream, including spaces 
 *             and line break, and stores the frequencies in an unordered map.
 * Parameters: istream &text - the input stream to read from
 *     Return: None
 */
void HuffmanCoder::count_freqs(std::istream &text) {
    // for the entire input, increment frequency of each character
    char c;
    while (text.get(c)) {
        freqs[c]++;
    }
}

/* build_tree()
 *    Purpose: Builds a Huffman tree, which is a binary tree with leaves
 *             corresponding to characters with least frequent characters
 *             farther from the root, from the frequencies of characters in the 
 *             input file.
 * Parameters: None
 *     Return: None
 */
void HuffmanCoder::build_tree() {
    // create a HuffmanTreeNode for each character and add to priority queue
    for (const auto entry : freqs) {
        HuffmanTreeNode *node = new HuffmanTreeNode(entry.first, entry.second);
        my_pq.push(node);
    }

    // check if only one character in input file
    if (my_pq.size() == 1) {
        HuffmanTreeNode *node = new HuffmanTreeNode('\0', 0);
        my_pq.push(node);
    }

    // pick two mins freqs from pq and join them together until a single tree 
    while (my_pq.size() > 1) {
        HuffmanTreeNode *left = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *right = my_pq.top();
        my_pq.pop();

        // create new internal node with sum of frequencies of children
        HuffmanTreeNode *parent = new HuffmanTreeNode('\0', 
                                                      left->get_freq() + 
                                                      right->get_freq());
        parent->set_left(left);
        parent->set_right(right);

        // add new internal node to priority queue
        my_pq.push(parent);
    }

    // set root to the last remaining node in the priority queue
    root_node = my_pq.top();
}

/* make_char_codes()
 *    Purpose: Generates binary codes from the Huffman tree for each character.
 *             The codes are stored in a map with the character as the key and
 *             the code as the value.
 * Parameters: HuffmanTreeNode *root - the root of the Huffman tree
 *             std::string s - the string to append the serialized tree to
 *     Return: None
 */
void HuffmanCoder::make_char_codes(HuffmanTreeNode *root, std::string s) {
    // Base case: if root is nullptr, return
    if (root == nullptr) {
        s = "";
        return;
    }
    // Recursive case: if leaf node, add character code to map
    if (root->isLeaf()) {
        char_codes[root->get_val()] = s;
        return;
    } else {
        make_char_codes(root->get_left(), s + "0");
        make_char_codes(root->get_right(), s + "1");
        return;
    }
}

/* encode_text(std::istream &text)
 *    Purpose: Encodes the input file using the Huffman tree. Each character
 *             is replaced with its corresponding binary code. The resulting
 *             string is returned.
 * Parameters: std::istream &text - the input stream to read from
 *     Return: std::string - the encoded text
 */
std::string HuffmanCoder::encode_text(std::istream &text) {
    // initalize empty string
    std::string s = "";

    // for the entire input, replace each character with its binary code
    char c;
    while (text.get(c)) {
        s += char_codes[c];
    }

    // return encoded text
    return s;
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
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    // initalize empty string
    std::string s = "";

    // if one character in input file, return "L" followed by char
    if (root->isLeaf()) {
        s += "L";
        s += root->get_val();
        return s;
    }

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
void HuffmanCoder::serialize_recursive(HuffmanTreeNode *root, std::string &s) {
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

/* HuffmanTreeNode *deserialize_recursive(std::istringstream &in)
 *    Purpose: Recursive helper function for deserialize_tree. Used to traverse
 *             the string and reconstruct the tree.
 * Parameters: istringstream &in - the istringstream to deserialize
 *     Return: HuffmanTreeNode * - the root of the deserialized Huffman tree
 */
HuffmanTreeNode *HuffmanCoder::deserialize_recursive(std::istringstream &in) {
    char c;

    // if end of string, return nullptr
    if (not(in.get(c))) {
        return nullptr;
    }

    // if pq only have 1 node, return that node
    if (my_pq.size() == 1) {
        return my_pq.top();
    // if leaf node, create new node and set value to next char in string
    } else if (c == 'L') {
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

/* decode_text(HuffmanTreeNode *root, std::istream &text, std::ostream &out)
 *    Purpose: Decodes the input file using the Huffman tree. Each binary code
 *             is replaced with its corresponding character. The resulting
 *             string is returned.
 * Parameters: HuffmanTreeNode *root - the root of the Huffman tree
 *             std::istream &text - the input stream to read from 
 *     Return: std::string - the decoded text
 */
std::string HuffmanCoder::decode_text(HuffmanTreeNode *root, 
                                                        std::istream &text) {
    // initalize empty string
    std::string s = "";

    // set node to root so it is not destructive
    char c;
    HuffmanTreeNode *node = root;

    // for the entire input, replace each character with its binary code
    while (text.get(c)) {
        // Base case: if leaf node, add character and reset node to root_node
        if (node->isLeaf()) {
            s += node->get_val();
            node = root_node;
        }
        // If internal node, traverse tree
        if (c == '0') {
            node = node->get_left();
        } else if (c == '1') {
            node = node->get_right();
        }
    }

    // Check if last character is a leaf node
    if (node->isLeaf()) {
        s += node->get_val();
    } else {
        throw std::runtime_error("Encoding did not match Huffman tree.");
    }
    // return encoded text
    return s;
}
