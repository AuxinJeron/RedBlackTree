//
//  rbTree.hpp
//  RedBlackTree
//
//  Created by Leon on 3/16/16.
//  Copyright © 2016 Leon. All rights reserved.
//

#ifndef rbTree_hpp
#define rbTree_hpp

#include <stdio.h>
#include <vector>
using namespace std;

enum rbtNodeColor { BLACK, RED };

template <typename K, typename T>
struct rbTreeNode {
    K key = 0;
    T value = 0;
    rbTreeNode<K, T> *leftChild = nullptr;
    rbTreeNode<K, T> *rightChild = nullptr;
    rbTreeNode<K, T> *parent = nullptr;
    rbtNodeColor color = RED;
};

template <typename K, typename T>
class RBTree {
    rbTreeNode<K, T> *root;
public:
    RBTree(); // constructor
    RBTree(vector< pair<K, T> > sortArray);
    ~RBTree(); // destructor
    
    void display();
    T getValue(K key);
    K getPrevious(K key);
    K getNext(K key);
    void insert(K key, T value);
    void erase(K key);
    T increase(K key, T value);
    T reduce(K key, T value);
    T inRange(K key1, K key2);
    
    // for test
    bool verifyRBTree();
    void leftRotate(K key);
    void rightRotate(K key);
    
private:
    void display(rbTreeNode<K, T> *node);
    rbTreeNode<K, T>* treeWithSortedArray(vector< pair<K, T> > &sortArray, int begin, int end, int deep);
    rbTreeNode<K, T>* insertRemedy(rbTreeNode<K, T> *node);;
    rbTreeNode<K, T>* leftRotate(rbTreeNode<K, T> *node);
    rbTreeNode<K, T>* rightRotate(rbTreeNode<K, T> *node);
    rbTreeNode<K, T>* nodeKey(K key);
    rbTreeNode<K, T>* minInTree(rbTreeNode<K, T> *node);
    void erase(rbTreeNode<K, T> *node);
    rbTreeNode<K, T>* eraseRemedy(rbTreeNode<K, T> *node);
    T inRange(rbTreeNode<K, T> *node, K key1, K key2);
    bool verifyRBTree(rbTreeNode<K, T> *node, int &num);
};

#include "rbTree.cpp"

#endif /* rbTree_hpp */
