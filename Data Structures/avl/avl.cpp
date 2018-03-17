/*
 * avl.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: jonathan
 */
#include "avl.hpp"
#include <iostream>
using std::cout;
// Determines the height of a child node
int height(struct Node *current){
	// Leaf nodes have a height of zero, so zero is returned for a null value
	if(EQ(current, NULL))
		return 0;
	return current->height;
}

// Sets the height value of a node, assuming that the height of the child nodes is known
void setHeight(struct Node* current){
	int lch = height(current->left),
		rch = height(current->right);
	if(GT(lch, rch))
		current->height = lch + 1;
	else
		current->height = rch + 1;
}
// Returns the difference in height between the left and right child trees
int getBalance(struct Node* current){
	return height(current->left) - height(current->right);
}
// Allocates a new node with the given value and sets left and right child nodes pointers to NULL
struct Node* newNode(TYPE value){
	struct Node* node = new Node;
	node->value = value;
	node->left = node->right = NULL;
	node->height = 1; // new node is initially added at leaf
	return node;
}
// Recursive function to insert a new value into the subtree at the pointer to current
// Returns new root of subtree
struct Node* addNode(struct Node* current, TYPE value){
	// Default case - perform normal insertion
	if(EQ(current, NULL))
		return newNode(value);
	if(LT(value, current->value))
		current->left = addNode(current->left, value);
	else if(GT(value, current->value))
		current->right = addNode(current->right, value);
	else // Equal keys are not allowed
		return current;
	return balance(current);
}
/*
  z                                y
 /  \                            /   \
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
 */
// Performs a left rotation on a subtree rooted with current
struct Node* rotateLeft(struct Node * x){
	struct Node *y = x->right;
	struct Node *T2 = y->left;
	// Perform rotation
	y->left = x;
	x->right = T2;
	//  Update heights
	setHeight(x);
	setHeight(y);
	// Return new root
	return y;
}
/*
         z                                      y
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

 */
// Performs a right rotation on a subtree rooted with current
struct Node* rotateRight(struct Node * y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
	setHeight(y);
	setHeight(x);
    // Return new root
    return x;
}
// Performs the rotations necessary to restore the balance in the tree
// if one subtree is more than 1 levels different in height from the other,
// than a rebalancing is performed.
struct Node* balance(struct Node* current){
	// Get the balance factor of this current node to see if
	// this node is unbalanced
    int balance = getBalance(current);

	// Update height of this current node
	setHeight(current);

    // Left Left Case
    if (GT(balance, 1)){
    	// Left Right Case
    	if(LT(getBalance(current->left), 0))
    		current->left =  rotateLeft(current->left);
        return rotateRight(current);
    }
    // Right Right Case
    if (LT(balance, -1)){
    	// Right Left Case
        if(GT(getBalance(current->right), 0))
        	current->right = rotateRight(current->right);
    	return rotateLeft(current);
    }
    /* return the (unchanged) node pointer */
    return current;
}
struct Node* removeLeftmost(struct Node* current){
	struct Node* temp;
	if(!EQ(current->left, 0)){ // our node has a left child
		current->left = removeLeftmost(current->left);
		return balance(current);
	} // Our node does not have a left child, therefore we are at the leftmost child
	temp = current->right; // save the right child
	delete current; // delete the leftmost node
	return temp; // returns the right child of the leftmost node
}
TYPE leftMost(struct Node* node){
    struct Node* current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current->value;
}
struct Node* getNode(struct Node* current, TYPE search){
	while(current != NULL){
		// Match found?
		if(EQ(current->value, search))
			return current;
		// Is our search value less than the value at the current node?
		else if(LT(search, current->value))
			current = current->left; // Move to left child
		else // search value is greater than the value at the current node
			current = current->right; // Move to right child
	}
	return NULL;
}
struct Node* removeNode(struct Node* current, TYPE value){
	struct Node *temp;
	if(EQ(value, current->value)){ // we have found the node to remove
		if(!EQ(current->right, 0)){ // node to remove has a right child
			current->value = leftMost(current->right); // shift leftmost value up to current node
			current->right = removeLeftmost(current->right); // remove the leftmost node with the value we took from
			return balance(current);
		}
		else{ // node to remove does not have a right child
			temp = current->left; // save the left child
			delete current; // remove the node
			return temp; // return the left child of the node just removed
		}
	}
	else if(LT(value, current->value))
		current->left = removeNode(current->left, value);
	else
		current->right = removeNode(current->right, value);
	return balance(current);
}
void preOrder(struct Node *root){
    if(!EQ(root, NULL)){
    	cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main(){
  struct Node *root = NULL;

  /* Constructing tree given in the above figure */
  root = addNode(root, 10);
  cout << "Adding 2nd node\n\n";
  root = addNode(root, 20);
  cout << "Adding 3rd node\n\n";
  root = addNode(root, 30);
  cout << "Adding 4th node\n\n";
  root = addNode(root, 40);
  cout << "Adding 5th node\n\n";
  root = addNode(root, 50);
  cout << "Adding 6th node\n\n";
  root = addNode(root, 25);
  //cout << "done adding nodes..\n";
  /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */
  cout << "Preorder traversal of the constructed AVL tree is \n";
  //cout << "Root value is: " << root->value << "\n";
  preOrder(root);
  cout << "\nSearching for Node: " << getNode(root, 40)->value << "\n";
  removeNode(root, 30);
  preOrder(root);
  return 0;
}




