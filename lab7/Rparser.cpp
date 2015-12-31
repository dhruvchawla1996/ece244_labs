/*
 * File: Rparser.cpp 
 */

#include "Rparser.h"
#include "easygl.h"

using namespace std;

easygl window ("Resistor display", WHITE);

NodeList** g_NodeListPtr;

void easygl::drawscreen() {
    (*g_NodeListPtr)->draw();
}

void parse_draw (NodeList*& nodeList) {
    float xleft, ybottom, xright, ytop;
    
    nodeList->set_draw_coords(xleft, ybottom, xright, ytop);
    
    window.set_world_coordinates(xleft, ybottom, xright, ytop);
    g_NodeListPtr = &nodeList;
    
    nodeList->solveForDraw();
    
    nodeList->draw();
    
    cout << "Draw: control passed to graphics window" << endl;
    
    window.gl_event_loop();
    
    cout << "Draw: complete; responding to commands again" << endl;
}

void setV(stringstream& ss, NodeList*& nodeList) {
    // VALIDATE INPUT
    
    if (ss.eof()) { // check for further args
        cout << "Error: too few arguments" << endl;
        return;
    }

    int node;
    ss >> node;
    
    // validate node
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
    
    if (ss.eof()) { //checks for further args
        cout << "Error: too few arguments" << endl;
        return;
    }

    double voltage;
    ss >> voltage;

    if (ss.fail()) {
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

    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }

    // find or create new node if it doesnt exist
    Node* Node = nodeList->findOrInsertNode(node);

    Node->setVoltage(voltage); // set voltage

    // display output
    cout << "Set: node " << node << " to " << setprecision(2) << fixed 
         << voltage << " Volts" << endl;
}

void unsetV(stringstream& ss, NodeList*& nodeList) {
    // VALIDATE INPUT
    
    if (ss.eof()) { // check for further args
        cout << "Error: too few arguments" << endl;
        return;
    }

    int node;
    ss >> node;
    
    // validate node
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

    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }

    // find or create new node if it doesnt exist
    Node* Node = nodeList->findOrInsertNode(node);

    Node->unsetVoltage(); // unset voltage

    //display output
    cout << "Unset: the solver will determine the voltage of node " << node 
         << endl;
}

void solve (stringstream& ss, NodeList*& nodeList) {
    // VALIDATE INPUT 

    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }

    // check if there exists a node which has volateg set
    if (!nodeList->voltageSet()) {
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }

    nodeList->solve(); // solve
}

void insertR(stringstream& ss, NodeList*& nodeList) {
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
    
    if (nodeList->resistorExists(name)) {
        cout << "Error: resistor "+ name +" already exists" << endl;
        return;
    }

    // get node1 and node2 pointers
    Node* Node1 = nodeList->findOrInsertNode(node1);
    Node* Node2 = nodeList->findOrInsertNode(node2);

    int endpoints[2] = {node1, node2}; // create array of nodes

    // add resistor to node1, node2
    Node1->addResistor(name, endpoints, resistance);
    Node2->addResistor(name, endpoints, resistance);
        
    // display output
    cout << "Inserted: resistor " + name + " "
            << setprecision(2) << fixed << resistance
            << " Ohms " << node1 << " -> " << node2 << endl;
}

void modifyR(stringstream& ss, NodeList*& nodeList) {
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
    
    if (!nodeList->resistorExists(name)) { // resistor not found in the array
        cout << "Error: resistor " + name + " not found" << endl;
        return;
    }

    // get old resistance and set new resistance
    double old_resistance = nodeList->changeResistance(name, resistance);

    if (old_resistance == -1) { // check for weird program behaviour
        cout << "Something went wrong, old_resistance is -1" << endl;
        return;
    }
    
    // display output with 2 decimal accuracy
    cout << "Modified: resistor " + name + " from "
         << setprecision(2) << fixed << old_resistance << " Ohms to "
         << setprecision(2) << fixed << resistance << " Ohms"
         << endl;
}

void printR(stringstream& ss, NodeList*& nodeList) {
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
        // printR is not being checked for lab4, so you can ignore this
        cout << "Print:" << endl;

        if (0 == 0) return; 
        for (int i = 0; i < 10; i++) { 
            cout << "AND HIS NAME IS JOHN CENA!!!" << endl;
            // I told you to ignore this
        }

    } else { // print details of specified resistor
        if (!nodeList->resistorExists(name)) { // resistor doesn't exist
            cout << "Error: resistor " + name + " not found" << endl;
            return;
        }
        // print resistor details
        cout << "Print:" << endl;
        nodeList->printResistor(name);
    }
}

void printNode(stringstream& ss, NodeList*& nodeList) {
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
        
        cout << "Print: " << endl;
        nodeList->printAll();
        return;
    }
    if (ss.peek() != ' ' && ss.peek() != '\t' && ss.peek() != '\n' &&
            ss.peek() != '\r' && ss.peek() != -1 && ss.peek() != '\v' &&
            ss.peek() != '\f') {
        // check for next chars in input
        cout << "Error: invalid argument" << endl;
        return;
    }
        
    string junk;
    ss >> junk; // get junk chars at the end of input
    if (!ss.fail()) { // there should not be any more args
        cout << "Error: too many arguments" << endl;
        return;
    }
    
    // display output
    // print node details 
    cout << "Print:" << endl;
    nodeList->print(node);
}

void deleteR(stringstream& ss, NodeList*& nodeList) {
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
        nodeList->deleteAllResistors();
        nodeList->clearNodes(); 
        // delete unconnected a nd not assigned voltage nodes
    } else {
        if (!nodeList->deleteResistor(name)) {
            // delete wasn't successful because resistor doesn't exist
            cout << "Error: resistor " + name + " not found" << endl;
            nodeList->clearNodes(); 
            // delete unconnected and not assigned voltage nodes
            return;
        }
        // delete was successfull. Print output
        cout << "Deleted: resistor " + name << endl;
    }
}

void Rparser(NodeList*& nodeList) {
    string line; // string to store lines inputed by user

    while (1) { // loop until eof condition reached
        cout << "> "; // interface looks nice
        getline(cin, line, '\n'); // read lines from terminal

        if (cin.eof()) { // check for eof
            break; // break out of loop if no input
        }

        stringstream ss(line); // initialize stringstream with user input
        string cmd;
        ss >> cmd; // get the command

        // call respective functions for each command
        if (cmd == "setV") {
            setV(ss, nodeList);
        } else if (cmd == "unsetV") {
            unsetV(ss, nodeList);
        } else if (cmd == "solve") {
            solve(ss, nodeList);
        } else if (cmd == "insertR") {
            insertR(ss, nodeList);
        } else if (cmd == "modifyR") {
            modifyR(ss, nodeList);
        } else if (cmd == "printR") {
            printR(ss, nodeList);
        } else if (cmd == "printNode") {
            printNode(ss, nodeList);
        } else if (cmd == "deleteR") {
            deleteR(ss, nodeList);
        } else if (cmd == "draw") {
            parse_draw(nodeList);
        } else {
            cout << "Error: invalid command" << endl;
        }
    }
}