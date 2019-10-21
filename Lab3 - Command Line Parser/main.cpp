//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented
// every time a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

//Function checks if the first word entered matches one of the valid commands
bool checkForInvalidCommand(string command);

//Function checks if the name used for a shape is a reserved word 
bool checkForInvalidShapeName(string shapeName);

//Function checks if a shape with the same name already exists in the database
bool checkForExistingShapeName(string shapeName);

//Function searches for a specified name
bool searchForShapeName(string shapeName);

//Function checks if the shape type is valid
bool checkForInvalidShapeType(string shapeType);

//Function checks if input value is valid
bool checkForInvalidValue(int value, string argument);

//Function checks for too many arguments to a command  
bool checkForTooManyArguments(stringstream & lineStream);

//Function checks for too few/ invalid arguments
bool checkForTooFewArgumentsOrInvalidArgument(stringstream & lineStream);

//Function checks if the shapesArray is full or not
bool checkForFullShapeArray();

//Function returns the Array Position for specified shape
int returnArrayPosition(string shapeName);

//Performs the necessary steps of maxShapes Command
void maxShapesCommand(stringstream & lineStream);

//Performs the necessary steps of create Command
void createCommand(stringstream & lineStream);

//Performs the necessary steps of move Command
void moveCommand(stringstream & lineStream);

//Performs the necessary steps of rotate Command
void rotateCommand(stringstream & lineStream);

//Performs the necessary steps of draw Command
void drawCommand(stringstream & lineStream);

//Performs the necessary steps of delete Command
void deleteCommand(stringstream & lineStream);

int main() {

    string line;
    string command;
   
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        // Function verifies valid command input
        if (!checkForInvalidCommand(command))
        {
            //Function chooses between different possible command outputs
            if (command == "maxShapes")
            {
                maxShapesCommand(lineStream);
            }
            
            else if (command == "create")
            {
                createCommand(lineStream);
            }
            
            else if (command == "move")
            {
                moveCommand(lineStream);
            }
            
            else if (command == "rotate")
            {
                rotateCommand(lineStream);
            }
            
            else if (command == "draw")
            {
                drawCommand(lineStream);
            }
            
            else if (command == "delete")
            {
                deleteCommand(lineStream);
            }
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
       
    }  // End input loop until EOF.
    return 0;
}

bool checkForInvalidCommand(string command)
{
    //Function returns false for valid commands
    if (command == "maxShapes" || command == "create" || command == "move" || 
        command == "rotate" || command == "draw" || command == "delete")
    {
        return false;
    }
    
    //Function returns true for invalid commands
    else
    {
        cout << "Error: invalid command" << endl;
        return true;
    }
}

bool checkForInvalidShapeName(string shapeName)
{
    //Functions checks through both reserved list of words
    for (int i = 0; i < 7; i++)
    {
        if (shapeName == keyWordsList[i])
        {
            cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (shapeName == shapeTypesList[i])
        {
            cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    return false;
}


bool checkForExistingShapeName(string shapeName)
{
    //Checks if a shape with the same name exists in the database, i.e., 
    //has once been created and has not been deleted
    for (int i = 0; i < max_shapes; i++)
    {
        if (shapesArray[i] != NULL) 
        {
            if (shapeName == shapesArray[i]->getName())
            {
                cout << "Error: shape " << shapeName << " exists" << endl;
                return true;
            }
        }
    }
    return false;
}

bool searchForShapeName(string shapeName)
{
    //Function returns true if the shape name exists
    for (int i = 0; i < max_shapes; i++)
    {
        if (shapesArray[i] != NULL) 
        {
            if (shapeName == shapesArray[i]->getName())
            {
                return true;
            }
        }
    }
    
    //Function returns false if the shape name is not found
    cout << "Error: shape " << shapeName << " not found" << endl;
    return false;;
}

bool checkForInvalidShapeType(string shapeType)
{
    //Function returns false for valid shape types
    if (shapeType == "ellipse" || shapeType == "rectangle" || 
        shapeType == "triangle")
    {
        return false;
    }
    
    //Function returns true for invalid shape types
    else
    {
        cout << "Error: invalid shape type" << endl;
        return true;
    }
}


bool checkForInvalidValue(int value, string argument)
{
    //Functions returns true if the the value specified is valid
    if (value < 0 )
    {
        cout << "Error: invalid value" << endl;
        return true;
    }
    
    else if (value > 360 && argument == "angle")
    {
        cout << "Error: invalid value" << endl;
        return true;
    }
    
    //Function returns false otherwise
    else return false;
}

bool checkForTooManyArguments(stringstream & lineStream)
{
    //Function peeks ahead to check if there are more arguments being entered
    char lookAhead;
    int peekValue = lineStream.peek();
    
    //Function returns true if the lineStream doesn't see a NULL character
    if(!lineStream.eof())
    {
        //while (peekValue != ws)
        cout << "Error: too many arguments" << endl;
        return true;
    }
    
    //Function returns false otherwise
    return false;
}

bool checkForTooFewArgumentsOrInvalidArgument(stringstream & lineStream)
{
    if (lineStream.fail())
    {
        //Function returns true if fewer arguments were given than expected 
        //for a command 
        if (lineStream.eof())
        {
            cout << "Error: too few arguments" << endl;
            return true;
        }
        
        //Function returns true if the argument is not of the correct type
        else
        {
            cout << "Error: invalid argument" << endl;
            return true;
        }
    }
    
    //Function returns false otherwise
    return false;
}
        
bool checkForFullShapeArray()
{
    //Function returns true if the shapeCount = max_shapes
    if (shapeCount == max_shapes)
    {
        cout << "Error: shape array is full" << endl;
        return true;
    }
    
    //Function returns false otherwise
    return false;
}

int returnArrayPosition(string shapeName)
{
    //Looks through the entire array to returns the Array Position of the shape
    for (int i = 0; i < max_shapes; i++)
    {
        if (shapesArray[i] != NULL) 
        {
            if (shapeName == shapesArray[i]->getName())
            {
                return i; 
            }
        }
    }
    
    //If the function can not find the shape, returns negative 1
    return -1;
}

void maxShapesCommand(stringstream & lineStream)
{
    lineStream >> max_shapes;
    if (!checkForTooFewArgumentsOrInvalidArgument(lineStream))
    {
        if (!checkForInvalidValue(max_shapes, "value"))
        {
            if (!checkForTooManyArguments(lineStream))
            {
                //Function dynamically allocates space for the shapes after
                //checking for errors
                shapesArray = new shape*[max_shapes];
                for (int i = 0; i < max_shapes; i++)
                {
                    shapesArray[i] = NULL;
                }
                
                //Confirmation message is printed
                cout << "New database: max shapes is " << max_shapes << endl;
            }
        }
    }
    return;
}

//Logic Implementation for the create Command
void createCommand(stringstream & lineStream)
{
    //Create variables to store arguments
    string name, type;
    int x_loc, y_loc, x_sz, y_sz;

    //Receives inputs and error checks
    lineStream >> name;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidShapeName(name)) return;
    else if (checkForExistingShapeName(name)) return;

    lineStream >> type;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidShapeType(type)) return;
    
    lineStream >> x_loc;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(x_loc, "loc")) return;
    
    lineStream >> y_loc;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(y_loc, "loc")) return;
    
    lineStream >> x_sz;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(x_sz, "size")) return;
    
    lineStream >> y_sz;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(y_sz, "size")) return;
    
    if (checkForTooManyArguments(lineStream)) return;
   
    if(!checkForFullShapeArray())
    {
        //Creates the specified shape after passing through all
        //required conditions
        shapesArray[shapeCount] = new shape(name, type, x_loc, y_loc, x_sz, 
                                              y_sz);
        cout << "Created " << name << ": " << type << " " << x_loc << " " 
             << y_loc << " " << x_sz << " " << y_sz << endl;
        shapeCount++;
    }
    return;
}

