/* 
 * File:   Main.cpp
 */

#include <cstdlib>
#include "Rparser.h"
#include "ResistorList.h"
#include "NodeList.h"

using namespace std;

int main() {
	NodeList* nodeList = new NodeList;
    Rparser(nodeList); // call parser to parse user inputs
    delete nodeList;
    nodeList = NULL;
    return 0;
}

