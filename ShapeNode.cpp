//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Ridvik Pal
//  Write the implementation (and only the implementation) of the ShapeNode class below

#include <string>
#include <iostream>

using namespace std;

#include "ShapeNode.h"
#include "Shape.h"

// Constructor - DONE
ShapeNode::ShapeNode(){
  myShape = nullptr;
  next = nullptr;
}

// Destructor - DONE
ShapeNode::~ShapeNode(){
  if (myShape != nullptr){
    delete myShape;
    myShape = nullptr;
  }
}

// Mutators - DONE
Shape* ShapeNode::getShape() const{
  return myShape;
}

ShapeNode* ShapeNode::getNext() const{
  return next;
}

// Mutators - DONE
void ShapeNode::setShape(Shape* ptr){
  myShape = ptr;
}

void ShapeNode::setNext(ShapeNode* ptr){
  next = ptr;
}

// Print Method
void ShapeNode::print() const{
  myShape->draw();
}