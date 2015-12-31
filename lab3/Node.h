/*
 * File: Node.h
 */

#ifndef NODE_H
#define NODE_H

#include "Resistor.h"
#include "Rparser.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define MAX_RESISTORS_PER_NODE 5

class Node {
    private:
        int numRes; // number of resistors currently connected
        int resIDArray[MAX_RESISTORS_PER_NODE];
        // stores the index of each resistor connected
    public:
        Node();
        
        ~Node();
        
        bool addResistor(int rIndex);
        // Updates resIDArray to show the resistor in position rIndex in
        // the resistor array is now connected to this node.
        // Returns true if successful
        
        void print(int nodeIndex);
        // prints the whole node
        // nodeIndex is the position of this node in the node array.
        
        bool isNodeFull();
        // returns true if node is full
};

// get global variables initialized in Main.cpp
extern Resistor **resistorArray; // stores pointers to Resistors
extern Node *nodeArray; // stores Nodes in the circuit
extern int resCount; // number of resistors currently in circuit
extern int maxNodeNumber; // max nodes allowed in the circuit
extern int maxResistors; // max resistors allowed in the circuit

#endif /* NODE_H */