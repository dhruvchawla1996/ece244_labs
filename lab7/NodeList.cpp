/*
 * File: NodeList.cpp
 */

#include "NodeList.h"
#include "easygl.h"
extern easygl window;

using namespace std;

NodeList::NodeList() {
    nodeHead = NULL;
}

NodeList::~NodeList() {
    while (nodeHead != NULL) {
        Node* p = nodeHead;
        nodeHead = p->getNext();
        p->setNext(NULL);
        delete p;
    }
}

Node* NodeList::findOrInsertNode(int id) {
    // find node by id
    Node* p = nodeHead;
    while (p != NULL) {
        if (p->getID() == id) {
            return p;
        }
        p = p->getNext();
    }
    // at this point, the node does not exist, so we need to insert it
    // start at the top again
    p = nodeHead;
    Node* prev = NULL;
    // allocate new node
    Node* newNode = new Node(id);

    while (p != NULL && id > p->getID()) {
        prev = p;
        p = p->getNext();
    }

    newNode->setNext(p);
    if (prev == NULL) {
        nodeHead = newNode;
    } else {
        prev->setNext(newNode);
    }

    return newNode;
}

bool NodeList::resistorExists(string name) const {
    // traverse through the linked list
    Node *p = nodeHead;
    while (p != NULL) {
        if (p->findResistor(name)) // resistor found!
            return true;
        p = p->getNext();
    }
    return false; // search complete and resistor not found
}

double NodeList::changeResistance(string name, double new_resistance) {
    // check if resistor exists
    if (resistorExists(name)) {
        int resistorsModified = 0; // counts resistors modified over the course
        // of while loop, should be 2 at the end of 
        // the while loop
        double old_resistance, temp_resistance;
        Node* p = nodeHead;
        while (p != NULL) {
            temp_resistance = p->changeResistance(name, new_resistance);
            if (temp_resistance != -1) { // -1 = resistor not found in node
                old_resistance = temp_resistance;
                resistorsModified++;
            }
            p = p->getNext();
        }
        if (resistorsModified == 2)
            return old_resistance;
    }
    return -1; // resistor does not exist, hence command is not successful
}

bool NodeList::deleteResistor(string name) {
    // check if resistor exists
    if (resistorExists(name)) {
        int resistorsDeleted = 0; // counts resistors deleted over the course
        // of while loop, should be 2 at the end of 
        // the while loop
        Node* p = nodeHead;
        while (p != NULL) {
            if (p->deleteResistor(name))
                resistorsDeleted++;
            p = p->getNext();
        }
        return (resistorsDeleted == 2);
    }
    return false; // resistor does not exist, hence command is not successful
}

void NodeList::deleteAllResistors() {
    Node* p = nodeHead;
    // traverse through node list
    while (p != NULL) {
        p->deleteAllResistors(); // delete all resistors at a node
        p = p->getNext(); // go to next node
    }
}

void NodeList::printResistor(string name) const {
    if (resistorExists(name)) { // search for resistor
        bool printed = false; // to prevent printing twice

        Node *p = nodeHead;
        // traverse through the node list
        while (p != NULL && !printed) {
            if (p->printResistor(name)) // print resistor if connected to node
                printed = true; // resistor has been printed
            p = p->getNext();
        }
    }
}

void NodeList::print(int id) const {
    Node* p = nodeHead;
    // traverse through node list
    while (p != NULL) {
        if (p->getID() == id) { // match ID
            p->print(); // print details of node p
            return; // since ID is unique, no need to search rest of the list
        }
        p = p->getNext();
    }
}

void NodeList::printAll() const {
    Node* p = nodeHead;
    // traverse through node list
    while (p != NULL) {
        p->print(); // print details of node p
        p = p->getNext();
    }
}

bool NodeList::voltageSet() const {
    Node* p = nodeHead;
    while (p != NULL) {
        if (p->is_voltage_set()) // has voltage been set on p?
            return true;
        p = p->getNext();
    }
    return false; // voltage has not been set on any node
}

