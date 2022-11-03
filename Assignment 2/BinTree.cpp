/*
By Aditya Duggirala
*/

#include "BinTree.h"
#include <algorithm>

using namespace std;

// default constructor creates empty tree
BinTree::BinTree()
{
    this->root = NULL;
}
// copy constructor makes a deep copy of a tree
BinTree::BinTree(const BinTree &tree)
{
    this->root = NULL;
    *this = tree;
}
// destructor
BinTree::~BinTree()
{
    this->makeEmpty();
}
// checks if tree is empty
bool BinTree::isEmpty() const
{
    if (this->root == NULL)
        return true;

    return false;
}

void BinTree::makeEmpty() // deletes all nodes in tree
{
    makeEmptyHelper(root);
}

void BinTree::makeEmptyHelper(Node *&curr) // deletes all nodes using postorder
{
    if (curr != NULL) // if root isn't null
    {
        makeEmptyHelper(curr->left); 
        makeEmptyHelper(curr->right);

        if (curr->data != NULL) // data isn't null
        {
            delete curr->data;
            curr->data = NULL; // pointer is null
        }

        delete curr;
        curr = NULL;
    }
}

BinTree &BinTree::operator=(const BinTree &tree) // set a tree to be equal to another tree
{
    if (*this == tree) // check if tree is equal using overloaded == operator
        return *this;

    this->makeEmpty(); // tree is empty now

    assignHelper(tree.root, this->root); // make both trees equal

    return *this;
}

void BinTree::assignHelper(Node *rightTree, Node *&leftTree)
{
    if (rightTree != NULL) // right tree node isn't null
    {

        leftTree = new Node; // set left tree node to new node
        NodeData *temp = new NodeData(*rightTree->data); // temp node holds data value of right tree node
        leftTree->data = temp; // leftTree node data is set to temp, which is the data of the right tree node

        assignHelper(rightTree->left, leftTree->left); // assign both left nodes of trees equal to each other
        assignHelper(rightTree->right, leftTree->right); // assign both left nodes of trees equal to each other
    }
    else
        leftTree = NULL; // left tree node is null since right tree node is null
}

bool BinTree::operator==(const BinTree &tree) const // checks if both trees are equal
{
    if (this->root == NULL && tree.root == NULL) // both tree roots are null
        return true;
    else
        return equalityCheckHelper(this->root, tree.root);
}

bool BinTree::equalityCheckHelper(Node *lNode, Node *rNode) const
{
    if (lNode == NULL && rNode == NULL) // if both nodes are null, trees are the same
        return true;

    if (lNode == NULL || rNode == NULL) // if only one node is null, one tree isn't equal to the other
        return false;

    if (*lNode->data == *rNode->data && lNode->left == NULL && rNode->left == NULL && lNode->right == NULL && rNode->right == NULL)
        return true;
// if both trees' node data is the same and the end of the both trees are reached, noth trees are the same
    return (*lNode->data == *rNode->data && equalityCheckHelper(lNode->left, rNode->left) && equalityCheckHelper(lNode->right, rNode->right));
    // keep checking both trees until leaf nodes are reached at end or if there's inequality reached
}

bool BinTree::operator!=(const BinTree &tree) const // checks if trees aren't equal by using overloaded == operator
{
    return !(*this == tree);
}

ostream &operator<<(ostream &o, const BinTree &tree) // print contents of tree using inorderTraversal
{
    tree.inorderTraversal(tree.root);
    o << endl;
    return o;
}

void BinTree::inorderTraversal(Node *curr) const // recursive function of inorder traversal
{
    if (curr != NULL)
    {
        inorderTraversal(curr->left);
        cout << *curr->data << " ";
        inorderTraversal(curr->right);
    }
}

bool BinTree::insert(NodeData *nodeInsert) // insert data into node
{
    return insertHelper(this->root, nodeInsert);
}

bool BinTree::insertHelper(Node *&curr, NodeData *nodeInsert)
{
    if (curr == NULL) 
    {
        curr = new Node; // make new node
        curr->data = nodeInsert; // node data is set to data in curr node
        curr->left = NULL;
        curr->right = NULL;
    }
    else if (*nodeInsert < *curr->data) // go left if nodeInsert is less than curr data
        insertHelper(curr->left, nodeInsert);
    else if (*nodeInsert > *curr->data)
        insertHelper(curr->right, nodeInsert);// go right if nodeInsert is greater than curr data
    else
        return false;

    return true;
}

