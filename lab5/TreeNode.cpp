/*
 * File: TreeNode.cpp
 */

#include "TreeNode.h"

using namespace std;

TreeNode::TreeNode( DBentry* _entryPtr ) {
	// initialize a new node with no chldren
	entryPtr = _entryPtr;
	left = NULL;
	right = NULL;
}

TreeNode::~TreeNode() {
	delete entryPtr;
	delete left;
	delete right;
	// set all deleted pointers to NULL
    entryPtr = NULL;
    left = NULL;
    right = NULL;
}

bool TreeNode::insert( DBentry* newEntry ) {
	if (entryPtr->getName() == newEntry->getName())
		return false; // entry exists
	if (entryPtr->getName() > newEntry->getName()) {
		// entry exists in left node
		if (left == NULL) {
			// no left child? insert new node at left 
			left = new TreeNode(newEntry);
			return true;
		}
		// insert in left subtree
		return left->insert(newEntry);
	}
	if (entryPtr->getName() < newEntry->getName()) {
		// entry exists in right node
		if (right == NULL) {
			// no right child? insert new node at right  
			right = new TreeNode(newEntry);
			return true;
		}
		// insert in right subtree
		return right->insert(newEntry);
	}
}

DBentry* TreeNode::find ( string name, int& probesCount ) const {
	probesCount++; // increment probe count
	// we have found waldo
	if (name == entryPtr->getName()) return entryPtr;
	// is it in left sutree?
	if (name < entryPtr->getName()) {
		if (left == NULL) return NULL; // reached the end and entry not found
		return left->find(name, probesCount); // search left subtree
	}
	// is it in right subtree?
	if (name > entryPtr->getName()) {
		if (right == NULL) return NULL; // reached the end and entry not found
		return right->find(name, probesCount); // search right subtree
	}
}

bool TreeNode::remove ( string name, TreeNode*& parentPointer ) {
	if (name < entryPtr->getName()) {
		if (left == NULL) return false;
		return left->remove(name, left); // search left subtree
	}
	if (name > entryPtr->getName()) {
		if (right == NULL) return false;
		return right->remove(name, right); // search right subtree
	}
	// name == entyPtr->getName()
	// time to EXTERMINATE
	if (left == NULL && right == NULL) { // node has no children
		parentPointer = NULL;
		delete this;
		return true;
	}
	if (left == NULL && right != NULL) { // node has a right child
		parentPointer = right; // assign right subtree to parentPointer
		setRight(NULL);
		delete this;
		return true;
	}
	if (left != NULL && right == NULL) { // node has a left child
		parentPointer = left; // assign left subtree to parentPointer
		setLeft(NULL);
		delete this;
		return true;
	}
	// left != NULL && right != NULL
	// EXTERMINATE, but with care

	// find max entry node in left subtree
	TreeNode* maxNode = left->getMax();

	// store that entry in the node that we are about to delete
	entryPtr->setName(maxNode->getEntry()->getName());
	entryPtr->setIPaddress(maxNode->getEntry()->getIPaddress());
	entryPtr->setActive(maxNode->getEntry()->getActive());

	// remove the max node in left subtree
	left->remove(maxNode->getEntry()->getName(),left);

	return true;
}

TreeNode* TreeNode::getMax() {
	if (right == NULL) return this; // no right child, we have reached max node
	return right->getMax(); // get the max node in right subtree
}

void TreeNode::countActive( int& activeNodes ) const {
	if (entryPtr->getActive() == true) // node is active
		activeNodes++; // increment active nodes counter
	
	// search for active nodes in left subtree
	if (left != NULL) left->countActive(activeNodes); 
	// search for active nodes in right subtree
	if (right != NULL) right->countActive(activeNodes);
}

void TreeNode::setLeft( TreeNode* newLeft ) {
	left = newLeft;
}

void TreeNode::setRight( TreeNode* newRight ) {
	right = newRight;
}

TreeNode* TreeNode::getLeft() const {
	return left;
}

TreeNode* TreeNode::getRight() const {
	return right;
}

DBentry* TreeNode::getEntry() const {
	return entryPtr;
}
