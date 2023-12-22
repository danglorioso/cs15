/* A simple program to demonstrate how to declare and use a min priority queue.
 * The min pq will contain pointers to instances of HuffmanTreeNode.
 *
 * Compile and link with the compiled HuffmanTreeNode class to run this program.
 * 
 * See C++ priority_queue documentation for more information:
 * https://cplusplus.com/reference/queue/priority_queue/
 *
 * Edited by: Milod Kazerounian, August 2022.
 */

#include "HuffmanTreeNode.h"
#include <queue>
#include <iostream>

using namespace std;

int main()
{
    // Declare some HuffmanTreeNodes with varying frequencies
    HuffmanTreeNode *node1 = new HuffmanTreeNode('a', 42);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('b', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('c', 100);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('d', 75);

    /* Declare our min priority queue. The priority_queue is instantiated
     * with three things:
     * 1) The type of priority_queue elements (in this case: HuffmanTreeNode*)
     * 2) The container used to represent the 
     *    priority queue (in this case: vector)
     * 3) The comparator function to use to pick "highest priority" element,
     *    (in this case, function referred to as: NodeComparator)
     */
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,
                   NodeComparator> my_pq;

    // Add our dummy nodes to the min priority_queue:
    my_pq.push(node1);
    my_pq.push(node2);
    my_pq.push(node3);
    my_pq.push(node4);

    /* Now, let's use top() and pop() on our priority queue, which will
     * respectively access and remove the minimum frequency element.
     */
    while(not my_pq.empty()) {
        HuffmanTreeNode *curr = my_pq.top();
        cerr << "Current top node contains character " << curr->get_val()
             << " and frequency " << curr->get_freq() << endl;

        my_pq.pop();
    }

    // Finally, recycle heap-allocated memory.
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    
    return 0;
}
