//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Ridvik Pal
//  Write the implementation (and only the implementation) of the GroupList class below

#include <string>
#include <iostream>

using namespace std;

#include "GroupList.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"

// Constructor - DONE
GroupList::GroupList(){
  head = nullptr;
}

// Destructor - DONE
GroupList::~GroupList(){
  GroupNode* temp = head;
  
  while (head != nullptr){
    temp = head;
    head = head->getNext();
    delete temp;
    temp = nullptr;
  }
}

// Accessor - DONE
GroupNode* GroupList::getHead() const{
  return head;
}

// Mutator - DONE
void GroupList::setHead(GroupNode* ptr){
  head = ptr;
}

// insert group into GroupList - DONE
void GroupList::insert(GroupNode* s){
  if (s != nullptr){
    if (head == nullptr){ // if no elements in the list, insert at head
      head = s;
    }else{ // if there are elements in the list, append to the list
      GroupNode* temp = head;
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
GroupNode* GroupList::remove(string name){
  GroupNode *temp = head, *previous = nullptr;
  
  // if head node is a match
  if (temp->getName() == name){
    head = head->getNext();
    temp->setNext(nullptr);
    return temp;
  }else{ // first node is not a match
    
    // loop through the linked list
    while (temp != nullptr && temp->getName() != name){
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

// prints out the GroupList - DONE
void GroupList::print() const{
  GroupNode *temp = head;
  while (temp != nullptr){
    temp->print();
    temp = temp->getNext();
  }
}