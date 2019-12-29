/* 
 * File:   main.cpp
 * Author: Malhar Shah
 *
 * Created on November 21, 2019, 6:36 PM
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;

int main(int argc, char** argv) {
    string line, command, name, status;
    string COMMANDS[8] = {"insert", "find", "remove", "printall", "printprobes", "removeall", "countactive", "updatestatus"};
    bool activeStatus;
    unsigned int IPaddress;
    
    TreeDB testTreeDB;
    
    cout << "> "; 
    getline(cin, line);
    
    while(!cin.eof() && !cin.fail()) {
        stringstream linestream(line);
        linestream >> command;
        
        if(command.compare(COMMANDS[0]) == 0) {
            linestream >> name >> IPaddress >> status;
            if(status.compare("active") == 0)
                activeStatus = true;
            else activeStatus = false;
            DBentry* newEntry = new DBentry(name, IPaddress, activeStatus);
            if(!testTreeDB.insert(newEntry))
                delete newEntry;
        }
        else if(command.compare(COMMANDS[1]) == 0) {
            linestream >> name;
            DBentry* entryFound = testTreeDB.find(name);
            if(entryFound != nullptr)
                cout << (*entryFound);
        }
        else if(command.compare(COMMANDS[2]) == 0) {
            linestream >> name;
            if(testTreeDB.remove(name))
                cout << "Success" << endl;
            else
                cout << "Error: entry does not exist" << endl;
        }
        else if(command.compare(COMMANDS[3]) == 0) {
            cout << testTreeDB;
        }
        else if(command.compare(COMMANDS[4]) == 0) {
            linestream >> name;
            DBentry* entryFound = testTreeDB.find(name);
            if(entryFound != nullptr)
                testTreeDB.printProbes();
        }
        else if(command.compare(COMMANDS[5]) == 0) {
            testTreeDB.clear();
            cout << "Success" << endl;
        }
        else if(command.compare(COMMANDS[6]) == 0) {
            testTreeDB.countActive();
        }
        else if(command.compare(COMMANDS[7]) == 0) {
            linestream >> name >> status;
            if(status.compare("active") == 0)
                activeStatus = true;
            else activeStatus = false;
            DBentry* findEntry = testTreeDB.find(name);
            if (findEntry != nullptr) {
                findEntry->setActive(activeStatus);
                cout << "Success" << endl;
            }
        }
        cout << "> ";
        getline(cin, line);
    }
    return 0;
}

