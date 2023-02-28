//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itself must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

/* ERROR OUTPUT FUNCTIONS*/

void errorInvalidName(){
  cout << "error: invalid name" << endl;
}

void errorNameExists(string n){
  cout << "error: name " << n << " exists" << endl;
}

void errorShapeNotFound(string n){
  cout << "error: shape " << n << " not found" << endl;
}

void errorGroupNotFound(string n){
  cout << "error: group " << n << " not found" << endl;
}

/* INSERT NEW SHAPENODE FUNCTION*/

ShapeNode* insertNewShape(GroupNode* gNode, string n, string t, int x_loc, int y_loc, int x_sz, int y_sz){
  Shape *newShape = new Shape(n, t, x_loc, y_loc, x_sz, y_sz);
  ShapeNode *newShapeNode = new ShapeNode();
  
  newShapeNode->setShape(newShape);
  (gNode->getShapeList())->insert(newShapeNode);
  return newShapeNode;
}

/* INSERT NEW GROUPNODE FUNCTION */

GroupNode* insertNewGroup(string n){
  GroupNode *newGroupNode = new GroupNode(n);
  
  gList->insert(newGroupNode);
  return newGroupNode;
}

/* MOVE SHAPE FROM ONE GROUPNODE TO ANOTHER */

void moveShape(ShapeNode *s, GroupNode *g1, GroupNode *g2){
  // remove the node with matching name from it's original group:
  (g1->getShapeList())->remove((s->getShape())->getName());
  (g2->getShapeList())->insert(s);
}

/* MOVE ALL SHAPES FROM ONE GROUP TO ANOTHER */

void moveAllShapes(GroupNode *g1, GroupNode *g2){
  ShapeNode *temp = (g1->getShapeList())->getHead();
  
  while (temp != nullptr){
    moveShape(temp, g1, g2);
    temp = (g1->getShapeList())->getHead();
  }
}

/* FIND GROUP WITH MATCHING NAME*/

GroupNode *findGroup(string n){
  GroupNode *currentGroup = gList->getHead();
  
  while (currentGroup != nullptr && currentGroup->getName() != n){
    currentGroup = currentGroup->getNext();
  }
  
  return currentGroup;
}

/* FIND SHAPE WITH MATCHING NAME ACROSS ALL GROUPS*/

ShapeNode *findShape(string n){
  GroupNode *currentGroup = gList->getHead();
  ShapeNode *currentShape = nullptr;
  
  while (currentGroup != nullptr){
    // look for shape in currentGroup
    currentShape = currentGroup->getShapeList()->find(n);
    
    // if shape not found then go to next group
    if (currentShape == nullptr){
      currentGroup = currentGroup->getNext();
    }else{
      // if shape found then return the currentShape pointer
      return currentShape;
    }
  }
  return nullptr; // if shape with given name not found, return nullptr
}

/* FIND THE GROUP OF A SHAPE WITH GIVEN NAME */

GroupNode *findShapeGroup(string n){
  GroupNode *currentGroup = gList->getHead();
  ShapeNode *currentShape = nullptr;
  
  while (currentGroup != nullptr){
    // look for shape in currentGroup
    currentShape = currentGroup->getShapeList()->find(n);
    
    // if shape not found then go to the next group
    if (currentShape == nullptr){
      currentGroup = currentGroup->getNext();
    }else{
      // if shape found then return the currentGroup pointer
      return currentGroup;
    }
  }
  return nullptr; // if shape with given name not found, return nullptr;
}

/* GET NEW NAME FROM STRINGSTREAM WITH ERROR CHECKING */

int getNewName(stringstream &input, string &n){
  string tmp;
  input >> tmp;
  // check if name is not a keyword
  if (tmp == keyWordsList[0] ||
          tmp == keyWordsList[1] ||
          tmp == keyWordsList[2] ||
          tmp == keyWordsList[3] ||
          tmp == keyWordsList[4] ||
          tmp == keyWordsList[5] ||
          tmp == shapeTypesList[0] ||
          tmp == shapeTypesList[1] ||
          tmp == shapeTypesList[2]){
    errorInvalidName();
    return -1;
  }else{
    // check if name is already used for a group
    GroupNode *matchingGroup = findGroup(tmp);
    if (matchingGroup == nullptr){
      
      // check if name is already used for a shape
      ShapeNode *matchingShape = findShape(tmp);
      if (matchingShape == nullptr){
        n = tmp;
        return 0;
      }else{
        errorNameExists(tmp);
        return -1;
      }
    }else{
      errorNameExists(tmp);
      return -1;
    }
  }
}

/* GET SHAPE FROM STRINGSTREAM WITH ERROR CHECKING */

int getShape(stringstream &input, string &n){
  string tmp;
  input >> tmp;
  
  if (tmp == keyWordsList[0] ||
          tmp == keyWordsList[1] ||
          tmp == keyWordsList[2] ||
          tmp == keyWordsList[3] ||
          tmp == keyWordsList[4] ||
          tmp == keyWordsList[5] ||
          tmp == shapeTypesList[0] ||
          tmp == shapeTypesList[1] ||
          tmp == shapeTypesList[2] ){
    errorInvalidName();
    return -1;
  }else{
    // check if shape exists
    ShapeNode *matchingShape = findShape(tmp);
    if (matchingShape == nullptr){
      errorShapeNotFound(tmp);
      return -1;
    }else{
      n = tmp;
      return 0;
    }
  }
}

