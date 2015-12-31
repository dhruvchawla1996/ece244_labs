/*
 * File: Rparser.cpp 
 */

#include "Rparser.h"

using namespace std;

int count_maxVal = 0; // counts number of times maxVal has been called in 
                      // runtime

bool resistorNameExists(string name) {
    // return false if there are no resistors in the network
    if (resCount == 0) {
        return false;
    }
    // search for name in resistorArray
    for (int i = 0; i < resCount; i++) {
        if (name == resistorArray[i]->getName()) {
            return true;
        }
    }
    return false;
}

int getResistorIndexFromName(string name) {
    // return -1 if there are no resistors in the network
    if (resCount == 0) {
        return -1;
    }
    // search for name in resistorArray and return index
    for (int i = 0; i < resCount; i++) {
        if (name == resistorArray[i]->getName()) {
            return i;
        }
    }
    return -1;
}

void deleteAll() {
    delete []nodeArray;
    nodeArray = NULL; // set nodeArray to NULL
    // delete each dynamically allocated resistor 
    for (int i = 0; i < resCount; i++) {
        delete resistorArray[i];
        resistorArray[i] = NULL; // set element to NULL
    }
    delete []resistorArray;
    resistorArray = NULL; // set to NULL
    resCount = 0; // set number of resistors in network to 0
}

void maxVal(stringstream& ss) {
    // delete network elements if already allocated
    if (count_maxVal != 0) {
        deleteAll();
    }

    ss >> maxNodeNumber; // get max node number in network 
    ss >> maxResistors; // get max resistors in network

    //  validate input
    if (maxNodeNumber <= 0 || maxResistors <= 0) { 
        cout << "Error: maxVal arguments must be greater than 0"
                << endl;
        return;
    }
    
    // allocate memory to resistorArray and nodeArray
    resistorArray = new Resistor*[maxResistors];
    nodeArray = new Node[maxNodeNumber + 1];
    
    resCount = 0; // set resistor count to 0

    count_maxVal++; // increment number of times maxVal has been called

    // display output
    cout << "New network: max node number is " << maxNodeNumber
            << "; max resistors is " << maxResistors << endl;
}

