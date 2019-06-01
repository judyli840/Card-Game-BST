//cards.h
//Authors: Your name and your partner's name
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>

using namespace std;

struct Node {
  int info;
  Node *left, *right, * parent;
  // useful constructor:
  Node(int v=0) : info(v), left(0), right(0), parent(0) { }
};

int convertCard(string val);  // convert card string to integer value
string convertInt(int i);     // convert integer value to card string

class Cards {
 public:
    // ctor, dtor, insert and one print method already done in cards.cpp:
    Cards();                   // constructor
    ~Cards();                  // destructor
    bool insert(string val);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    // 8 METHODS YOU MUST IMPLEMENT in cards.cpp:
    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(int value) const;  // true if value is in tree
    Node* getMin() const;            // returns pointer to min
    Node* getMax() const;            // returns pointer to max

    // THESE ARE HARDER! DO THESE LAST
    int getPredecessor(int value) const;       // returns the predecessor value of the given value or 0 if there is none
    int getSuccessor(int value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(int value);                    // deletes the Node containing the given value from the tree

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(int value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(int value) const; // returns the Node containing the predecessor of the given value

 private:
    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(int value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(int value, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int sum(Node *n) const;
    int count(Node *n) const;
};
#endif

