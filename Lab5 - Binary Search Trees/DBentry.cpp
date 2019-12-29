#include <iostream>
#include <cstdlib>
#include <string>
#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

//Default constructor
DBentry::DBentry(){}

//Constructs a DBentry with specifies name, IPaddress, and active status
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

//Destructor
DBentry::~DBentry(){}	

//Sets the domain name, which we will use as a key
void DBentry::setName(string _name) {
    name = _name;
}

//Sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress) {
    IPaddress = _IPaddress;
}
    
//Sets whether or not this entry is active
void DBentry::setActive(bool _active){
    active = _active;
}

//Returns the name
string DBentry::getName() const {
    return name;
}

//Returns the IPaddress data
unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

//Returns whether or not this entry is active
bool DBentry::getActive() const {
    return active;
}

//Prints the entry in the format 
//name : IPaddress : active  followed by newline
//Active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs) {
    string status = "active";
    if(!rhs.active)
        status = "inactive";
    out << rhs.name << " : " << rhs.IPaddress << " : " << status << endl;
    return out;
}