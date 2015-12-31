/*
 * File: Resistor.cpp 
 */

#include "Resistor.h"

using namespace std;

Resistor::Resistor(string name_, double resistance_, int endpoints_[], Resistor* next_) {
    // assign name
    name = name_;
    // assign resistance
    resistance = resistance_;
    // assign next resistor pointer
    next = next_;
    // assign endpoints
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
}

string Resistor::getName() const {
    return name;
}

double Resistor::getResistance() const {
    return resistance;
}

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

Resistor* Resistor::getNext() const {
    return next;
}

void Resistor::setNext(Resistor* next_) {
    next = next_;
}

int Resistor::getOtherNodeID (int this_node_id) {
    if (endpointNodeIDs[0] == this_node_id)
        return endpointNodeIDs[1];
    return endpointNodeIDs[0];
}

int Resistor::getEndpointOne() {
    return endpointNodeIDs[0];
}

int Resistor::getEndpointTwo(){
    return  endpointNodeIDs[1];
}

void Resistor::print() {
    cout<<setw(20)<<left<<name<<" "<<setw(8)<<right<<setprecision(2)<<fixed
            <<resistance<<" Ohms "<<endpointNodeIDs[0]<<" -> "
            <<endpointNodeIDs[1]<<endl;
}

Resistor::~Resistor(){
    delete next;
}
