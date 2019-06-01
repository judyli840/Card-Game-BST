//cards.cpp
//Timothy Yuan
//Implementation of the classes defined in cards.h

#include "cards.h"

#include <iostream>
#include <string>
using std::cout;

// convert card string to integer value
int convertCard(string val){
  int value = 0;
  if(val[0]=='d'){
    value += 13;
  }else if(val[0]=='s'){
    value += 26;
  }else if(val[0]=='h'){
    value += 39;
  }
  if(val.substr(2)=="a"){
    value += 1;
  }else if(val.substr(2)=="j"){
    value += 11;
  }else if(val.substr(2)=="q"){
    value += 12;
  }else if(val.substr(2)=="k"){
    value += 13;
  }else{
    value += stoi(val.substr(1));
  }
  return value;
}

// convert int to card string
string convertInt(int i){
  string s = "";
  if((i-1)/13==0){
    s+="c";
  }else if((i-1)/13==1){
    s+="d";
  }else if((i-1)/13==2){
    s+="s";
  }else{
    s+="h";
  }
  s+=" ";
  if(i%13==1){
    s+="a";
  }else if(i%13==11){
    s+="j";
  }else if(i%13==12){
    s+="q";
  }else if(i%13==0){
    s+="k";
  }else{
    s+=std::to_string(i%13);
  }
  return s;
}

// constructor sets up empty tree
Cards::Cards() : root(0) { }

// destructor deletes all nodes
Cards::~Cards() {
    clear(root);
}

// recursive helper for destructor
void Cards::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool Cards::insert(string val) {
  int value = convertCard(val);
    // handle special case of empty tree first
    if (!root) {
	     root = new Node(value);
	     return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool Cards::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void Cards::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void Cards::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void Cards::printInOrder() const {
    printInOrder(root);
}
void Cards::printInOrder(Node *n) const {
    if(n){
      printInOrder(n->left);
      cout << convertInt(n->info) << endl;
      printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void Cards::printPostOrder() const {
    printPostOrder(root);
}

void Cards::printPostOrder(Node *n) const {
  if(n){
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
  }
}

// return sum of values in tree
int Cards::sum() const {
    return sum(root);
}

// recursive helper for sum
int Cards::sum(Node *n) const {
    if(!n)return 0;
    return n->info+sum(n->left)+sum(n->right);
}

// return count of values
int Cards::count() const {
    return count(root);
}

// recursive helper for count
int Cards::count(Node *n) const {
    if(!n)return 0;
    return 1+count(n->left)+count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
Node* Cards::getNodeFor(int value, Node* n) const{
    if(!n)return NULL;
    if(n->info==value)return n;
    if(n->info>value){
      return getNodeFor(value, n->left);
    }else{
      return getNodeFor(value, n->right);
    }
}

// returns true if value is in the tree; false if not
bool Cards::contains(int value) const {
    Node* n = getNodeFor(value, root);
    if(n)return true;
    return false;
  }

//returns pointer to min
Node* Cards::getMin() const{
  Node* n = root;
  while(n->left){
    n=n->left;
  }
  return n;
}

//returns pointer to max
Node* Cards::getMax() const{
  Node* n = root;
  while(n->right){
    n=n->right;
  }
  return n;
}

// returns the Node containing the predecessor of the given value
Node* Cards::getPredecessorNode(int value) const{
  Node* n = getNodeFor(value, root);
  if(!n){
    return NULL;
  }
  if(n->left){
    n=n->left;
    while(n->right){
      n=n->right;
    }
    return n;
  }else{
    while(n->parent&&n->info<n->parent->info){
      n=n->parent;
    }
    return n->parent;
  }
}

// returns the predecessor value of the given value or 0 if there is none
int Cards::getPredecessor(int value) const{
  Node* n = getPredecessorNode(value);
  if(n)return n->info;
  return 0;
}

// returns the Node containing the successor of the given value
Node* Cards::getSuccessorNode(int value) const{
  Node* n = getNodeFor(value, root);
  if(!n){
    return NULL;
  }
  if(n->right){
    n=n->right;
    while(n->left){
      n=n->left;
    }
    return n;
  }else{
    while(n->parent&&n->info>n->parent->info){
      n=n->parent;
    }
    return n->parent;
  }
}

// returns the successor value of the given value or 0 if there is none
int Cards::getSuccessor(int value) const{
  Node* n = getSuccessorNode(value);
  if(n)return n->info;
  return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool Cards::remove(int value){
    Node* n = getNodeFor(value, root);
    if(!n)return false;
    if(!n->parent){
      if(!n->left&&!n->right){
        root = 0;
      }else if(!n->left){
        n->right->parent = 0;
        root = n->right;
      }else if(!n->right){
        n->left->parent=0;
        root = n->left;
      }else{
        int tmp = getPredecessor(value);
        remove(tmp);
        n->info = tmp;
        return true;
      }
      delete n;
      return true;
    }
    if(!n->left&&!n->right){
      if(n==n->parent->left){
        n->parent->left=0;
      }else{
        n->parent->right=0;
      }
      delete n;
      return true;
    }else if(!n->left){
      n->right->parent = n->parent;
      if(n==n->parent->left){
        n->parent->left = n->right;
      }else{
        n->parent->right = n->right;
      }
      delete n;
      return true;
    }else if(!n->right){
      n->left->parent = n->parent;
      if(n==n->parent->left){
        n->parent->left = n->left;
      }else{
        n->parent->right = n->left;
      }
      delete n;
      return true;
    }else{
      int tmp = getPredecessor(value);
      remove(tmp);
      n->info = tmp;
      return true;
    }
}

