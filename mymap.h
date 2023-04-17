// Filename: mymap.h
// This header file will simulate a c++ map
// Included in tests.cpp
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// University of Illinois at Chicago
// CS 251: Spring 2022
// 2022/03/10

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename keyType, typename valueType>
class mymap {
private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    // Helper function for put and copy
    // This will initialize a new node with the given key and value
    // and return a pointer to it
    NODE* create_node(keyType key, valueType value) {
        // initialize all values
        NODE* newNode = new NODE;
        newNode->key = key;
        newNode->value = value;
        // default left and right will be nullptr
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->isThreaded = true;
        return newNode;
    }

    // Helper function for tostring
    // This will recursively traverse the tree
    // Stores the string into out and returns it
    // Using inorder traversal
    void _buildstring (NODE* node, ostream& out) {
        // if node is nullptr, return
        if (node == nullptr) {
            return;
        }
        _buildstring(node->left, out);
        out << "key: " << node->key;
        out << " value: " << node->value << endl;
        // if node is threaded, return
        node = (node->isThreaded) ? nullptr : node->right;
        _buildstring(node, out);
    }

    // Helper function for clear and destructor
    // This will recursively delete the tree
    void destroy(NODE* &current) {
        NODE* prev = nullptr;
        // if current is nullptr
        // that means all nodes have been deleted
        while (current != nullptr) {
            // if current is threaded
            // goto threaded node, delete previousely
            if (current->isThreaded) {
                prev = current;
                current = current->right;
                delete prev;
            } else {
                // if not, go right one
                // and go all the way left
                prev = current;
                current = current->right;
                delete prev;
                current = _bottom_left(current);
            }
        }
    }

    // Helper function for copy root
    // Thie function will create a new node
    // By creating a new node 
    // With given node key and value
    NODE* copy_node (NODE* node) {
        // if root is nullptr, return nullptr
        if (node == nullptr) {
            return nullptr;
        }
        // create a new node and return it
        NODE* newNode = create_node(node->key, node->value);
        return newNode;
    }

    // Helper function for thread traverse
    // This will traverse to the bottom left node
    // Return the node
    NODE* _bottom_left(NODE* node) {
        if (node->left == nullptr) {
            return node;
        }
        return _bottom_left(node->left);
    }

    // Helper function for copy and equal operator
    // This will recursively copy the tree
    // Using preorder traversal
    void _copy_Tree (NODE* current) {
        // if current is nullptr, return
        if (current == NULL) {
            return;
        } else {
            // Preorder traversal
            _copy_Tree(current->left);
            // Create a new node with current key and value
            put(current->key, current->value);
            // If current is threaded, return
            current = (current->isThreaded) ? nullptr : current->right;
            _copy_Tree(current);
        }
    }

    // Helper function for insert
    // Function will insert a new node to left/right
    void insert_node (NODE* prev, keyType key, valueType value) {
        // call helper function to create new node
        NODE* n = create_node(key, value);
        // if root is a nullptr, set root to n
        if (prev == nullptr) {
            root = n;
        } else if (key < prev->key) {
            // if key is less than prev key, set prev left to n
            n->right = prev;
            prev->left = n;
        } else {
            // if key is greater than prev key, set prev right to n
            // prev isthreaded update to false
            prev->isThreaded = false;
            // link n's right to prev's right
            n->right = prev->right;
            prev->right = n;
        }
    }

    // Helper function for check balance string
    // This will recursively traverse the tree
    // Stores the string into out and returns it
    // Use preorder traversal
    void _balance_string(NODE* current, ostream& out) {
        if (current == NULL) {
            return;
        }
        out << "key: " << current->key << ", nL: " << current->nL << ", nR: " << current->nR << endl;
        _balance_string(current->left, out);
        current = (current->isThreaded) ? nullptr : current->right;
        _balance_string(current, out);
    }

    // Helper function for tovector
    // This will recursively traverse the tree
    // Stores keys and values into vector and returns it
    // Using inorder traversal
    void _insert_vector(NODE* current, vector<pair<keyType, valueType>>& v)
    {
        if (current == NULL) {
            return;
        }
        _insert_vector(current->left, v);
        v.push_back(make_pair(current->key, current->value));
        current = (current->isThreaded) ? nullptr : current->right;
        _insert_vector(current, v);
    }

    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    struct iterator {
    private:
        NODE* curr;  // points to current in-order node for begin/end

    public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        // operator++:
        // This function should advance curr to the next in-order node.
        // O(logN)
        iterator operator++() {
            // if curr isThreaded, go right
            if (curr->isThreaded) {
                curr = curr->right;
            } else {
                // if not, go right one
                // and go all the way left
                curr = curr->right;
                while (curr->left != nullptr) {
                    curr = curr->left;
                }
            }
            return *this;
        }
    };

public:

