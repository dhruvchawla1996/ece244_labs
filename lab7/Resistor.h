/*
 * File: Resistor.h
 */

#ifndef RESISTOR_H
#define RESISTOR_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Resistor {
    friend class ResistorList;
private:
    double resistance; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    Resistor* next; // points to next resistor in linked list
public:
    Resistor(string name_, double resistance_, int endpoints_[2],\
            Resistor* next_);
   
    ~Resistor();

    string getName() const; // returns the name

    double getResistance() const; // returns the resistance

    void setResistance (double resistance_); // sets resistance
    
    Resistor* getNext () const; // returns next resistor pointer
    
    void setNext (Resistor* next_); // sets next resistor pointer

    int getOtherNodeID (int this_node_id); 
    // returns nodeID of other node connected to resistor given nodeID of a 
    // node
    
    int getEndpointOne () ;
   int getEndpointTwo () ;
    
    
    void print (); // prints resistor details
    
    // ignore this function for now, might use it in the future
    friend ostream& operator<<(ostream&,const Resistor&);
};

ostream& operator<<(ostream&,const Resistor&);

#endif /* RESISTOR_H */