int BinTree::getHeight(const NodeData &toFind) const 
{
    return getHeightHelper(toFind, this->root);
}

int BinTree::getHeightHelper(const NodeData &toFind, Node *curr) const
{
    if (curr == NULL) // height is 0 since node is null
        return 0;
    else if (*curr->data == toFind) // found node and call recursive function to find height of subtree
        return recursiveGetHeightHelper(curr);
    else
    {
        // go left and right to find root node of subtree
        int left = getHeightHelper(toFind, curr->left);
        int right = getHeightHelper(toFind, curr->right);

        return max(left, right); 
    }
}

int BinTree::recursiveGetHeightHelper(Node *curr) const
{
    if (curr == NULL)
        return 0;
    else

        return 1 + max(recursiveGetHeightHelper(curr->left), recursiveGetHeightHelper(curr->right));
        // find max height between left and right paths of subtree and adds one since we're counting from 0th level
}

void BinTree::bstreeToArray(NodeData *fillArray[]) // put nodes from tree into array
{
    bstreeToArrayHelper(this->root, fillArray);

    this->makeEmpty();
}

int BinTree::bstreeToArrayHelper(Node *curr, NodeData *fillArray[])
{
    if (curr == NULL) // node is null, tree is done
        return 0;

    int left = bstreeToArrayHelper(curr->left, fillArray); // go left

    NodeData *temp;
    temp = curr->data; // curr data is set to temp
    curr->data = NULL; // point node to null
    *(fillArray + left) = temp; // array points to temp
    temp = NULL;

    int right = bstreeToArrayHelper(curr->right, fillArray + left + 1); // go right

    return left + right + 1; // add 1 since we're counting from zero
}

void BinTree::arrayToBSTree(NodeData *array[]) // making balanced tree from array
{
    this->makeEmpty(); // delete tree

    int elements = 0;

    for (int i = 0; i < 100; i++) // max size of array is 100
    {
        if (array[i] != NULL)
            elements++; // how many elements in array point to NodeData
        else
            array[i] = NULL;
    }

    arrayToBSTreeHelper(root, array, 0, elements - 1);
}

void BinTree::arrayToBSTreeHelper(Node *curr, NodeData *array[], int low, int elements)
{
    if (low > elements)
        curr = NULL; // end of array 
    else
    {
        int mid = (low + elements) / 2; // mid point of array for balanced tree

        NodeData *temp; 
        temp = array[mid]; // assign mid to temp
        array[mid] = NULL; // element set to null

        insert(temp); // insert NodeData into tree
        arrayToBSTreeHelper(curr, array, low, mid - 1); // fill left side of tree
        arrayToBSTreeHelper(curr, array, mid + 1, elements); // fill right side of tree
    }
}

void BinTree::displaySideways() const
{
    sideways(root, 0);
}

void BinTree::sideways(Node *curr, int level) const
{
    if (curr != NULL)
    {
        level++;
        sideways(curr->right, level);

        for (int i = level; i >= 0; i--)
            cout << "    ";

        cout << *curr->data << endl;
        sideways(curr->left, level);
    }
}

bool BinTree::retrieve(const NodeData &nodeToRetrieve, NodeData *&retrievedNode)
{
    retrieveHelper(this->root, nodeToRetrieve, retrievedNode); // go thru tree to find NodeData

    if (retrievedNode != NULL)
        return true; // found NodeData

    return false; // Nodedata not in tree
}

bool BinTree::retrieveHelper(Node *&curr, const NodeData &nodeToRetrieve, NodeData *&retrievedNode) const
{
    if (curr == NULL) //NodeData isn't in tree
    {
        retrievedNode = NULL;
        return false;
    }

    if (*curr->data == nodeToRetrieve) // NodeData found
    {
        retrievedNode = curr->data;
        return true;
    }
    else if (*curr->data < nodeToRetrieve)
        retrieveHelper(curr->right, nodeToRetrieve, retrievedNode); // go right
    else if (*curr->data > nodeToRetrieve)
        retrieveHelper(curr->left, nodeToRetrieve, retrievedNode); // go left
    else
        return false; // NodeData not found
}
