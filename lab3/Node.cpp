/*
 * File: Node.cpp 
 */

#include "Node.h"

using namespace std;

Node::Node() {
    numRes = 0; // number of resistors connected to the node is 0 in the 
                // beginning
}

Node::~Node(){}

bool Node::addResistor(int rIndex) {
    if (numRes < MAX_RESISTORS_PER_NODE) { // check for free space in the node
        resIDArray[numRes] = rIndex; // store ID of resistor connected
        numRes++; // increment no. of resistors connected
        return true; // resistor successfully inserted
    } else {
        return false; // resistor insertion not successful because of no 
                      // free space in node
    }
}

void Node::print(int nodeIndex) {
    // print number of resistors connected to node
    cout<<"Connections at node "<<nodeIndex<<": "<<numRes<<" resistor(s)"<<endl;
    
    // print details of each resistor connected to node
    for (int i = 0; i < numRes; i++) {
        cout<<"  ";
	resistorArray[resIDArray[i]]->print();
    }
}

bool Node::isNodeFull() {
    // check if number of resistors connected to node is >= to max capacity of 
    // node
    return numRes >= MAX_RESISTORS_PER_NODE;
}
