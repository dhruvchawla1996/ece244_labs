/*
 * File: Node.h
 */

#ifndef NODE_H
#define NODE_H

#include "ResistorList.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Node {
    friend class NodeList;
private:
    int id; // node id
    ResistorList resList; // linked list of resistors connected to node
    bool isVoltageSet; // specifies if node voltage is set by setV command
    double voltage; // voltage at node
    Node* next; // pointer to next node in NodeList
public:
    Node(int id_);
    
    ~Node();
    
    void setVoltage (double voltage_); 
    // sets Volatge specified by user in setV command 

    void setVoltageForSolver (double voltage_);
    // sets voltage of node for solver, only affects voltage if voltage
    // has not been set by user
    
    void unsetVoltage (); // called by unsetV command

    bool is_voltage_set () const; // returns true if voltage has been
                                  // specified by user

    double getVoltage () const; // returns voltage
    
    void addResistor (string name, int endpoints_[2], double resistance); 
    // adds resistor to node's resistor list

    bool findResistor (string name) const;
    // finds resistor by name in resList, returns true if found

    double changeResistance (string name, double new_resistance);
    // change reistance of resistor with specified name, returns old 
    // resistance if successful, -1 if not

    bool deleteResistor (string name); // finds resistor in resList, returns 
                                       // true if found

    void deleteAllResistors (); // deletes all resistors connected to node
    
    void print () const;
    // prints details of resistor connected to node
    // if node has no resistors connected, prints voltage set by user
    // prints nothing if node voltage has not been set and node is not 
    // connected

    bool printResistor (string name) const; // finds resistor by name in 
                                            // resList and prints details 

    Node* getNext () const; // get next node pointer

    void setNext (Node* next_); // set next node

    int getID () const;

    void setID (int id_);
    
    int getNumberOfResistorsConnected () const;
};

#endif /* NODE_H */