void NodeList::solve() {
    // set voltage to 0 for nodes which don't have their voltage set by user
    Node* p = nodeHead;
    while (p != NULL) {
        p->setVoltageForSolver(0);
        p = p->getNext();
    }

    double MIN_ITERATION_CHANGE = 0.0001;

    double max_node_voltage_change = 42; // It's the answer to the ultimate  
    // question of the universe

    while (max_node_voltage_change > MIN_ITERATION_CHANGE) {
        p = nodeHead;
        max_node_voltage_change = 0;
        double new_voltage; // delare new voltage of p after one iteration
        while (p != NULL) {
            if (!p->is_voltage_set()) {
                // as equation 3 consists of two terms multiplied together, 
                // I will calculate the two terms separately for all nodes 
                // connected to p and multiply them together
                double first_term = 0, second_term = 0;
                ResistorList& res = p->resList;
                // traverse through p's resList
                Resistor* r = res.getResHead();
                while (r != NULL) {
                    double resistance = r->getResistance();

                    first_term += (1 / resistance);

                    // get voltage of other node
                    int other_node_id = r->getOtherNodeID(p->getID());
                    Node* other_node = findOrInsertNode(other_node_id);
                    double other_node_voltage = other_node->getVoltage();

                    second_term += (other_node_voltage / resistance);

                    r = r->getNext();
                }
                // calculate new voltage of p
                new_voltage = (1 / first_term) * second_term;

                // check if change is greater than MIN_ITERATION_CHANGE
                if (fabs(p->getVoltage() - new_voltage) > \
					max_node_voltage_change) {
                    max_node_voltage_change = \
						fabs(p->getVoltage() - new_voltage);
                }
                // store new voltage
                p->setVoltageForSolver(new_voltage);

            }
            p = p->getNext();
        }
    }

    // print output
    cout << "Solve:" << endl;
    p = nodeHead;
    while (p != NULL) {
        cout << "  Node " << p->getID() << ": " << setprecision(2) << fixed
                << p->getVoltage() << " V" << endl;
        p = p->getNext();
    }
}

void NodeList::clearNodes () {
    bool clean = false;
    
    while (!clean) {
        clean = true;
        if (nodeHead != NULL) {
            Node* p = nodeHead;
            Node* prev = NULL;
            while (p != NULL) {
                // check if node has no connections or no assigned voltage
                if (!p->getNumberOfResistorsConnected() && !p->is_voltage_set()) {
                    if (prev == NULL) 
                        nodeHead = p->getNext();
                    else
                        prev->setNext(p->getNext());
                    p->setNext(NULL);
                    delete p;
                    clean = false;
                    break;
                }
                prev = p;
                p = p->getNext();
            }
        }
    }
}

void NodeList::solveForDraw() {
    // set voltage to 0 for nodes which don't have their voltage set by user
    Node* p = nodeHead;
    while (p != NULL) {
        p->setVoltageForSolver(0);
        p = p->getNext();
    }

    double MIN_ITERATION_CHANGE = 0.0001;

    double max_node_voltage_change = 42; // It's the answer to the ultimate  
    // question of the universe

    while (max_node_voltage_change > MIN_ITERATION_CHANGE) {
        p = nodeHead;
        max_node_voltage_change = 0;
        double new_voltage; // delare new voltage of p after one iteration
        while (p != NULL) {
            if (!p->is_voltage_set()) {
                // as equation 3 consists of two terms multiplied together, 
                // I will calculate the two terms separately for all nodes 
                // connected to p and multiply them together
                double first_term = 0, second_term = 0;
                ResistorList& res = p->resList;
                // traverse through p's resList
                Resistor* r = res.getResHead();
                while (r != NULL) {
                    double resistance = r->getResistance();

                    first_term += (1 / resistance);

                    // get voltage of other node
                    int other_node_id = r->getOtherNodeID(p->getID());
                    Node* other_node = findOrInsertNode(other_node_id);
                    double other_node_voltage = other_node->getVoltage();

                    second_term += (other_node_voltage / resistance);

                    r = r->getNext();
                }
                // calculate new voltage of p
                new_voltage = (1 / first_term) * second_term;

                // check if change is greater than MIN_ITERATION_CHANGE
                if (fabs(p->getVoltage() - new_voltage) > \
					max_node_voltage_change) {
                    max_node_voltage_change = \
						fabs(p->getVoltage() - new_voltage);
                }
                // store new voltage
                p->setVoltageForSolver(new_voltage);

            }
            p = p->getNext();
        }
    }


}