void insertR(stringstream& ss) {
    // VALIDATE INPUT
    
    if (ss.eof()) { // check for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    string name;
    ss >> name; // get name
    
    //validate name
    if (ss.fail()) {
        cout << "Error: too few arguments" << endl;
        return;
    }
    if (name == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\""
                << endl;
        return;
    }
    if (ss.eof()) { //checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    double resistance;
    ss >> resistance; // get resistance
    
    // validate resistance
    if (ss.fail()) { // check if resistance is indeed a double
        ss.clear();
        string invalid_arg;
        ss >> invalid_arg;
        if (ss.fail()) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' &&
            ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' &&
            ss.peek() != '\f') {
        // check for next chars in input
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (resistance < 0) { // check for negative resistance
        cout << "Error: negative resistance" << endl;
        return;
    }
    if (ss.eof()) { //checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    // get node1
    int node1;
    ss >> node1;
    
    // validate node1
    if (ss.fail()) { // check if nodeid is an int
        ss.clear();
        string invalid_arg;
        ss >> invalid_arg;
        if (ss.fail()) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' &&
            ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' &&
            ss.peek() != '\f') {
        // check for next chars in input
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (node1 < 0 || node1 > maxNodeNumber) {
        // check if nodeid is in range
        cout << "Error: node " << node1
                << " is out of permitted range 0-"
                << maxNodeNumber << endl;
        return;
    }
    if (ss.eof()) { //checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    // get node2
    int node2;
    ss >> node2;
    
    // validate node2
    if (ss.fail()) { // check if nodeid is an int
        ss.clear();
        string invalid_arg;
        ss >> invalid_arg;
        if (ss.fail()) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' &&
            ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' &&
            ss.peek() != '\f') {
        // check for next chars in input
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (node2 < 0 || node2 > maxNodeNumber) {
        // check if nodeid is in range
        cout << "Error: node " << node2
                << " is out of permitted range 0-"
                << maxNodeNumber << endl;
        return;
    }
    if (node1 == node2) { // check if resistor is connected to both
        // terminals
        cout << "Error: both terminals of resistor connect to node "
                << node1 << endl;
        return;
    }
    
    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }
    
    if (resCount > maxResistors - 1) {
        cout << "Error: resistor array is full" << endl;
        return;
    }
    if (nodeArray[node1].isNodeFull() || nodeArray[node2].isNodeFull()) {
        cout << "Error: node is full" << endl;
        return;
    }
    if (resistorNameExists(name)) {
        cout << "Error: resistor name already exists" << endl;
        return;
    }
    
    // add resistor to nodes
    nodeArray[node1].addResistor(resCount);
    nodeArray[node2].addResistor(resCount);
    
    int end_points[2] = {node1, node2}; // create endpoints array
    resistorArray[resCount] = new Resistor(resCount, name, resistance, \
                                           end_points); // instantiate Resistor
    resCount++; // increment number of resistors in network
    
    // display output
    cout << "Inserted: resistor " + name + " "
            << setprecision(2) << fixed << resistance
            << " Ohms " << node1 << " -> " << node2 << endl;
}

void modifyR(stringstream& ss) {
    // VALIDATE INPUT
    
    if (ss.eof()) { // checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    string name;
    ss >> name; // get name
    
    // validate name
    if (ss.fail()) {
        cout << "Error: too few arguments" << endl;
        return;
    }
    if (name == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\""
                << endl;
        return;
    }
    if (ss.eof()) { //checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    double resistance;
    ss >> resistance; // get resistance
    // validate resistance
    if (ss.fail()) { // check of resistance is indeed a double
        ss.clear();
        string invalid_arg;
        ss >> invalid_arg;
        if (ss.fail()) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' &&
            ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' &&
            ss.peek() != '\f') {
        // check for next chars in input
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (resistance < 0) { // check for negative resistance
        cout << "Error: negative resistance" << endl;
        return;
    }
    
    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }
    
    // get index of resistor in the array
    int resistor_index = getResistorIndexFromName(name);
    if (resistor_index == -1) { // resistor not found in the array
        cout << "Error: resistor " + name + " not found" << endl;
        return;
    }
    // get old resistance
    double old_resistance = resistorArray[resistor_index]->getResistance();
    // set new resistance
    resistorArray[resistor_index]->setResistance(resistance);
    
    // display output with 2 decimal accuracy
    cout << "Modified: resistor " + name + " from "
            << setprecision(2) << fixed << old_resistance << " Ohms to "
            << setprecision(2) << fixed << resistance << " Ohms"
            << endl;
}

void printR(stringstream& ss) {
    // VALIDATE INPUT
    if (ss.eof()) { // checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    string name;
    ss >> name; // get name
    if (ss.fail()) {
        ss.clear();
        string invalid_arg;
        ss >> invalid_arg;
        if (ss.fail()) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }
    
    if (name == "all") { // check for keyword "all"
        cout << "Print:" << endl;
        if (resCount == 0) return; // no resistors in network
        for (int i = 0; i < resCount; i++) { // loop through resistorArray
            resistorArray[i]->print(); // print resistor details
        }
    } else { // print details of specified resistor
        // get index of resistor in resistorArray
        int resistor_index = getResistorIndexFromName(name);
        if (resistor_index == -1) { // resistor doesn't exist
            cout << "Error: resistor " + name + " not found" << endl;
            return;
        }
        // print resistor details
        cout << "Print:" << endl;
        resistorArray[resistor_index]->print();
    }
}

void printNode(stringstream& ss) {
    // VALIDATE INPUT
    if (ss.eof()) { // checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    int node;
    ss >> node; // get node id
    // validate node
    if (ss.fail()) {
        // analyze input again to see if it was 'all'
        ss.clear(); // clear error flag
        string node_string;
        ss >> node_string; // get node again but as a string
        if (ss.fail()) { // was a whitespace all along
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (node_string != "all") {
            cout << "Error: invalid argument" << endl;
            return;
        }
        
        string junk;
        ss >> junk; // get junk chars at the end of input
        if (!ss.fail()) { // there should not be any more args
            cout << "Error: too many arguments" << endl;
            return;
        }
        
        // print all node details
        cout << "Print:" << endl;
        for (int i = 0; i <= maxNodeNumber; i++) { // loop through nodeArray
            nodeArray[i].print(i); // print details of each node
        }
        return;
    }
    if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' &&
            ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' &&
            ss.peek() != '\f') {
        // check for next chars in input
        cout << "Error: invalid argument" << endl;
        return;
    }
    if (node < 0 || node > maxNodeNumber) {
        // check if nodeid is in range
        cout << "Error: node " << node
                << " is out of permitted range 0-"
                << maxNodeNumber << endl;
        return;
    }
    
    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }
    
    //display output
    // print node details 
    cout << "Print:" << endl;
    nodeArray[node].print(node);
}

void deleteR(stringstream& ss) {
    // VALIDATE INPUT
    if (ss.eof()) { // checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    string name;
    ss >> name; // get name
    if (ss.fail()) {
        ss.clear();
        string invalid_arg;
        ss >> invalid_arg;
        if (ss.fail()) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        cout << "Error: too few arguments" << endl;
        return;
    }
    
    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }
    
    if (name == "all") { // check for keyword "all"
        // give the user an empty network
        cout << "Deleted: all resistors" << endl; // print output
        deleteAll(); // delete the whole network
        // initialize the network so that user gets an empty network
        resistorArray = new Resistor*[maxResistors];
        nodeArray = new Node[maxNodeNumber + 1];
        resCount = 0;
    } else {
        cout << "Deleted: resistor " + name << endl;
    }
}

void Rparser() {
    string line; // string to store lines inputed by user

    while (1) { // loop until eof condition reached
        cout << "> "; // interface looks nice
        getline(cin, line, '\n'); // read lines from terminal

        if (cin.eof()) { // check for eof
            deleteAll(); // delete the whole network
            break; // break out of loop if no input
        }

        stringstream ss(line); // initialize stringstream with user input
        string cmd;
        ss >> cmd; // get the command

        // call respective functions for each command
        if (cmd == "maxVal") {
            maxVal(ss);
        } else if (cmd == "insertR") {
            insertR(ss);
        } else if (cmd == "modifyR") {
            modifyR(ss);
        } else if (cmd == "printR") {
            printR(ss);
        } else if (cmd == "printNode") {
            printNode(ss);
        } else if (cmd == "deleteR") {
            deleteR(ss);
        } else {
            cout << "Error: invalid command" << endl;
        }
    }
}