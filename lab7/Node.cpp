/*
 * File: Node.cpp 
 */

#include "Node.h"

using namespace std;

Node::Node(int id_) {
    id = id_;
    isVoltageSet = false;
    voltage = 0;
    next = NULL;
}

Node::~Node(){
    resList.deleteAllRes();
    delete next; // deletes next node in nodeList
}

void Node::setVoltage(double voltage_) {
    isVoltageSet = true;
    voltage = voltage_;
}

void Node::setVoltageForSolver (double voltage_) {
    if (!isVoltageSet) // check if voltage has been set by user
        voltage = voltage_; // if not, we are free to set voltage
}

void Node::unsetVoltage() {
    isVoltageSet = false;
    voltage = 0;
}

bool Node::is_voltage_set () const {
    return isVoltageSet;
}

double Node::getVoltage () const {
    return voltage;
}

void Node::addResistor(string name, int endpoints_[2], double resistance) {
    resList.insertRes(name, endpoints_, resistance);
}

bool Node::findResistor (string name) const {
    return (resList.findRes(name) != NULL);
}

double Node::changeResistance (string name, double new_resistance) {
    return resList.changeResistance(name, new_resistance);
}

bool Node::deleteResistor (string name) {
    Resistor* resistor = resList.findRes(name); // find resistor in resList
    if (resistor != NULL) { // found!
        resList.deleteRes(resistor);
        return true;
    }
    return false; // not found
}

void Node::deleteAllResistors() {
    resList.deleteAllRes();
}

void Node::print() const {
    // no connections but voltage has been set
    if (resList.getCount() == 0 && isVoltageSet)
        cout << "Connections at node " << id << ": " << setprecision(2) << fixed
             <<  voltage << " V" << endl;
    else if (resList.getCount() != 0) { // node is connected to a resistor
        cout << "Connections at node " << id << ": " << resList.getCount()
             << " resistor(s)" << endl;
        resList.print();
    }
}

bool Node::printResistor (string name) const {
    return resList.printR(name);
}

Node* Node::getNext() const {
    return next;
}

void Node::setNext(Node* next_) {
    next = next_;
}

int Node::getID() const {
    return id;
}

void Node::setID(int id_) {
    id = id_;
}

int Node::getNumberOfResistorsConnected() const {
    return resList.getCount();
}