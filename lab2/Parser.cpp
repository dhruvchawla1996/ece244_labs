// Parser.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#define MAX_NODE_NUMBER 5000

void parser () {
    string line; // string to store lines inputted
    
    while (1) {
        cout << "> ";
        getline(cin, line, '\n'); // read lines from terminal
        
        if (cin.eof()) {
            break; // break out of loop if no input
        }
        
        stringstream ss(line); // initialize stringstream with line
        string cmd; ss >> cmd; // get the command
        
        if (cmd == "insertR") {
            if (ss.eof()) { // checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            string name; ss >> name; // get name
            if (ss.fail()) {
                cout << "Error: too few arguments" << endl;
                continue;
            }
            if (name == "all") {
                cout << "Error: resistor name cannot be the keyword \"all\""
                        << endl;
                continue;
            }
            if (ss.eof()) { //checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            double resistance; ss >> resistance; // get resistance
            if (ss.fail()) { // check if resistance is indeed a double
                ss.clear();
		string invalid_arg; ss >> invalid_arg;
		if (ss.fail()){
		    cout << "Error: too few arguments" << endl;
		    continue;
		}
		cout << "Error: invalid argument" << endl;
                continue;
            }
            if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' && 
                ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' && 
                ss.peek() != '\f') { 
                // check for next chars in input
                cout << "Error: invalid argument" << endl;
                continue;
            }
            if (resistance < 0) { // check for negative resistance
                cout << "Error: negative resistance" << endl;
                continue;
            }
            if (ss.eof()) { //checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            int node1; ss >> node1;
            if (ss.fail()) { // check if nodeid is an int
                ss.clear();
		string invalid_arg; ss >> invalid_arg;
		if (ss.fail()){
		    cout << "Error: too few arguments" << endl;
		    continue;
		}
		cout << "Error: invalid argument" << endl;
                continue;
            }
            if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' && 
                ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' && 
                ss.peek() != '\f') { 
                // check for next chars in input
                cout << "Error: invalid argument" << endl;
                continue;
            }
            if (node1 < 0 || node1 > MAX_NODE_NUMBER) { 
                // check if nodeid is in range
                cout << "Error: node " << node1 
                    << " is out of permitted range 0-" 
                    << MAX_NODE_NUMBER << endl;
                continue;
            }
            if (ss.eof()) { //checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            int node2; ss >> node2;
            if (ss.fail()) { // check if nodeid is an int
                ss.clear();
		string invalid_arg; ss >> invalid_arg;
		if (ss.fail()){
		    cout << "Error: too few arguments" << endl;
		    continue;
		}
		cout << "Error: invalid argument" << endl;
                continue;
            }
            if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' && 
                ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' && 
                ss.peek() != '\f') { 
                // check for next chars in input
                cout << "Error: invalid argument" << endl;
                continue;
            }
            if (node2 < 0 || node2 > MAX_NODE_NUMBER) { 
                // check if nodeid is in range
                cout << "Error: node " << node2 
                    << " is out of permitted range 0-" 
                    << MAX_NODE_NUMBER << endl;
                continue;
            }
            if (node1 == node2) { // check if resistor is connected to both
                // terminals
                cout << "Error: both terminals of resistor connect to node " 
                    << node1 << endl;
                continue;
            }
            string junk; ss >> junk; // get junk chars at the end of input
            if (!ss.fail()) { // there should not be any more args
                cout << "Error: too many arguments" << endl;
                continue;
            }
            // display output
            cout << "Inserted: resistor " + name + " " 
                << setprecision(2) << fixed << resistance
                << " Ohms " << node1 << " -> " << node2 << endl;
        } else if (cmd == "modifyR") {
            if (ss.eof()) { // checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            string name; ss >> name; // get name
            if (ss.fail()) {
                cout << "Error: too few arguments" << endl;
                continue;
            }
            if (name == "all") {
                cout << "Error: resistor name cannot be the keyword \"all\""
                        << endl;
                continue;
            }
            if (ss.eof()) { //checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            double resistance; ss >> resistance; // get resistance
            if (ss.fail()) { // check of resistance is indeed a double
                ss.clear();
		string invalid_arg; ss >> invalid_arg;
		if (ss.fail()){
		    cout << "Error: too few arguments" << endl;
		    continue;
		}
		cout << "Error: invalid argument" << endl;
                continue;
            }
            if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' && 
                ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' && 
                ss.peek() != '\f') { 
                // check for next chars in input
                cout << "Error: invalid argument" << endl;
                continue;
            }
            if (resistance < 0) { // check for negative resistance
                cout << "Error: negative resistance" << endl;
                continue;
            }
            string junk; ss >> junk; // get junk chars at the end of input
            if (!ss.fail()) { // there should not be any more args
                cout << "Error: too many arguments" << endl;
                continue;
            }
            // display output with 2 decimal accuracy
            cout << "Modified: resistor " + name + " to "  
                << setprecision(2) << fixed << resistance << " Ohms" 
                << endl;
        } else if (cmd == "printR") {
            if (ss.eof()) { // checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            string name; ss >> name; // get name
            if (ss.fail()) {
                ss.clear();
		string invalid_arg; ss >> invalid_arg;
		if (ss.fail()){
		    cout << "Error: too few arguments" << endl;
		    continue;
		}
		cout << "Error: too few arguments" << endl;
                continue;
            }
            string junk; ss >> junk; // get junk chars at the end of input
            if (!ss.fail()) { // there should not be any more args
                cout << "Error: too many arguments" << endl;
                continue;
            }
            if (name == "all") { // check for keyword "all"
                cout << "Print: all resistors" << endl;
            } else {
                cout << "Print: resistor " + name << endl;
            }
        } else if (cmd == "printNode") {
            if (ss.eof()) { // checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            int node; ss >> node;
            if (ss.fail()) {
                ss.clear();
                string node_string; ss >> node_string;
                if (ss.fail()) {
                    cout << "Error: too few arguments" << endl;
                    continue;
                }
                if (node_string != "all") {
                    cout << "Error: invalid argument" << endl;
                    continue;
                }
                string junk; ss >> junk; // get junk chars at the end of input
                if (!ss.fail()) { // there should not be any more args
                    cout << "Error: too many arguments" << endl;
                    continue;
                }
                cout << "Print: all nodes" << endl;
                continue;
            }
            if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' && 
                ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' && 
                ss.peek() != '\f') {  
                // check for next chars in input
                cout << "Error: invalid argument" << endl;
                continue;
            }
            if (node < 0 || node > MAX_NODE_NUMBER) { 
                // check if nodeid is in range
                cout << "Error: node " << node 
                    << " is out of permitted range 0-" 
                    << MAX_NODE_NUMBER << endl;
                continue;
            }
            string junk; ss >> junk; // get junk chars at the end of input
            if (!ss.fail()) { // there should not be any more args
                cout << "Error: too many arguments" << endl;
                continue;
            }
            cout << "Print: node " << node << endl;
        } else if (cmd == "deleteR") {
            if (ss.eof()) { // checks for further args
                cout << "Error: too few arguments" << endl;
                continue;
            }
            string name; ss >> name; // get name
            if (ss.fail()) {
                ss.clear();
		string invalid_arg; ss >> invalid_arg;
		if (ss.fail()){
		    cout << "Error: too few arguments" << endl;
		    continue;
		}
		cout << "Error: too few arguments" << endl;
                continue;
            }
            string junk; ss >> junk; // get junk chars at the end of input
            if (!ss.fail()) { // there should not be any more args
                cout << "Error: too many arguments" << endl;
                continue;
            }
            if (name == "all") { // check for keyword "all"
                cout << "Deleted: all resistors" << endl;
            } else {
                cout << "Deleted: resistor " + name << endl;
            }
        } else {
            cout << "Error: invalid command" << endl;
        }
    }
}

int main () {
    parser();
    return 0;
}
