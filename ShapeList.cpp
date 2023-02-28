//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Ridvik Pal
//  Write the implementation (and only the implementation) of the ShapeList class below

#include <string>
#include <iostream>

using namespace std;

#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"

// Constructor - DONE
ShapeList::ShapeList(){
  head = nullptr;
}

// Destructor - DONE
ShapeList::~ShapeList(){
  ShapeNode* temp = head; //stores head temporarily

  while (head != nullptr){
    temp = head;
    head = head->getNext();
    delete temp;
    temp = nullptr;
  }
}

// Accessor - DONE
ShapeNode* ShapeList::getHead() const{
  return head;
}

// Mutator - DONE
void ShapeList::setHead(ShapeNode* ptr){
  head = ptr;
}

// find location of shapeNode with matching name - DONE
ShapeNode* ShapeList::find(string name) const{
  ShapeNode* temp = head;
  
  while (temp != nullptr && (temp->getShape())->getName() != name){
    temp = temp->getNext();
  }
  return temp;
}

// insert given ShapeNode into the end of the linked list - DONE
void ShapeList::insert(ShapeNode* s){
  if (s != nullptr){
    if (head == nullptr){ // if no elements in the list, insert at head
      head = s;
    }else{ // there are elements in the list, append to the list
      ShapeNode* temp = head;
      // find the location of the last node in the linked list
      while (temp->getNext() != nullptr){
        temp = temp->getNext();
      }
      // insert the node at the end of the list
      temp->setNext(s);
    }
  }
}

// removes a ShapeNode from the linked list and returns a pointer to that ShapeNode - DONE
ShapeNode* ShapeList::remove(string name){
  ShapeNode *temp = head, *previous = nullptr;
  
  // if head node is a match
  if ((temp->getShape())->getName() == name){
    head = head->getNext();
    temp->setNext(nullptr);
    return temp;
  }else{ // first node is not a match
    
    // loop through the linkedlist
    while (temp != nullptr && (temp->getShape())->getName() != name){
      previous = temp;
      temp = temp->getNext();
    }
    
    // if match found, then perform the swap of next pointers
    if (temp != nullptr){
      previous->setNext(temp->getNext());
      temp->setNext(nullptr);
    }
    
    return temp;
  }
}

// prints out the ShapeList
void ShapeList::print() const{
  ShapeNode *temp = head;
  while (temp != nullptr){
    temp->print();
    temp = temp->getNext();
  }
}