void NodeList::set_draw_coords(float& xleft, float& ybottom, float& xright, float& ytop) {
    xleft = 0;
    ybottom = 0;
    
    int WIDTH_BUFFER = 20;
    int HEIGHT_BUFFER = 200;
        
    int WIDTH_FOR_NODE = 100;
    int HEIGHT_FOR_RESISTOR = 100;
    
    int count_nodes = 0, count_resistors = 0;
    
    Node* p = nodeHead;
    while (p != NULL) {
        count_nodes++;
        count_resistors += p->getNumberOfResistorsConnected();
        p = p->getNext();
    }
    count_resistors /= 2;
    
    xright = WIDTH_FOR_NODE * count_nodes + WIDTH_BUFFER;
    ytop = HEIGHT_FOR_RESISTOR * count_resistors + HEIGHT_BUFFER;
}

void NodeList::draw() {
    window.gl_clearscreen();
    
    int count_resistors = 0;
    Node* p = nodeHead;
    while (p != NULL) {
        
        count_resistors += p->getNumberOfResistorsConnected();
        p = p->getNext();
    }
    count_resistors /= 2;
    
    int WIDTH_FOR_NODE = 100;
    int HEIGHT_BUFFER = 200;
    int HEIGHT_FOR_RESISTOR = 100;
    int HEIGHT_FOR_NODE = HEIGHT_FOR_RESISTOR * count_resistors + HEIGHT_BUFFER;;
    
    
    int LEFT_BUFFER = 10;
    int BOTTOM_BUFFER = 50;
    
    int x_coord = LEFT_BUFFER;
    
    stringstream ss;
    string text;
    
    p = nodeHead;
    while (p != NULL) {
        window.gl_setcolor(LIGHTGREY);
        window.gl_fillrect(x_coord, BOTTOM_BUFFER, x_coord + 10, HEIGHT_FOR_NODE);
        
        window.gl_setcolor(BLACK);
        ss << "Node ";
        ss << p->getID() <<endl;
        getline(ss,text);
        window.gl_drawtext(x_coord+5, BOTTOM_BUFFER/2 + 5, text);
        ss.flush();
        
        ss << p->getID();
        ss << " V"<< endl;
        getline(ss,text);
        window.gl_drawtext(x_coord+5, BOTTOM_BUFFER/2 - 5, text);
        ss.flush();
        
        x_coord =x_coord+ WIDTH_FOR_NODE;
        
        p = p->getNext();
    }
    
    x_coord = 10;
    int y_coord = BOTTOM_BUFFER+HEIGHT_FOR_RESISTOR;
    p = nodeHead;
    
    while (p != NULL) {
        ResistorList& res = p->resList;
        Resistor* r = res.getResHead();
        while (r != NULL) {
            if (r->getEndpointOne() > p->getID()) {
                window.gl_setcolor(BLACK);
                window.gl_drawline(x_coord+2.5, y_coord, x_coord+(r->getEndpointOne() - p->getID())*WIDTH_FOR_NODE+2.5, y_coord);
                window.gl_setcolor(RED);
                window.gl_fillrect(x_coord+2.5+(r->getEndpointOne() - p->getID())*WIDTH_FOR_NODE/2-10, y_coord-10, x_coord+2.5+(r->getEndpointOne() - p->getID())*WIDTH_FOR_NODE/2+10, y_coord+10);
                
                ss << r->getName() << " (" << r->getResistance() << " Ohm)" << endl;
                getline(ss, text);
                
                window.gl_drawtext(x_coord+2.5+(r->getEndpointOne() - p->getID())*WIDTH_FOR_NODE/2, y_coord-20, text);
                
                ss.flush();
                y_coord += HEIGHT_FOR_RESISTOR;
            } else if (r->getEndpointTwo() > p->getID()) {
                window.gl_setcolor(BLACK);
                window.gl_drawline(x_coord+2.5, y_coord, x_coord+(  r->getEndpointTwo() - p->getID()   )*WIDTH_FOR_NODE+2.5, y_coord);
                window.gl_setcolor(RED);
                window.gl_fillrect(x_coord+2.5+(r->getEndpointTwo() - p->getID() )*WIDTH_FOR_NODE/2-10, y_coord-10, x_coord+2.5+(r->getEndpointTwo() - p->getID() )*WIDTH_FOR_NODE/2+10, y_coord+10);
                
                ss << r->getName() << " (" << r->getResistance() << " Ohm)" << endl;
                getline(ss, text);
                
                window.gl_drawtext(x_coord+2.5+(r->getEndpointTwo() - p->getID() )*WIDTH_FOR_NODE/2, y_coord-20, text);
                
                ss.flush();
                y_coord += HEIGHT_FOR_RESISTOR;
            }
            
            r = r->getNext();
        }
        
        x_coord += WIDTH_FOR_NODE;
        p = p->getNext();
        
    }
}