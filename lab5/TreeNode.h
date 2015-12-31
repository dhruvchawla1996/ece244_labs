/*
 * File: TreeNode.h
 */

#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include "DBentry.h"

using namespace std;

class TreeNode {
	friend class TreeDB;
private:
	DBentry* entryPtr ; 
	TreeNode* left ; 
	TreeNode* right ;
	// insert new node into binary tree
	bool insert( DBentry* newEntry );
	// find node by name and return data base entry at found node
	DBentry* find ( string name, int& probesCount ) const;
	// removes entry by name, return true if successful
	bool remove ( string name, TreeNode*& parentPointer );
	// return number of active nodes
	void countActive( int& activeNodes ) const;
	// return node with max name in entry
	TreeNode* getMax() ;
public:
	// A useful constructor 
	TreeNode( DBentry* _entryPtr ) ;
	// the destructor 
	~TreeNode() ;
	// sets the left child of the TreeNode. 
	void setLeft( TreeNode* newLeft ) ;
	// sets the right child of the TreeNode 
	void setRight( TreeNode* newRight ) ;
	// gets the left child of the TreeNode. 
	TreeNode* getLeft() const ;
	// gets the right child of the TreeNode 
	TreeNode* getRight() const ;
	// returns a pointer to the to the DBentry the TreeNode contains.
	DBentry* getEntry() const ; 
};

#endif /* TREENODE_H */