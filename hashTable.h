#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "AVLTree.h"
#include "User.h"
#pragma once

class HashTable {
public:
  HashTable();    // default constructor
  HashTable(int); // one parameter constructor
  ~HashTable();   // destructor
  bool insert(const User &);
  bool remove(const User &);
  User *search(const User &) const;
  int size() const;    // return numOfItems
  int maxSize() const; // return arrSize

private:
  AVLTree *arr;
  int arrSize;
  int numOfItems;
  int hashFunc(const string &) const;
  int getPrime(int) const;
  bool isPrime(int) const;
};

#endif // HASHTABLE_H