/* GET GROUP FROM STRINGSTREAM WITH ERROR CHECKING */

int getGroup(stringstream &input, string &n){
  string tmp;
  input >> tmp;
  
  if (tmp == keyWordsList[0] ||
          tmp == keyWordsList[1] ||
          tmp == keyWordsList[2] ||
          tmp == keyWordsList[3] ||
          tmp == keyWordsList[4] ||
          tmp == shapeTypesList[0] ||
          tmp == shapeTypesList[1] ||
          tmp == shapeTypesList[2] ){
    errorInvalidName();
    return -1;
  }else{
    // check if group exists
    GroupNode *matchingGroup = findGroup(tmp);
    if (matchingGroup == nullptr){
      errorGroupNotFound(tmp);
      return -1;
    }else{
      n = tmp;
      return 0;
    }
  }
}

/* GET SHAPE OR GROUP FROM STRINGSTREAM WITH ERROR CHECKING */

int getExistingName(stringstream &input, string &n){
  string tmp;
  input >> tmp;
  // check if name is not a keyword
  if (tmp == keyWordsList[0] ||
          tmp == keyWordsList[1] ||
          tmp == keyWordsList[2] ||
          tmp == keyWordsList[3] ||
          tmp == keyWordsList[4] ||
          tmp == keyWordsList[5] ||
          tmp == shapeTypesList[0] ||
          tmp == shapeTypesList[1] ||
          tmp == shapeTypesList[2] ){
    errorInvalidName();
    return -1;
  }else{
    // check if name is already used for a group
    GroupNode *matchingGroup = findGroup(tmp);
    if (matchingGroup == nullptr){ // if group is not found
      ShapeNode *matchingShape = findShape(tmp);
      if (matchingShape == nullptr){ // if shape is not found
        errorShapeNotFound(tmp);
        return -1;
      }else{
        n = tmp;
        return 0;
      }
    }else{ // group is found
      n = tmp;
      return 0;
    }
  }
}

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    string Name, Type, Group;
    int X_loc = 0, Y_loc = 0, X_sz = 0, Y_sz = 0, errorCheck1 = 0, errorCheck2 = 0;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        if (command == keyWordsList[0]){ // SHAPE COMMAND - DONE
          
          //check for errors when getting name using getNewName Function
          errorCheck1 = getNewName(lineStream, Name);
          
          if (errorCheck1 != -1){
            lineStream >> Type;
            lineStream >> X_loc;
            lineStream >> Y_loc;
            lineStream >> X_sz;
            lineStream >> Y_sz;

            // Create the new shape, insert it into the poolGroup
            ShapeNode *nShape = insertNewShape(poolGroup, Name, Type, X_loc, Y_loc, X_sz, Y_sz);
            nShape->print(); // notify the user the shape has been printed
          }
          
        }else if (command == keyWordsList[1]){ // GROUP COMMAND - DONE
          
          // check for errors when getting name using getNewName Function
          errorCheck1 = getNewName(lineStream, Name);
          
          if (errorCheck1 != -1){
            GroupNode *nGroup = insertNewGroup(Name);
            cout << nGroup->getName() << ": " << "group" << endl;
          }
          
        }else if (command == keyWordsList[2]){ // MOVE COMMAND
          
          // check for errors when inputting shape
          errorCheck1 = getShape(lineStream, Name);
          if (errorCheck1 != -1){
            // check for errors when inputting group
            errorCheck2 = getGroup(lineStream, Group);

            if (errorCheck2 != -1){
              GroupNode *findG1 = findShapeGroup(Name);
              GroupNode *findG2 = findGroup(Group);

              moveShape((findG1->getShapeList())->find(Name), findG1, findG2);
              cout << "moved " << Name << " to " << Group << endl;
            }
          }
          
        }else if (command == keyWordsList[3]){ // DELETE COMMAND
          errorCheck1 = getExistingName(lineStream, Name);
          
          if (errorCheck1 != -1){
            
            // look for matching group name first
            GroupNode *findG1 = findGroup(Name);
            
            if (findG1 == nullptr){ // if matching group is not found then delete the matching shape
              ShapeNode *findS1 = findShape(Name);
              findG1 = findShapeGroup(Name);
              
              (findG1->getShapeList())->remove((findS1->getShape())->getName());
              delete findS1;
            }else{ // matching GroupNode is found so move all shapes back to poolgroup and delete the group
              moveAllShapes(findG1, poolGroup);
              
              // remove GroupNode from GroupList and delete it
              gList->remove(findG1->getName());
              delete findG1;
              findG1 = nullptr;
            }
            
            cout << Name << ": deleted" << endl;
          }
          
        }else if (command == keyWordsList[4]){ // DRAW COMMAND - DONE
          cout << "drawing: " << endl;
          
          // get first group
          GroupNode* currentGroup = gList->getHead();
          
          // loop through the groups and print them one by one
          while (currentGroup != nullptr){
            currentGroup->print();
            currentGroup = currentGroup->getNext();
          }
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

