#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include "node.h"
#include "token.h"

using namespace std;

class SymbolTable {
  public:
    void insert(string identifierName);
    bool verify(string identifierName);
    void printTokens();

  private:
    vector<string> identifierNames;
    bool searchName(string name);
};

#endif