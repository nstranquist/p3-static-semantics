#include <iostream>
#include "node.h"
#include "tree.h"
#include "printTree.h"
#include "symbolTable.h"

using namespace std;

// - Each node will print one line or possibly nothing (if the leave has nothing in it).
// - The line will start with indentations of 2 spaces per level, then display the node's label and any tokes stored in the node
// - Continue over children left to right

void PrintTree::semanticAnalyze(Node *root) {
  SymbolTable symbolTable;
  this->symbolTable = symbolTable;
  cout << "3. Analyzing Parse Tree for Semantics...\n\n" << endl;

  // print pre-order, use symbolTable functions as needed
  int startingLevel = 0;
  this->scanPreorder(root, startingLevel);

  cout << "Scan Complete. Tokens at the end: " << endl;
  this->symbolTable.printTokens();
}

void PrintTree::scanPreorder(Node *root, int level) {
  if (root==NULL) {
    cout << "root is null. returning" << endl;
    return;
  }

  // cout << "Label: " << root->label << endl;
  // cout << std::string((level*2), '-') << root->label
  //   << ": " << root->nodes.size() << " nodes, "
  //   << root->tokens.size() << " tokens";

  // If In <vars>, run symbolTable.insert();
  // Else, run symbolTable.verify();
  bool isVars = false;
  if(root->label == "vars") {
    isVars = true;
  }

  if(root->tokens.size() > 0) {
    cout << ": ";
    // Print All Token Values
    size_t i = 0;
    for(vector<Token*>::iterator t = root->tokens.begin(); t != root->tokens.end(); ++t) {
      cout << (*t)->tokenInstance << " ";
      // If is Identifier
      if((*t)->tokenID==IDENT_tk) {
        // If Is vars, insert, else, verify
        if(isVars) {
          cout << "is vars, checking then inserting" << endl;
          // If exists, throw error
          bool isFound = this->symbolTable.verify((*t)->tokenInstance);
          if(isFound) {
            string errorMessage = "Error: Identifier '" + (*t)->tokenInstance + "' is already in use on line #";
            errorMessage +=  (*t)->lineNumber;
            throw invalid_argument(errorMessage);
          }
          // else, insert into table
          else {
            this->symbolTable.insert((*t)->tokenInstance);
          }
        }
        else {
          cout << "is not vars, verifying" << endl;
          bool isFound = this->symbolTable.verify((*t)->tokenInstance);
          if(isFound) {
            // Throw Error:
            cout << "ERROR: Identifier '" << (*t)->tokenInstance << "' is already being used" << endl;
          }
        }
      }
      ++i;
    }
  }
  cout << "\n";

  // Iterate over vectors, from left to right, calling printPreorder() on the vector
  // (source) https://cal-linux.com/tutorials//vectors.html
  size_t i = 0;
  for(vector<Node*>::iterator t = root->nodes.begin(); t != root->nodes.end(); ++t) {
    scanPreorder(root->nodes[i], level + 1);
    ++i;
  }
}

void PrintTree::printTree(Node *root)
{
  cout << "2. Printing Tree...\n\n";

  // Print with Preorder traversal, with indentations, for testing purposes
  int startingLevel = 0;
  this->printPreorder(root, startingLevel);
}

void PrintTree::printPreorder(Node *root, int level) {
  if (root==NULL) {
    cout << "root is null. returning" << endl;
    return;
  }

  // cout << "Label: " << root->label << endl;
  cout << std::string((level*2), '-') << root->label
    << ": " << root->nodes.size() << " nodes, "
    << root->tokens.size() << " tokens";

  if(root->tokens.size() > 0) {
    cout << ": ";
    // Print All Token Values
    size_t i = 0;
    for(vector<Token*>::iterator t = root->tokens.begin(); t != root->tokens.end(); ++t) {
      cout << (*t)->tokenInstance << " ";
      ++i;
    }
  }
  cout << "\n";

  // Iterate over vectors, from left to right, calling printPreorder() on the vector
  // (source) https://cal-linux.com/tutorials//vectors.html
  size_t i = 0;
  for(vector<Node*>::iterator t = root->nodes.begin(); t != root->nodes.end(); ++t) {
    printPreorder(root->nodes[i], level + 1);
    ++i;
  }
}
