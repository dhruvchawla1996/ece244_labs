/*
 * File: Main.cpp
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

// insert new node in binary tree database, prints success if successful
void insert( stringstream& ss, TreeDB& DNS_tree);
// find node in database by name, prints node details
void find( stringstream& ss, TreeDB& DNS_tree);
// removes node in database by seaching for name,  prints success if successful
void remove( stringstream& ss, TreeDB& DNS_tree);
// print details of all nodes in database
void printall( stringstream& ss, TreeDB& DNS_tree);
// print probes needed to find a particular node by name in database
void printprobes( stringstream& ss, TreeDB& DNS_tree);
// delete all entries in database
void removeall( stringstream& ss, TreeDB& DNS_tree);
// return active nodes in database
void countactive( stringstream& ss, TreeDB& DNS_tree);
// update status of node by seatching for name,  prints success if successful
void updatestatus( stringstream& ss, TreeDB& DNS_tree);

int main( int argc, char const *argv[] ) {
	if (argc > 1) {
		cout << "No other args should be given for this program" << endl;
		return -1;
	}
	string line; // store the cin input in the line
	TreeDB DNS_tree;

	while (1) { // loop until eof reached
		cout << "> "; // looks cooler
		getline(cin, line, '\n'); // read one line at a time

		if (cin.eof()) {
			break; 
		}

		stringstream ss(line); // initialize stringstream with user input
        string cmd;
        ss >> cmd; // get the command

        // call respective functions for each command
        if 		(cmd == "insert") 		insert(ss, DNS_tree);
        else if (cmd == "find") 		find(ss, DNS_tree);
        else if (cmd == "remove") 	    remove(ss, DNS_tree);
        else if (cmd == "printall") 	printall(ss, DNS_tree);
        else if (cmd == "printprobes")  printprobes(ss, DNS_tree);
        else if (cmd == "removeall")    removeall(ss, DNS_tree);
        else if (cmd == "countactive")  countactive(ss, DNS_tree);
        else if (cmd == "updatestatus") updatestatus(ss, DNS_tree);
        else cout << "Error: invalid command" << endl;
	}
	return 0;
}

void insert( stringstream& ss, TreeDB& DNS_tree) {
	string name, status;
	unsigned int IPaddress;
	bool active;

	ss >> name >> IPaddress >> status;

	if (status == "active") active = true;
	else if (status == "inactive") active = false;

	// dynamically allocate new entry
	DBentry* newEntry = new DBentry(name, IPaddress, active);

	if (!DNS_tree.insert(newEntry)) { // insert into tree
		// if you are in this condition, insertion was not successful
		cout << "Error: entry already exists" << endl;
        delete newEntry; // newEntry is not going anywhere :(
        newEntry = NULL;
		return;
	}
	cout << "Success" << endl; // insertion was successful
}

void find( stringstream& ss, TreeDB& DNS_tree) {
	string name;
	ss >> name;

	DBentry* entry = DNS_tree.find(name);

	if (entry == NULL) {
		cout << "Error: entry does not exist" << endl;
		return;
	}

	cout << *entry;
}

void remove( stringstream& ss, TreeDB& DNS_tree) {
	string name;
	ss >> name;

	if (!DNS_tree.remove(name)) {
		cout << "Error: entry does not exist" << endl;
		return;
	}
	cout << "Success" << endl;
}

void printall( stringstream& ss, TreeDB& DNS_tree) {
	cout << DNS_tree;
}

void printprobes( stringstream& ss, TreeDB& DNS_tree) {
	string name;
	ss >> name;

	DBentry* entry = DNS_tree.find(name);

	if (entry == NULL) {
		cout << "Error: entry does not exist" << endl;
		return;
	}

	DNS_tree.printProbes();
}

void removeall( stringstream& ss, TreeDB& DNS_tree) {
	DNS_tree.clear();
	cout << "Success" << endl;
}

void countactive( stringstream& ss, TreeDB& DNS_tree) {
	DNS_tree.countActive();
}

void updatestatus( stringstream& ss, TreeDB& DNS_tree) {
	string name, status;
	ss >> name >> status;

	DBentry* entry = DNS_tree.find(name);

	if (entry == NULL) {
		cout << "Error: entry does not exist" << endl;
		return;
	}

	if (status == "active") entry->setActive(true);
	else if (status == "inactive") entry->setActive(false);
	cout << "Success" << endl;
}