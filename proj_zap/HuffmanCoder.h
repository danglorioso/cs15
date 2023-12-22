/*
 *  HuffmanCoder.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 11/07/2023
 *
 *  CS 15 PROJECT 3: zap
 *
 *  PURPOSE: Implementation of the HuffmanCoder class, which is used to encode
 *           and decode text files using Huffman coding. This class also stores
 *           member variables for the Huffman tree and character codes.
 *           Content include a constructor, destructor, and functions 
 *           including encoder, decoder, and helper functions.
 *
 */
 
#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include "HuffmanTreeNode.h"

class HuffmanCoder {
public:
    // Constructor
    HuffmanCoder();

    // Destructor
    ~HuffmanCoder();

    // Encoder and Decoder functions
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

private:
    // Helper functions
    template<typename streamtype>
    void open_or_die(streamtype &stream, std::string filename);
    bool file_empty(std::ifstream &input);
    void delete_tree(HuffmanTreeNode *root);

    // Encode helper functions
    void count_freqs(std::istream &text);
    void build_tree();
    void make_char_codes(HuffmanTreeNode *root, std::string s);
    std::string encode_text(std::istream &text);
    std::string serialize_tree(HuffmanTreeNode *root);
    void serialize_recursive(HuffmanTreeNode *root, std::string &s);

    // Decode helper functions
    HuffmanTreeNode *deserialize_recursive(std::istringstream &in);
    std::string decode_text(HuffmanTreeNode *root, std::istream &text); 
    
    // Member variables
    std::unordered_map<char, int> freqs;
    std::unordered_map<char, std::string> char_codes;
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>,
                NodeComparator> my_pq;
    HuffmanTreeNode *root_node;
};

#endif