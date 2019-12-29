#include <iostream>
#include <cstdlib>
#include <string>
#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

//Default constructor, creates an empty database, sets probesCount to 0
TreeDB::TreeDB() {
    root = nullptr;
    probesCount = 0;
}

//Destructor, deletes all the entries in the database.
TreeDB::~TreeDB() {
    clear();
}

// Inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// In the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry) {
    if(newEntry == NULL)
        return false;
    if(isTreeEmpty()) {
        root = new TreeNode(newEntry);
        cout << "Success" << endl;
        return true;
    }
    else if(findKey(root, newEntry->getName()) != nullptr) {
        cout << "Error: entry already exists" << endl;
        return false;
    }
    else {
        insertEntry(newEntry, root);
        cout << "Success" << endl;
        return false;
    }
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the nullptr pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name) {
    probesCount = 0;
    if(isTreeEmpty()) {
        cout << "Error: entry does not exist" << endl;
        return nullptr;
    }
    
    TreeNode* current = root;
    DBentry* currentEntry = current->getEntry();
    
    while(current != nullptr) {
        currentEntry = current->getEntry();
        if(currentEntry->getName() == name) {
            probesCount++;
            return currentEntry;
        }
        else if(currentEntry->getName() > name){
            probesCount++;
            current = current->getLeft();
        }
        else {
            probesCount++;
            current = current->getRight();
        }
    }
    cout << "Error: entry does not exist" << endl;
    return nullptr;
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name) {
    if(root == NULL)
        return false;
    return deleteNode(root, NULL, name);
}
	
// deletes all the entries in the database.
void TreeDB::clear() {
    deleteAllNodes(root);
    root = NULL;
}
    
// prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    if(probesCount == 0)
        cout << "Error: entry does not exist" << endl;
    else
        cout << probesCount << endl;
    return;
}
   
// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const {
    int activeNumber = 0;
    TreeNode* rootNode = root;
    findAllActiveNodes(rootNode, activeNumber);
    cout << activeNumber << endl;
    return;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs) {
    if(rhs.root != NULL)
        out << rhs.root;
}

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs) {
    if(rhs != NULL) {
        out << rhs->getLeft();
        out << *(rhs->getEntry());
        out << rhs->getRight();
        return out;
    }
} 

//Checks if the tree is empty, returns true if it is, false otherwise
bool TreeDB::isTreeEmpty() {
    if(root == nullptr) 
        return true;
    return false;
}

//Finds the specified key in the tree, returns the node that holds they key
TreeNode* TreeDB::findKey(TreeNode* node, string nameOfKey) {
    if(node == nullptr)
        return nullptr;
    if(node->getEntry()->getName() == nameOfKey)
        return node;
    else if(node->getEntry()->getName() > nameOfKey)
        return findKey(node->getLeft(), nameOfKey);
    else
        return findKey(node->getRight(), nameOfKey);
}

//Inserts a specified entry into a tree
void TreeDB::insertEntry(DBentry* newEntry, TreeNode* node) {
    if(newEntry->getName() < node->getEntry()->getName()) {
        if(node->getLeft() == NULL) {
            TreeNode* newNode = new TreeNode(newEntry);
            node->setLeft(newNode);
        }
        else
            insertEntry(newEntry, node->getLeft());
    }
    if(newEntry->getName() > node->getEntry()->getName()) {
        if(node->getRight() == NULL) {
            TreeNode* newNode = new TreeNode(newEntry);
            node->setRight(newNode);
        }
        else
            insertEntry(newEntry, node->getRight());
    }
}
   
//Function deletes the node with a certain name, and returns true
//Function returns false if it is unable to find it
bool TreeDB::deleteNode(TreeNode* node,TreeNode* parent, string nameOfKey) {
    if(node == NULL)
        return false;
    //If the node's key matches the key that is being looked for
    if(node->getEntry()->getName() == nameOfKey) {
        //If the node that needs to be deleted has no children
        if(node->getRight() == NULL && node->getLeft() == NULL) { 
            //If the root node needs to be deleted
            if(parent == NULL) {  
                delete node;
                //root = NULL;
                return true;
            }
            else {
                //If parent right node is the node to be deleted
                //Set the parent's right to NULL
                if(parent->getRight() == node)
                    parent->setRight(NULL);
                //If parent left node is the node to be deleted
                //Set the parent's left to NULL
                if(parent->getLeft() == node)
                    parent->setLeft(NULL);
                //Delete node and return true
                delete node;
                return true;
            }
        }
        //If the node that needs to be deleted doesn't have a left subtree
        if(node->getLeft() == NULL) {
            //If the node that needs to be deleted is the root node
            if(parent == NULL)
                root = node->getRight();
            else {
                //If parent's right is the node to be removed
                //Set parent's right to node's right
                if(parent->getRight() == node)
                    parent->setRight(node->getRight());
                //If parent's left is the node to be removed
                //Set parent's left to node's right
                if(parent->getLeft() == node)
                    parent->setLeft(node->getRight());
            }
            delete node;
            return true;
        }
        //Find the largest node on the left subtree and set it to largestLeft
        TreeNode* largestLeft = findLargestFromLeftSubtree(node->getLeft(), node);
        //Replace node with largest left
        largestLeft->setLeft(node->getLeft());
        largestLeft->setRight(node->getRight());
        //If parent is the root node, set root to largest left
        if(parent == NULL)
            root = largestLeft;
        else {
            //If parent right node is the node to be deleted
            //Set the parent's right to largestLeft
            if(parent->getRight() == node)
                parent->setRight(largestLeft);
            //If parent left node is the node to be deleted
            //Set the parent's left to largestLeft
            if(parent->getLeft() == node)
                parent->setLeft(largestLeft);
        }
        delete node;
        return true;
    }
    //If the key value is less than current node's value, look left
    if(node->getEntry()->getName() > nameOfKey)
        return deleteNode(node->getLeft(), node, nameOfKey);
    //If the key value is greater than current node's value, look right
    if(node->getEntry()->getName() < nameOfKey)
        return deleteNode(node->getRight(), node, nameOfKey);
}

   
//Function used to find the largest node from the left subtree
TreeNode* TreeDB::findLargestFromLeftSubtree(TreeNode* node, TreeNode* parent) {
    if(node->getRight() == NULL) {
        if(parent->getRight() == node)
            parent->setRight(node->getLeft());
        if(parent->getLeft() == node)
            parent->setLeft(node->getLeft());
        return node;
    }
    return findLargestFromLeftSubtree(node->getRight(), node);
}
   
//Function used to count all the active nodes within the tree
void TreeDB::findAllActiveNodes(TreeNode* node, int& activeNumber) const{
    if (node == nullptr)
        return;
    else if (node->getEntry()->getActive()) {
        activeNumber++;
    }
    findAllActiveNodes(node->getLeft(), activeNumber);
    findAllActiveNodes(node->getRight(), activeNumber);
}
   
//Deletes all the nodes within the tree
void TreeDB::deleteAllNodes(TreeNode* node) {
    if(node == nullptr)
        return;
    deleteAllNodes(node->getLeft());
    deleteAllNodes(node->getRight());
    delete node;
}