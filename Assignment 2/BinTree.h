
/*
By Aditya Duggirala
*/
#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include "nodedata.h"
using namespace std;

class BinTree
{
  
private:
    struct Node
    {
        NodeData *data; // pointer to data object
        Node *left;     // left subtree pointer
        Node *right;    // right subtree pointer
    };
    Node *root; // root of the tree

     // helper for makeEmpty
    void makeEmptyHelper(Node *&current);

     // helper for overloaded =
    void assignHelper(Node *, Node *&);

    // helper for overloaded ==
    bool equalityCheckHelper(Node *, Node *) const;

     // helper for overloaded <<
    void inorderTraversal(Node *) const;

    // helper for getHeight
    int getHeightHelper(const NodeData &, Node *) const;

    // helper for the getHeighthelper
    int recursiveGetHeightHelper(Node *) const;

    // helper for insert
    bool insertHelper(Node *&, NodeData *);

    // helper for bstreeToArray
    int bstreeToArrayHelper(Node *, NodeData *[]);

    // helper for arrayToBSTree
    void arrayToBSTreeHelper(Node *, NodeData *[], int, int);

    // helper for displaySideways
    void sideways(Node *, int) const; // helper for displaySideways()

    // helper for retrieve
    bool retrieveHelper(Node *&, const NodeData &, NodeData *&) const;

public:
    // Constructors and Destructor
    BinTree();                // constructor
    BinTree(const BinTree &); // copy constructor
    ~BinTree();               // destructor, calls makeEmpty

    bool isEmpty() const; // true if tree is empty, otherwise false
    void makeEmpty();     // make the tree empty so isEmpty returns true

    // Assignment operator
    BinTree &operator=(const BinTree &);

    // Comparison operators
    bool operator==(const BinTree &) const;
    bool operator!=(const BinTree &) const;

    //Output operator
    friend ostream &operator<<(ostream &outStream, const BinTree &);

    // Inserts a node into a tree(Made from lab2.cpp)
    bool insert(NodeData *);

    // Returns the height of a particular node in a tree
    int getHeight(const NodeData &) const;

    // Builds an array of NodeData from a BSTree'
    void bstreeToArray(NodeData *[]);

    // Builds a BSTree from a NodeData array
    void arrayToBSTree(NodeData *[]);

    // Displays the tree sideways
    void displaySideways() const;

     // Searches a tree for a particular value(Made from lab2.cpp)
    bool retrieve(const NodeData &, NodeData *&);
};

#endif // BINTREE_BINTREE_H
