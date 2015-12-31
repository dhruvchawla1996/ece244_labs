/*
 * File: TreeDB.cpp
 */

#include "TreeDB.h"

using namespace std;

TreeDB::TreeDB() {
	root = NULL; // initialize empty tree
	probesCount = -1;
}

TreeDB::~TreeDB() {
	delete root;
	root = NULL;
}

bool TreeDB::insert( DBentry* newEntry ) {
	if (root == NULL) { // empty tree
		root = new TreeNode(newEntry);
		return true;
	}
	return root->insert(newEntry);
}

DBentry* TreeDB::find( string name ) {
	probesCount = 0;
	if (root == NULL) // empty tree
		return NULL;
	return root->find(name, probesCount);
}

bool TreeDB::remove( string name ) {
	if (root == NULL) return false; // can't delete anything from empty tree
	return root->remove(name, root);
}

void TreeDB::clear() {
	delete root;
	root = NULL;
}

void TreeDB::printProbes() const {
	cout << probesCount << endl;
}

void TreeDB::countActive () const {
	int activeNodes = 0;
	if (root != NULL) {
		root->countActive(activeNodes);
	}
	cout << activeNodes << endl;
}

ostream& operator<<( ostream& out, const TreeDB& rhs ) {
	if (rhs.root == NULL) out << endl; // if tree is empty, print a blank line
	else out << rhs.root; // printing root node
	return out;
}

ostream& operator<<( ostream& out, TreeNode* rhs ) {
	if (rhs == NULL) { // node is null
		out << ""; // print nothing
		return out;
	}
	// print all nodes in order
	out << rhs->getLeft(); 
	out << *(rhs->getEntry()); 
	out << rhs->getRight();
	return out;
}