    // default constructor:
    // Creates an empty mymap.
    // Time complexity: O(1)
    // Initializes size to 0, and root to nullptr.
    mymap() {
        root = nullptr;
        size = 0;
    }

    // copy constructor:
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    mymap(const mymap& other) {
        // create a new root
        root = copy_node(other.root);
        // if other root is empty return
        if (root == nullptr) {
            size = 0;
            return;
        } else {
            size = 1;
        }
        // call copy tree helper function
        _copy_Tree(other.root);
    }

    // operator=:
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    mymap& operator=(const mymap& other) {
        // create a new root
        root = copy_node(other.root);
        // if other root is empty return
        if (root == nullptr) {
            size = 0;
        } else {
            size = 1;
            // call copy tree helper function
            _copy_Tree(other.root);
        }
        return *this;
    }

    // clear:
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    void clear() {
        // if root is nullptr, return
        if (root == nullptr) {
            return;
        }
        NODE* current = root;
        // goto bottom left node
        current = _bottom_left(current);
        // call destroy helper function
        destroy(current);
        // set to default
        root = nullptr;
        size = 0;
    }

    // destructor:
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    ~mymap() {
        // if root is nullptr, return
        if (root == nullptr) {
            return;
        }
        NODE* current = root;
        // goto bottom left node
        current = _bottom_left(current);
        // call destroy helper function
        destroy(current);
    }

    // put:
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    void put(keyType key, valueType value) {
        // check if key is already in the tree
        bool isInTree = false;
        if (contains(key)) {
            isInTree = true;
        }
        // initialize variables
        NODE* prev = nullptr;
        NODE* current = root;
        while (current != nullptr) {
            // if key is already in the tree, update value
            if (key == current->key) {
                current->value = value;
                return;
            } else if (key < current->key) {
                // if key is less than current key, go left
                // save current node as prev
                prev = current;
                prev->nL = (isInTree) ? prev->nL : prev->nL + 1;
                current = current->left;
            } else {
                // if key is greater than current key, go right
                // save current node as prev
                prev = current;
                prev->nR = (isInTree) ? prev->nR : prev->nR + 1;
                // if current is threaded, return nullptr
                current = (current->isThreaded) ? nullptr : current->right;
            }
        }
        // call insert helper function
        insert_node(prev, key, value);
        size++;
    }

    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    bool contains(keyType key) {
        NODE* current = root;
        // if root is nullptr, return false
        if (current == nullptr) {
            return false;
        }
        // use inorder traversal to find key
        while (current != nullptr) {
            // if key is found, return true
            if (key == current->key) {
                return true;
            } else if (key < current->key) {
                current = current->left;
            } else {
                // if isThreaded, return nullptr
                // to break the loop
                current = (current->isThreaded) ? nullptr : current->right;
            }
        }
        // if not found return false
        return false;
    }

    // get:
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    valueType get(keyType key) {
        NODE* current = root;
        // use inorder traversal to find key
        while (current != nullptr) {
            // if key is found, return value
            if (key == current->key) {
                return current->value;
            } else if (key < current->key) {
                current = current->left;
            } else {
                // if isThreaded, return nullptr
                // to break the loop
                current = (current->isThreaded) ? nullptr : current->right;
            }
        }
        return valueType();
    }

    // operator[]:
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    valueType operator[](keyType key) {
        NODE* current = root;
        // if root is nullptr, insert one
        // with value of default valueType()
        if (current == nullptr) {
            put(key, valueType());
            return valueType();
        }
        // use inorder traversal to find key
        while (current != nullptr) {
            // if key is found, return value
            if (key == current->key) {
                return current->value;
            } else if (key < current->key) {
                current = current->left;
            } else {
                // if isThreaded, return nullptr
                // to break the loop
                current = (current->isThreaded) ? nullptr : current->right;
            }
        }
        // if not found, insert one and return default valueType()
        put(key, valueType());
        return valueType();
    }

    // Size:
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    int Size() {
        return size;
    }

    // begin:
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    iterator begin() {
        NODE* current = root;
        // call helper function to find bottom left node
        current = _bottom_left(current);
        return iterator(current);
    }

    // end:
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // Time Complexity: O(1)
    iterator end() {
        return iterator(nullptr);
    }

    // toString:
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    string toString() {
        stringstream ss;
        NODE* current = root;
        // call helper function to build string
        _buildstring(current, ss);
        // return string
        return ss.str();
    }

    // toVector:
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    vector<pair<keyType, valueType> > toVector() {
        vector<pair<keyType, valueType>> v;
        NODE* current = root;
        // call helper function to build vector
        _insert_vector(current, v);
        return v;
    }

    // checkBalance:
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    string checkBalance() {
        stringstream ss;
        NODE* current = root;
        // call helper function to build string
        _balance_string(current, ss);
        // return string
        return ss.str();
    }
};