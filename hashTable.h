#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef>
#include <iostream>

template <typename KeyType, typename ValueType>
class HashTable {
private:
    // Define the structure for a node in the hash table
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
    };

    size_t size;
    Node** table;

    // Private member functions
    Node* createNode(KeyType key, ValueType value);
    size_t hash(KeyType key);

public:
    // Constructor
    HashTable(size_t size);

    // Destructor
    ~HashTable();

    // Member functions
    void insert(KeyType key, ValueType value);
    bool get(KeyType key, ValueType& value);
    void removeEntry(KeyType key);
};

// Implementation of member functions
template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t size) : size(size) {
    table = new Node*[size]();
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    for (size_t i = 0; i < size; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Node*
HashTable<KeyType, ValueType>::createNode(KeyType key, ValueType value) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}

template <typename KeyType, typename ValueType>
size_t HashTable<KeyType, ValueType>::hash(KeyType key) {
    return std::hash<KeyType>{}(key) % size;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType key, ValueType value) {
    size_t index = hash(key);
    Node* newNode = createNode(key, value);
    if (newNode == nullptr) {
        std::cerr << "Failed to insert key-value pair. Memory allocation error." << std::endl;
        exit(EXIT_FAILURE);
    }

    newNode->next = table[index];
    table[index] = newNode;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::get(KeyType key, ValueType& value) {
    size_t index = hash(key);
    Node* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            value = current->value;
            return true;  // Success
        }
        current = current->next;
    }

    return false;  // Key not found
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::removeEntry(KeyType key) {
    size_t index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                // Remove the first node
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

#endif  // HASHTABLE_H
