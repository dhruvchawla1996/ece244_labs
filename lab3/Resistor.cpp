/*
 * File: Resistor.cpp 
 */

#include "Resistor.h"

using namespace std;

Resistor::Resistor(int rIndex_, string name_, double resistance_, int endpoints_[]) {
    name = name_;
    resistance = resistance_;
    rIndex = rIndex_;
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

void Resistor::print() {
    cout<<setw(20)<<left<<name<<" "<<setw(8)<<right<<setprecision(2)<<fixed
            <<resistance<<" Ohms "<<endpointNodeIDs[0]<<" -> "
            <<endpointNodeIDs[1]<<endl;
}

Resistor::~Resistor(){}
