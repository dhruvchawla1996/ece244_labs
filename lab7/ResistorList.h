/* 
 * File:   ResistorList.h
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include <iostream>
#include <string>
#include "Resistor.h"

using namespace std;

class ResistorList {
private:
    Resistor* resHead; // head of linked list of resistors

    int count; // number of resistors in resistor list
public:
    ResistorList();
    
    ~ResistorList();
    
    void insertRes (string name, int endpoints[2], double resistance);
    // insert new resistor in linked list at the end
    
    Resistor* findRes (string name) const; 
    // find resistor given name, return pointer to resistor if found, otherwise
    // return NULL
    
    void deleteRes (Resistor* resistor); // delete resistance from list given
                                         // pointer to resistor

    void deleteAllRes (); // deletes all resistors in list

    double changeResistance (string name, double new_resistance);
    // change resistance of given resistor to new resistance. Checks if 
    // resistor exists in list first. Returns old value of reistance if 
    // successful, else returns -1

    int getCount () const; // returns number of resistor 
    
    Resistor* getResHead () const; // returns resHead

    bool printR (string name) const; // prints details of resistor in the list, 
    							     // prints nothing if resistor not in list

    void print () const; // prints all resistors in list
};

#endif	/* RESISTORLIST_H */

