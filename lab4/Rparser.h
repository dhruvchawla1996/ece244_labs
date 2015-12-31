/* 
 * File:   Rparser.h
 */

#ifndef RPARSER_H
#define	RPARSER_H

#include "NodeList.h"
#include "ResistorList.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void Rparser(NodeList*&); 
// parse user input and search for command until eof is reached


// Functions for specific commands in user input

void setV(stringstream&, NodeList*&);

void unsetV(stringstream&, NodeList*&);

void solve(stringstream&, NodeList*&);

void insertR(stringstream&, NodeList*&);

void modifyR(stringstream&, NodeList*&);

void printR(stringstream&, NodeList*&);

void printNode(stringstream&, NodeList*&);

void deleteR(stringstream&, NodeList*&);

#endif	/* RPARSER_H */

