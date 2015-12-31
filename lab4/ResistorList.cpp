/*
 * File: ResistorList.cpp
 */

#include "ResistorList.h"

using namespace std;

ResistorList::ResistorList() {
    resHead = NULL;
    count = 0;
}

void ResistorList::insertRes(string name, int endpoints[], double resistance) {
    // dynamicaly allocate new resistor
    Resistor* newRes = new Resistor(name, resistance, endpoints, NULL);
    if (resHead == NULL) {
        resHead = newRes;
    } else {
        Resistor* p = resHead;
        // get to the end of the linked list
        while (p->getNext() != NULL) {
            p = p->getNext();
        }
        p->setNext(newRes); // make the last resistor point to new resistor
    }
    count++; // increment number of resistors
}

Resistor* ResistorList::findRes(string name) const {
    if (resHead == NULL) // check if list is empty
        return NULL;
    Resistor *p = resHead;
    while (p != NULL) {
        if (p->getName() == name) // found!
            return p;
        p = p->getNext();
    }
    return NULL; // not found
}

void ResistorList::deleteRes(Resistor* resistor) {
    if (resHead != NULL) {
        Resistor *p = resHead;
        Resistor *prev = NULL; // previous resistor, initialised to NULL
        while (p != NULL) {
            if (p->getName() == resistor->getName()) { 
                // since name is unique, match the names
                if (prev == NULL) { // delete at beginning
                    resHead = p->getNext();
                } else {
                    prev->setNext(p->getNext());
                }
                p->setNext(NULL);
                delete p;
                count--;
                return; // search complete
            }
            prev = p;
            p = p->getNext();
        }
    }
}

void ResistorList::deleteAllRes () {
    Resistor* p = resHead;
    Resistor* prev = NULL; // previous resistor, initialised to NULL
    while (p != NULL) {
        prev = p;
        p = p->getNext();
        prev->setNext(NULL);
        delete prev;
    }
    resHead = NULL;
    count = 0;
}

double ResistorList::changeResistance (string name, double new_resistance){
    Resistor* p = findRes(name);
    if (p == NULL) // resistor not found
        return -1;

    // resistor found, get old value
    double old_resistance = p->getResistance();
    // change resistance
    p->setResistance(new_resistance);

    return old_resistance;
}

int ResistorList::getCount () const {
    return count;
}

Resistor* ResistorList::getResHead() const {
    return resHead;
}

bool ResistorList::printR (string name) const {
    Resistor* resistor = findRes(name); // find resistor
    if (resistor != NULL) { // found!
        if (resistor->getName() == name) { // double check
            resistor->print(); 
            return true; // resistor printed successfully
        }
    }
    return false; // not found
}

void ResistorList::print () const {
    Resistor* p = resHead;
    while (p != NULL) {
        cout << "  ";
        p->print();
        p = p->getNext();
    }
}

ResistorList::~ResistorList() {
    while (resHead != NULL) {
        Resistor* p = resHead;
        resHead = p->getNext();
        p->setNext(NULL);
        delete p;
    }
    count = 0;
}