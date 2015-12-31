/* 
 * File:   Rparser.h
 */

#ifndef RPARSER_H
#define	RPARSER_H

#include "Node.h"
#include "Resistor.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

extern int count_maxVal; // counts number of times maxVal has been called in 
                         // runtime

void Rparser(); // parse user input and search for command until eof is reached

bool resistorNameExists(string); // check if resistor exists name in 
                                 // resistorArray

int getResistorIndexFromName(string); // get index of resistor in resistorArray

void deleteAll(); // delete nodeArray, resistorArray and all dynamically 
                  // allocated resistors

// Functions for specific commands in user input

void insertR(stringstream&);

void modifyR(stringstream&);

void printR(stringstream&);

void printNode(stringstream&);

void deleteR(stringstream&);

#endif	/* RPARSER_H */

