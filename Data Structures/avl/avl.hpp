/*
 * avl.hpp
 *
 *  Created on: Jan 15, 2018
 *      Author: jonathan
 */

#ifndef AVL_HPP_
#define AVL_HPP_
#define TYPE int

#ifndef LT
#define LT(A,B) ((A) < (B))
#endif

#ifndef GT
#define GT(A,B) ((A) > (B))
#endif

#ifndef EQ
#define EQ(A,B) ((A)==(B))
#endif

struct Node{
	TYPE value;
	struct Node *left;
	struct Node *right;
	int height;
};
int height(struct Node *);
void setHeight(struct Node*);

int getBalance(struct Node*);

struct Node* newNode(TYPE);
struct Node* addNode(struct Node*, TYPE);

struct Node* rotateLeft(struct Node *);
struct Node* rotateRight(struct Node *);

struct Node* balance(struct Node*);

struct Node* removeLeftmost(struct Node*);
TYPE leftMost(struct Node*);

struct Node* getNode(struct Node*, TYPE);
struct Node* removeNode(struct Node*, TYPE);
void preOrder(struct Node *);
#endif /* AVL_HPP_ */
