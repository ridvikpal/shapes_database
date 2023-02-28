//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Ridvik Pal
//  Write the implementation (and only the implementation) of the GroupNode class below

#include <string>
#include <iostream>

using namespace std;

#include "GroupNode.h"
#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"

// Constructor - DONE
GroupNode::GroupNode(string n){
  name = n;
  myShapeList = new ShapeList();
  next = nullptr;
}

// Destructor - DONE
GroupNode::~GroupNode(){
  if (myShapeList != nullptr){
    delete myShapeList;
    myShapeList = nullptr;
  }
}

// Accessors - DONE
string GroupNode::getName() const{
  return name;
}

ShapeList* GroupNode::getShapeList() const{
  return myShapeList;
}

GroupNode* GroupNode::getNext() const{
  return next;
}

// Mutators - DONE
void GroupNode::setShapeList(ShapeList* ptr){
  myShapeList = ptr;
}

void GroupNode::setNext(GroupNode* ptr){
  next = ptr;
}

// Print out group - DONE
void GroupNode::print() const{
  cout << name << ": " << endl;
  myShapeList->print();
}