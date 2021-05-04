#include <stdio.h>
#include <iostream>
#include "symbolTable.h"

using namespace std;

void SymbolTable::insert(string identifierName) {
  // Can Add Scope later, maybe to state
  cout << "\ninserting identifier: " << identifierName << endl;

  this->identifierNames.push_back(identifierName);

  cout << "this is a next identifer in the sequence and we need to do something about it. Okay? Okay? We see what's bout ot happen ext okay" << endl;
}

bool SymbolTable::verify(string identifierName) {
  cout << "\nverifying uniqueness of identifier: " << identifierName << endl;

  bool found = this->searchName(identifierName);

  cout << "Is Found? " << found << endl; // 1 is true, 0 is false
  
  return found;
}

bool SymbolTable::searchName(string name) {
  // Search through the identifierNames vector for the name
  // If found, return true. Else, return false

  for(size_t i = 0; i<this->identifierNames.size(); ++i) {
    if(this->identifierNames[i] == name) {
      cout << "found name in identifiers. returning true" << endl;
      return true;
    }
  }

  return false;
}

void SymbolTable::printTokens() {
  for(size_t i = 0; i<this->identifierNames.size(); ++i) {
    cout << "Identifier: " << this->identifierNames[i] << endl;
  }
}