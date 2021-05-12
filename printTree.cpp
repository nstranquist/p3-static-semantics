#include <iostream>
#include <stdio.h>
#include "node.h"
#include "tree.h"
#include "printTree.h"
#include "symbolTable.h"

using namespace std;

void PrintTree::semanticAnalyze(Node *root) {
  SymbolTable symbolTable;
  this->symbolTable = symbolTable;
  this->symbolTable.isBeforeMain = true;
  this->symbolTable.varCount = 0;
  this->symbolTable.blockCount = 0;
  this->stackLevel = 0; // Global = 0
  cout << "3. Analyzing Parse Tree for Semantics...\n\n" << endl;

  // print pre-order, use symbolTable functions as needed
  int startingLevel = 0;
  this->scanPreorder(root, startingLevel);

  cout << "Scan Complete. Tokens at the end: \n" << endl;
  cout << "Globals: \n" << endl;
  this->symbolTable.printStack(this->symbolTable.globalIdentifiers);
  cout << "\nLocals: \n" << endl;
  this->symbolTable.printStack(this->symbolTable.localIdentifiers);
}

void PrintTree::scanPreorder(Node *root, int level) {
  if (root==NULL) {
    cout << "root is null. returning" << endl;
    return;
  }

  // if variables before <main>, process as global variables (this->symbolTable->isBeforeMain)
  // else when working in a block (<begin>...<end>)
    // set varCount = 0;
    // if inside <vars>, handle variable declarations:
      // if varCount > 0, call find(var) and error/exit if returns non-negative integer that's < varCount (means multiple definitions)
    // else if inside non-vars:
      // when identifier token is found:
      // Call find(var), if returns -1 then try verify(var), throw error if still not found
    // when leaving the block (<end>):
      // call pop() varCount times
      // reset varCount
  if(root->label == "block") {
    cout << "is a block element, assuming start of block" << endl;
    // update var counts
    this->symbolTable.varCounts.push_back(0);
    this->symbolTable.blockCount++;
  }

  if(root->tokens.size() > 0) {
    // To keep track of correct variable usage
    bool previousData = false;
    bool previousIdentifier = false;
    bool previousAssign = false;

    cout << ": ";
    // Print All Token Values
    size_t i = 0;
    for(vector<Token*>::iterator t = root->tokens.begin(); t != root->tokens.end(); ++t) {
      cout << (*t)->tokenInstance << " ";
      if(root->label == "vars") {
        // Check that data -> identifier -> assign is used correctly for the variable
        if(previousData) {
          if((*t)->tokenID != IDENT_tk) {
            string errorMessage = "Error: Identifier expected after 'data' keyword on line #" + to_string((*t)->lineNumber);
            throw invalid_argument(errorMessage);
          }
        }
        if(previousIdentifier) {
          if((*t)->tokenInstance != ":=") {
            string errorMessage = "Error: Assign statement ':=' expected after [identifier] on line #" + to_string((*t)->lineNumber);
            throw invalid_argument(errorMessage);
          }
        }
        if(previousAssign) {
          cout << "next token should be an integer" << endl;
          if((*t)->tokenID != NUM_tk) {
            string errorMessage = "Error: Numeric token expected after [assign] on line #" + to_string((*t)->lineNumber);
            throw invalid_argument(errorMessage);
          }
        }

        if((*t)->tokenID == IDENT_tk) {
          if(!previousData) {
            string errorMessage = "Error: Identifier used in <vars> before 'data' keyword being used on line #" + to_string((*t)->lineNumber);
            throw invalid_argument(errorMessage);
          }
          previousIdentifier = true;
          cout << "is 'identifier' declaration" << endl;
          if(this->symbolTable.varCount > 0) {
            int found = this->symbolTable.find((*t)->tokenInstance);
            cout << "found value: " << found << endl;
            if(found >= 0 && found < this->symbolTable.varCounts.at(found)) {
              string errorMessage = "Error: Variable " + (*t)->tokenInstance + " at line #";
              errorMessage +=  to_string((*t)->lineNumber);
              errorMessage += " is already defined in this scope";
              throw invalid_argument(errorMessage);
            }
          }
          Symbol *symbol = this->symbolTable.createSymbol(*t);
          if(this->symbolTable.blockCount == 0) {
            this->symbolTable.globalIdentifiers.push_back(symbol);
          }
          else {
            this->symbolTable.push(symbol);
          }
          this->symbolTable.varCount++;
        }
        else {
          previousIdentifier = false;
        }

        if((*t)->tokenInstance == "data") {
          previousData = true;
        }
        else {
          previousData = false;
        }

        if((*t)->tokenInstance == ":=") {
          previousAssign = true;
        }
        else {
          previousAssign = false;
        }
      }
      else {
        if((*t)->tokenID == IDENT_tk) {
          cout << "is identifier token. is being used" << endl;
          int found = this->symbolTable.find((*t)->tokenInstance);
          if(found == -1) {
            int globalFound = this->symbolTable.findGlobal((*t)->tokenInstance);
            if(globalFound == -1) {
              string errorMessage = "Error: Variable " + (*t)->tokenInstance + " on line #";
              errorMessage += to_string((*t)->lineNumber);
              errorMessage += " was not found in scope";
              throw invalid_argument(errorMessage);
            }
            else {
              cout << "the variable was found in the globals. We are OK" << endl;
            }
          }
        }
      }

      ++i;

      // If is before <main>
        // If is <main>
          // Set isBeforeMain = false;
        // Else if is identifier
          // Add identifier to symbolTable as a global variable: this->symbolTable.push(...data);
        // Else... throw error(?)
      // Else if is not before <main>
        // If is identifier
          // If is in <vars>
            // If varCount > 0, call find(var) and error/exit if non-negative number that's < varCount (multiple definitions)
            // Then push(var) and this->varCount++;
          // If is not in <vars>
            // Call find(var), if -1, try this->symbolTable.verify(var) (to check if global variable). Error if still not found.
        // If is <begin> block
          // reset varCount = 0;
        // If is <end> block
          // call pop() varCount number of times
          // reset varCount = 0; (or pop from vector if using that option)
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

  if(root->label == "block") {
    cout << "assuming end of block" << endl;
    // this->symbolTable.blockCount--;
    // pop varCount number of times
    int numVars;
    int varCountsSize = this->symbolTable.varCounts.size();
    if(varCountsSize > 0) {
      cout << "size > 0: " << varCountsSize << endl;
      numVars = this->symbolTable.varCounts[varCountsSize - 1];
    }
    else {
      numVars = 0;
    }
    cout << "numVars: " << numVars << endl;
    for(int i = numVars; i>0; i--) {
      this->symbolTable.pop();
    }
    this->symbolTable.varCounts.pop_back();
    cout << "made out of block" << endl;
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