//Logic Implementation for the move Command
void moveCommand(stringstream & lineStream)
{
    string name;
    int x_loc, y_loc, arrayLocationOfShape;
    
    //Receives inputs and error checks
    lineStream >> name;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (!searchForShapeName(name)) return;
    
    lineStream >> x_loc;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(x_loc, "loc")) return;
    
    lineStream >> y_loc;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(y_loc, "loc")) return;
    
    if (checkForTooManyArguments(lineStream)) return;
    
    arrayLocationOfShape = returnArrayPosition(name);
    
    //Performs move action using class mutators after error checking
    shapesArray[arrayLocationOfShape]->setXlocation(x_loc);
    shapesArray[arrayLocationOfShape]->setYlocation(y_loc);
    
    //Prints confirmation message
    cout << "Moved " << name << " to " << x_loc << " " << y_loc << endl;
}

//Logic Implementation for the rotate Command
void rotateCommand(stringstream & lineStream)
{
    string name;
    int angle, arrayLocationOfShape;
    
    //Receives inputs and error checks
    lineStream >> name;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (!searchForShapeName(name)) return;
    
    lineStream >> angle;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (checkForInvalidValue(angle, "angle")) return;
    
    if (checkForTooManyArguments(lineStream)) return;
    
    arrayLocationOfShape = returnArrayPosition(name);
    
    //Performs rotation if all inputs are valid
    shapesArray[arrayLocationOfShape]->setRotate(angle);
    
    //Prints confirmation message
    cout << "Rotated " << name << " by " << angle << " degrees" << endl;
}

//Logic Implementation for the draw Command
void drawCommand(stringstream & lineStream)
{
    string argument;
    int arrayLocationOfShape;
    
    //Receives inputs and error checks
    lineStream >> argument;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (argument != "all")
    {
        if (!searchForShapeName(argument)) return;
    }
    if (checkForTooManyArguments(lineStream)) return;
    
    //"Draw all" command
    if (argument == "all")
    {
        cout << "Drew all shapes" << endl;
        for (int i = 0; i < max_shapes; i++)
        {
            if (shapesArray[i] != NULL)
            {
                shapesArray[i]->draw();
            }
        }
    }
    
    else
    {
        //Finds specified shape and calls the draw function on the shape
        arrayLocationOfShape = returnArrayPosition(argument);
        cout << "Drew " << argument << endl;
        shapesArray[arrayLocationOfShape]->draw();
    } 
}

//Logic Implementation for the delete Command
void deleteCommand(stringstream & lineStream)
{
    string argument;
    int arrayLocationOfShape;
    
    //Receives inputs and error checks
    lineStream >> argument;
    if (checkForTooFewArgumentsOrInvalidArgument(lineStream)) return;
    else if (argument != "all")
    {
        if (!searchForShapeName(argument)) return;
    }
    if (checkForTooManyArguments(lineStream)) return;
    
    //"Delete all" command
    if (argument == "all")
    {
        for (int i = 0; i < max_shapes; i++)
        {
            if (shapesArray[i] != NULL)
            {
                delete shapesArray[i];
                shapesArray[i] = NULL;
            }
        }
        cout << "Deleted: all shapes" << endl;
    }
    
    else 
    {
        //Finds specified shape and calls the delete function on the shape
        arrayLocationOfShape = returnArrayPosition(argument);
        delete shapesArray[arrayLocationOfShape];
        shapesArray[arrayLocationOfShape] = NULL;
    
        cout << "Deleted shape " << argument << endl;
    }
}
