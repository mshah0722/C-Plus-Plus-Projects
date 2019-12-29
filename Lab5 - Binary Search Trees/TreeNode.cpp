#include <iostream>
#include <cstdlib>
#include <string>
#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

// A useful constructor
// Set left and right nodes to nullptr;
// Dynamically allocating new entryPtr of DBentry* type
// Setting entryPtr to match _entryPtr
TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr = new DBentry();
    entryPtr->setName(_entryPtr->getName());
    entryPtr->setIPaddress(_entryPtr->getIPaddress());
    entryPtr->setActive(_entryPtr->getActive());
    left = nullptr;
    right = nullptr;
}

// The destructor
// Deleting the dynamically allocated memory for entryPtr of type DBentry*
TreeNode::~TreeNode() {
    delete entryPtr;
}

// Sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft) {
    left = newLeft;
}

// Sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight) {
    right = newRight;
}

// Gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const {
    return left;
}

// Gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const {
    return right;
}

// Returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const {
    return entryPtr;
}