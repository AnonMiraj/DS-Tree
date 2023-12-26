#ifndef AVLTREE_H
#define AVLTREE_H
#include "User.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct AVLNode {
  User key;
  AVLNode *left;
  AVLNode *right;
  int height;
  AVLNode() {
    left = NULL;
    right = NULL;
    height = 1; // new node is initially
  };
};
class AVLTree {
private:
  AVLNode *root;

  int height(AVLNode *N) {
    if (N == NULL)
      return 0;
    return N->height;
  }
  int max(int a, int b) { return (a > b) ? a : b; }
  AVLNode *InPre(AVLNode *p) {
    while (p && p->right != NULL) {
      p = p->right;
    }
    return p;
  }
  AVLNode *InSucc(AVLNode *p) {
    while (p && p->left != NULL) {
      p = p->left;
    }
    return p;
  }

  // Get Balance factor of node N
  int getBalance(AVLNode *N) {
    if (N == NULL)
      return 0;
    return height(N->left) - height(N->right);
  }
  /* Helper function that allocates a
  new node with the given key and
  NULL left and right pointers. */
  AVLNode *newNode(User &key) {
    try {
      AVLNode *node = new AVLNode;
      node->key.MakeCopy(key);
      return node;
    } catch (const std::bad_alloc &e) {
      // Handle memory allocation failure
      std::cerr << "Memory allocation failed: " << e.what() << std::endl;
      return nullptr;
    }
  }
  // help function that update the root for each insertions

  // Recursive function to insert a key
  // in the subtree rooted with node and
  // returns the new root of the subtree.
  AVLNode *insertNode(AVLNode *node, User &NewUser) {
    /* 1. Perform the normal BST insertion */
    if (node == NULL) {
      cout << "not null first\n";
      return newNode(NewUser);
    } else if (NewUser.getHandel() < node->key.getHandel()) {
      node->left = insertNode(node->left, NewUser);
    } else if (NewUser.getHandel() > node->key.getHandel()) {
      node->right = insertNode(node->right, NewUser);
    } else { // Equal keys are not allowed in BST
      return node;
    }
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && NewUser.getHandel() < node->left->key.getHandel())
      return rightRotate(node);

    // Right Right Case
    if (balance < -1 && NewUser.getHandel() > node->right->key.getHandel())
      return leftRotate(node);

    // Left Right Case
    if (balance > 1 && NewUser.getHandel() > node->left->key.getHandel()) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && NewUser.getHandel() < node->right->key.getHandel()) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
  }

  // For Rotations
  AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
  }
  AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
  }

  // for searching
  AVLNode *search_(AVLNode *root, User key);
  AVLNode *search_(AVLNode *root, string key);

  AVLNode *remove_(AVLNode *p, string key);
  void printPreorder_(AVLNode *node) {
    if (node == NULL) {
      return;
    }

    // First print data of node
    cout << node->key.getHandel() << " ";

    // Then recur on left subtree
    printPreorder_(node->left);

    // Now recur on right subtree
    printPreorder_(node->right);
  }

public:
  // For displaying

  void printPreorder() { printPreorder_(this->root); }
  AVLTree() { root = NULL; }
  AVLNode *GetRoot() { return root; }
  AVLNode *search(const User &key) { return search_(root, key); }
  AVLNode *search(const string &key) { return search_(root, key); }

  AVLNode* insert(User &key) { return root=insertNode(root, key); }
  AVLNode *remove(const string key) { return remove_(root, key); }
};

#endif // AVLTREE_H
