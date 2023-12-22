/*
 *  unit_tests.h
 *  Author: Dan Glorioso (dglori02)
 *  Date: 11/07/2023
 * 
 *  CS 15 PROJECT 3: zap
 * 
 *  PURPOSE: To test the functionality of the PhaseOne functions using the
 *           unit testing framework with a variety of tests that cover
 *           possible cases.
 * 
 */

#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

/*Dummy Test*/
// Tests that the unit_tests is working
void dummy_test() {
    assert(true);
}

/********************************************************************\
*                       PHASEONE FUNCTIONS                           *
\********************************************************************/
/*count_freqs(istream &text)*/
// Tests that the count_freqs function is working with one character input
void test_count_freqs_one_char() {
    std::stringstream ss;
    ss << "a";

    // Redirect std::cout to ss2
    std::stringstream ss2;
    auto old_cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(ss2.rdbuf());

    count_freqs(ss);

    // Restore old cout buffer
    std::cout.rdbuf(old_cout_buffer);

    assert(ss2.str() == "a: 1\n");
}

// Tests the count_freq function with an empty input
void test_count_freqs_empty() {
    std::stringstream ss;
    ss << "";

    // Redirect std::cout to ss2
    std::stringstream ss2;
    auto old_cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(ss2.rdbuf());

    count_freqs(ss);

    // Restore old cout buffer
    std::cout.rdbuf(old_cout_buffer);

    assert(ss2.str() == "");
}

/*serialize_tree(HuffmanTreeNode *root)*/
// Tests the serialize_tree function with a tree with one node
void test_serialize_tree_one_node() {
    HuffmanTreeNode *root = new HuffmanTreeNode('a', 1);

    assert(serialize_tree(root) == "La");
}

// Tests the serialize_tree function with an empty tree
void test_serialize_tree_empty() {
    HuffmanTreeNode *root = nullptr;

    assert(serialize_tree(root) == "");
}

// Tests the serialize_tree function with Figure1 tree
void test_serialize_tree_figure1() {
    HuffmanTreeNode *fig1Tree = makeFigure1Tree('\0');
    std::string s = serialize_tree(fig1Tree);
    assert(s == "IIILaLbILeLfILcLd");
}

/*deserialize_tree(const std::string &s)*/
// Tests the deserialize_tree function with a tree with two leaves
void test_deserialize_tree_one_node() {
    // Serialized tree string
    std::string serialized_tree = "ILaLb";

    // Deserialize the tree
    HuffmanTreeNode* root = deserialize_tree(serialized_tree);

    // Check that the tree is same as the original
    assert(root->get_val() == '\0');
}

// Tests the deserialize_tree function with Figure1 tree
void test_deserialize_tree_figure1() {
    // Serialized tree string
    std::string serialized_tree = "IIILaLbILeLfILcLd";

    // Deserialize the tree
    HuffmanTreeNode* root = deserialize_tree(serialized_tree);

    // Check that the tree is same as the original
    assert(treeEquals(root, makeFigure1Tree('\0'), false, false));
}

// Tests the deserialize_tree function with a tree with one leaf
void test_deserialize_tree_one_leaf() {
    // Serialized tree string
    std::string serialized_tree = "La";

    // Deserialize the tree
    HuffmanTreeNode* root = deserialize_tree(serialized_tree);

    // Check that the tree is same as the original
    assert(root->get_val() == 'a');
}
