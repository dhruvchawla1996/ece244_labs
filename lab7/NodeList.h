/* 
 * File:   NodeList.h
 */

#ifndef NODELIST_H
#define	NODELIST_H

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "Node.h"

using namespace std;

class NodeList {
private:
    Node* nodeHead; // points to first node in linked list, is NULL if no
                    // nodes exist in NodeList
public:
    NodeList ();

    ~NodeList ();

    Node* findOrInsertNode (int id); // finds node if exists by id, else 
    								 // creates new node and stores it in 
    								 // the linkded list by asccending order
    								 // of id. Returns pointer to new node

    bool resistorExists (string name) const; // finds whether resistor exists 
    										 // in list

    double changeResistance (string name, double new_resistance);
    // change reistance of resistor with specified name, returns old 
    // resistance if successful, -1 if not

    bool deleteResistor (string name); 
    // finds resistor by name in all nodes, returns true if search and deletion
    // successful

    void deleteAllResistors (); // delete all resistors in all nodes

    void printResistor (string name) const; 
    // finds resistor by name and prints details

    void print (int id) const; // print details of a specific node

    void printAll () const; // prints details of all nodes

    bool voltageSet () const; // checks if voltage has been set on any node

    void solve (); // solve voltage at every node
    
    void solveForDraw();
    
    void clearNodes (); 
    // deletes node(s) in list which have no connections or no assigned voltage
    
    void set_draw_coords (float& xleft, float& ybottom, float& xright, float& ytop);
    
    void draw ();
};

#endif	/* NODELIST_H */

