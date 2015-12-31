/* 
 * File:   Main.cpp
 */

#include <cstdlib>
#include "Rparser.h"
#include "Resistor.h"
#include "Node.h"

using namespace std;

Resistor **resistorArray = NULL; // stores pointers to Resistors, initialized 
                                 // to null
Node *nodeArray = NULL; // stores Nodes in the circuit, initialized to null
int resCount = 0; // number of resistors currently in circuit, initialized to 0
int maxNodeNumber = 0; // max nodes allowed in the circuit, initialized to 0
int maxResistors = 0; // max resistors allowed in the circuit, initialized to 0

int main() {
    Rparser(); // call parser to parse user inputs
    return 0;
}

