#include <iostream>
#include "node.h"
#include "tree.h"
#include "printTree.h"

using namespace std;

// - Each node will print one line or possibly nothing (if the leave has nothing in it).
// - The line will start with indentations of 2 spaces per level, then display the node's label and any tokes stored in the node
// - Continue over children left to right

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
    << root->tokens.size() << " tokens"
    << endl;
  // Iterate over vectors, from left to right, calling printPreorder() on the vector
  // (source) https://cal-linux.com/tutorials//vectors.html
  size_t i = 0;
  for(vector<Node*>::iterator t = root->nodes.begin(); t != root->nodes.end(); ++t) {
    printPreorder(root->nodes[i], level + 1);
    ++i;
  }
}

// void printPreorder(Node *root, int level) {
//   if (root==NULL) return;
//   // printf("%*c%d:%-9s ",level*2,' ',level/*, NodeId.info*/); // assume some info printed as string
//   printf("\n");
//   // cout << root->data << " ";
//   printPreorder(root->left,level+1);
//   printPreorder(root->right,level+1);
// }