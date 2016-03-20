//
//  rbTree.cpp
//  RedBlackTree
//
//  Created by Leon on 3/16/16.
//  Copyright © 2016 Leon. All rights reserved.
//

#ifndef rbTree_CPP
#define rbTree_CPP

#include <iostream>
#include <math.h>
#include "rbTree.hpp"

template <typename K, typename T>
void deleteNode(rbTreeNode<K, T> *node) {
    if (node == nullptr) return;
    
    rbTreeNode<K, T> *left = node->leftChild;
    rbTreeNode<K, T> *right = node->rightChild;
    delete node; // delete the node itself;
    
    if (left != nullptr) delete left; // recursively delete left child & right child
    if (right != nullptr) delete right;
}

template <typename K, typename T>
RBTree<K, T>::RBTree() {
    root = nullptr;
}

template<typename K, typename T>
RBTree<K, T>::RBTree(vector< pair<K, T> > sortArray) {
    root = this->treeWithSortedArray(sortArray, 0, int(sortArray.size()) - 1, 1);
}

template <typename K, typename T>
RBTree<K, T>::~RBTree() {
    deleteNode(this->root);
}

template <typename K, typename T>
void RBTree<K, T>::display() {
    this->display(this->root);
}

template <typename K, typename T>
void RBTree<K, T>::display(rbTreeNode<K, T> *node) {
    if (node == nullptr) return;
    
    cout << node->key << "[" << node->color << "]-";
    //if (node->parent != nullptr) cout << "p(" << node->parent->key << ")";
    if (node->leftChild != nullptr) cout << "l(" << node->leftChild->key << ")";
    if (node->rightChild != nullptr) cout << "r(" << node->rightChild->key << ")";
    cout << endl;
    
    this->display(node->leftChild);
    this->display(node->rightChild);
}

template <typename K, typename T>
rbTreeNode<K, T>* RBTree<K, T>::nodeKey(K key) {
    rbTreeNode<K, T> *node = this->root;
    while (node != nullptr) {
        if (key == node->key) break;
        else if (key < node->key) node = node->leftChild;
        else node = node->rightChild;
    }
    return node;
}

template <typename K, typename T>
T RBTree<K, T>::getValue(K key) {
    rbTreeNode<K, T> *node = this->root;
    while (node != nullptr) {
        if (key == node->key) return node->value;
        else if (key < node->key) node = node->leftChild;
        else node = node->rightChild;
    }
    return 0;
}

template <typename K, typename T>
K RBTree<K, T>::getPrevious(K key) {
    rbTreeNode<K, T> *node = this->root;
    K max = 0; // use the var max to store the max value along the path to key
    while (node != nullptr) {
        if (node->key < key) max = max > node->key ? max : node->key;
        if (key == node->key) break;
        else if (key < node->key) node = node->leftChild;
        else node = node->rightChild;
    }
    if (node == nullptr) return 0; // if didn't find the key, return 0
    node = node->leftChild;
    while (node != nullptr) {
        if (node->key < key) max = max > node->key ? max : node->key;
        node = node->rightChild;
    }
    return max; // if the result is the root node, return 0
}

template <typename K, typename T>
K RBTree<K, T>::getNext(K key) {
    rbTreeNode<K, T> *node = this->root;
    K min = 0;
    while (node != nullptr) {
        if (node->key > key && min == 0) min = node->key;
        else if (node->key  > key) min = min <  node->key ? min : node->key;
        if (key == node->key) break;
        else if (key < node->key) node = node->leftChild;
        else node = node->rightChild;
    }
    if (node == nullptr) return 0;
    node = node->rightChild;
    while (node != nullptr) {
        if (node->key > key && min == 0) min = node->key;
        else if (node->key > key) min = min < node->key ? min : node->key;
        node = node->leftChild;
    }
    return min;
}

template<typename K, typename T>
rbTreeNode<K, T>* RBTree<K, T>::minInTree(rbTreeNode<K, T> *node) {
    rbTreeNode<K, T> *min = node;
    while (min->leftChild != nullptr) {
        min = min->leftChild;
    }
    return min;
}

template <typename K, typename T>
void RBTree<K, T>::insert(K key, T value) {
    rbTreeNode<K, T> *parent = this->root; // store the parent pointer
    rbTreeNode<K, T> *pos = this->root; // store the current position of the searching pointer
    
    while (pos != nullptr) {
        parent = pos;
        if (key < pos->key) pos = pos->leftChild;
        else if (key == pos->key) return;
        else pos = pos->rightChild;
    }
    
    rbTreeNode<K, T> *node = new rbTreeNode<K, T>; // the newly inserted node
    node->key = key;
    node->value = value;
    
    if (parent == nullptr) { // the RBTress is empty now, the newly inserted node will be the root node
        this->root = node;
    }
    else {
        node->parent = parent; // insert the node to leftChild or rightChild
        if (node->key < parent->key)
            parent->leftChild = node;
        else
            parent->rightChild = node;
    }
    
    while (node != nullptr) {
        node = this->insertRemedy(node);
    }
}

template <typename K, typename T>
T RBTree<K, T>::increase(K key, T value) {
    rbTreeNode<K, T> *parent = this->root; // store the parent pointer
    rbTreeNode<K, T> *pos = this->root; // store the current position of the searching pointer
    
    while (pos != nullptr) {
        parent = pos;
        if (key < pos->key) pos = pos->leftChild;
        else if (key == pos->key) break;
        else pos = pos->rightChild;
    }
    
    if (pos != nullptr) {
        pos->value = pos->value + value;
        return pos->value;
    }
    
    rbTreeNode<K, T> *node = new rbTreeNode<K, T>; // the newly inserted node
    node->key = key;
    node->value = value;
    
    if (parent == nullptr) { // the RBTress is empty now, the newly inserted node will be the root node
        this->root = node;
    }
    else {
        node->parent = parent; // insert the node to leftChild or rightChild
        if (node->key < parent->key)
            parent->leftChild = node;
        else
            parent->rightChild = node;
    }
    
    while (node != nullptr) {
        node = this->insertRemedy(node);
    }
    return value;
}

template <typename K, typename T>
T RBTree<K, T>::reduce(K key, T value) {
    rbTreeNode<K, T> *node = this->nodeKey(key);
    
    if (node != nullptr) {
        node->value = node->value - value;
        node->value = node->value > 0 ? node->value : 0;
        
        if (node->value > 0) return node->value;
        else {
            // delete the node
            if (node->leftChild != nullptr && node->rightChild != nullptr) {
                // deleted node has two childs, find the min node in the right subtree, and delete that node
                rbTreeNode<K, T> *minNode = this->minInTree(node->rightChild);
                node->key = minNode->key;
                node->value = minNode->value;
                this->erase(minNode);
            }
            else {
                // delete node has no child or one child
                this->erase(node);
            }
            return 0;
        }
    }
    
    return 0;
}

template<typename K, typename T>
void RBTree<K, T>::erase(K key) {
    rbTreeNode<K, T> *deleteNode = this->root;
    
    while (deleteNode != nullptr) {
        if (deleteNode->key == key) break;
        else if (key < deleteNode->key) deleteNode = deleteNode->leftChild;
        else deleteNode = deleteNode->rightChild;
    }
    
    if (deleteNode == nullptr) return;
    
    if (deleteNode->leftChild != nullptr && deleteNode->rightChild != nullptr) {
        // deleted node has two childs, find the min node in the right subtree, and delete that node
        rbTreeNode<K, T> *minNode = this->minInTree(deleteNode->rightChild);
        deleteNode->key = minNode->key;
        deleteNode->value = minNode->value;
        this->erase(minNode);
    }
    else {
        // delete node has no child or one child
        this->erase(deleteNode);
    }
}

template<typename K, typename T>
void RBTree<K, T>::erase(rbTreeNode<K, T> *node) {
    if (node->leftChild != nullptr && node->rightChild != nullptr) {
        cout << "Warning: delete a node with two leafs." << endl;
        return;
    }
    
    if (node->leftChild == nullptr && node->rightChild == nullptr) {
        // delete node has no leafs, just delete it
        if (node->parent != nullptr) {
            // do not delete node, use this node remedy the tree first
            // if delete this node, can not use leaf to charge what condition should be choose
            if (node->color == BLACK) {
                rbTreeNode<K, T> *deficient = node;
                while (deficient != nullptr) deficient = this->eraseRemedy(deficient);
            }
            if (node->parent->leftChild == node) node->parent->leftChild = nullptr;
            else node->parent->rightChild = nullptr;
        }
        else {
            this->root = nullptr; // if this node is the root of the tree, the tree becomes empty
        }
        delete node;
        node = nullptr;
    }
    else {
        // delete node has one leaf
        rbTreeNode<K, T> *childNode = node->leftChild != nullptr ? node->leftChild : node->rightChild;
        if (node->parent != nullptr) {
            if (node->parent->leftChild == node) node->parent->leftChild = childNode;
            else node->parent->rightChild = childNode;
        }
        else {
            this->root = childNode;
        }
        childNode->parent = node->parent;
        if (node->color == BLACK) {
            rbTreeNode<K, T> *deficient = childNode;
            while (deficient != nullptr) deficient = this->eraseRemedy(deficient);
        }
        delete node;
        node = nullptr;
    }
}

template<typename K, typename T>
rbTreeNode<K, T>* RBTree<K, T>::eraseRemedy(rbTreeNode<K, T> *node) {
    if (node == nullptr) return nullptr;
    
    if (node->color == RED) { // if the root of the deficient subtree is red, just make it black
        node->color = BLACK;
        return nullptr;
    }
    
    if (node->parent == nullptr) { // if the root of the deficient subtree is the root of the whole tree, done
        return nullptr;
    }
    
    rbTreeNode<K, T> *y = node;
    rbTreeNode<K, T> *py = y->parent;
    rbTreeNode<K, T> *v; // v is the sibling of y
    rbTreeNode<K, T> *w; // w is the right child of v
    
    if (py->leftChild == y) {
        v = py->rightChild;
        int red_v_child = 0;
        if (v->leftChild != nullptr) red_v_child = v->leftChild->color == RED ? red_v_child + 1 : red_v_child;
        if (v->rightChild != nullptr) red_v_child = v->rightChild->color == RED ? red_v_child + 1 : red_v_child;
        
        if (v->color == BLACK && red_v_child == 0) {
            if (py->color == BLACK) {
                v->color = RED;
                return py;
            }
            else {
                v->color = RED;
                py->color = BLACK;
                return nullptr;
            }
        }
        else if (v->color == BLACK && red_v_child == 1) {
            if (v->rightChild != nullptr && v->rightChild->color == RED) {
                v->color = py->color;
                py->color = BLACK;
                v->rightChild->color = BLACK;
                this->leftRotate(py);
                return nullptr;
            }
            else if (v->leftChild != nullptr && v->leftChild->color == RED) {
                v->leftChild->color = py->color;
                py->color = BLACK;
                this->rightRotate(v);
                this->leftRotate(py);
                return nullptr;
            }
        }
        else if (v->color == BLACK && red_v_child == 2) {
            v->leftChild->color = py->color;
            py->color = BLACK;
            this->rightRotate(v);
            this->leftRotate(py);
            return nullptr;
        }
        else {
            // the v's color is red
            w = v->leftChild;
            int red_w_child = 0;
            if (w->leftChild != nullptr) red_w_child = w->leftChild->color == RED ? red_w_child + 1 : red_w_child;
            if (w->rightChild != nullptr) red_w_child = w->rightChild->color == RED ? red_w_child + 1 : red_w_child;
            if (red_w_child == 0) {
                v->color = BLACK;
                w->color = RED;
                this->leftRotate(py);
                return nullptr;
            }
            else if (red_w_child == 1 && w->rightChild->color == RED) {
                w->rightChild->color = BLACK;
                this->rightRotate(v);
                this->leftRotate(py);
                return nullptr;
            }
            else {
                w->leftChild->color = BLACK;
                this->rightRotate(w);
                this->rightRotate(v);
                this->leftRotate(py);
                return nullptr;
            }
        }
    }
    else {
        v = py->leftChild;
        int red_v_child = 0;
        if (v->leftChild != nullptr) red_v_child = v->leftChild->color == RED ? red_v_child + 1 : red_v_child;
        if (v->rightChild != nullptr) red_v_child = v->rightChild->color == RED ? red_v_child + 1 : red_v_child;
            
        if (v->color == BLACK && red_v_child == 0) {
            if (py->color == BLACK) {
                v->color = RED;
                return py;
            }
            else {
                v->color = RED;
                py->color = BLACK;
                return nullptr;
            }
        }
        else if (v->color == BLACK && red_v_child == 1) {
            if (v->leftChild != nullptr && v->leftChild->color == RED) {
                v->color = py->color;
                py->color = BLACK;
                v->leftChild->color = BLACK;
                this->rightRotate(py);
                return nullptr;
            }
            else if (v->rightChild != nullptr && v->rightChild->color == RED) {
                v->rightChild->color = py->color;
                py->color = BLACK;
                this->leftRotate(v);
                this->rightRotate(py);
                return nullptr;
            }
        }
        else if (v->color == BLACK && red_v_child == 2) {
            v->rightChild->color = py->color;
            py->color = BLACK;
            this->leftRotate(v);
            this->rightRotate(py);
            return nullptr;
        }
        else {
            // the v's color is red
            w = v->rightChild;
            int red_w_child = 0;
            if (w->leftChild != nullptr) red_w_child = w->leftChild->color == RED ? red_w_child + 1 : red_w_child;
            if (w->rightChild != nullptr) red_w_child = w->rightChild->color == RED ? red_w_child + 1 : red_w_child;
            if (red_w_child == 0) {
                v->color = BLACK;
                w->color = RED;
                this->rightRotate(py);
                return nullptr;
            }
            else if (red_w_child == 1 && w->leftChild->color == RED) {
                w->leftChild->color = BLACK;
                this->leftRotate(v);
                this->rightRotate(py);
                return nullptr;
            }
            else {
                w->rightChild->color = BLACK;
                this->leftRotate(w);
                this->leftRotate(v);
                this->rightRotate(py);
                return nullptr;
            }
         }
    }
    return nullptr;
}

template <typename K, typename T>
rbTreeNode<K, T>* RBTree<K,T>::treeWithSortedArray(vector<pair<K, T> > &sortArray, int begin, int end, int deep) {
    if (begin > end) return nullptr;
    int mid = ceil((begin + end) / 2);
    
    rbTreeNode<K, T> *node = new rbTreeNode<K, T>;
    node->key = sortArray[mid].first;
    node->value = sortArray[mid].second;
    
    rbTreeNode<K, T> *leftNode = this->treeWithSortedArray(sortArray, begin, mid - 1, deep + 1);
    if (leftNode != nullptr) leftNode->parent = node;
    
    rbTreeNode<K, T> *rightNode = this->treeWithSortedArray(sortArray, mid + 1, end, deep + 1);
    if (rightNode != nullptr) rightNode->parent = node;
    
    node->leftChild = leftNode;
    node->rightChild = rightNode;
    node->color = BLACK;
    
    if (deep > log2(sortArray.size() + 1)) node->color = RED;
    
    return node;
}

template <typename K, typename T>
rbTreeNode<K, T>* RBTree<K, T>::insertRemedy(rbTreeNode<K, T> *node) {
    if (node->parent == nullptr) { // node is the root
        node->color = BLACK;
        return nullptr;
    }
    if (node->parent->parent == nullptr && node->parent->color == RED && node->color == RED) {
        node->parent->color = BLACK;
        printf("Root should not be red.\n");
        return nullptr; // return nullptr means the remedy is done
    }
    
    rbTreeNode<K, T> *p, *pp, *gp;
    p = node;
    pp = node->parent;
    gp = node->parent->parent;
    
    if (p->color == BLACK || pp->color == BLACK) return nullptr; // return nullptr means the remedy is done
    
    bool isRed = false;
    // check whether p's uncle is red
    if (gp->leftChild == pp && gp->rightChild != nullptr) {
        if (gp->rightChild->color == RED) {
            isRed = true;
            gp->rightChild->color = BLACK;
        }
    }
    else if (gp->rightChild == pp && gp->leftChild != nullptr) {
        if (gp->leftChild->color == RED) {
            isRed = true;
            gp->leftChild->color = BLACK;
        }
    }
    
    // fix the condition that the uncle's color is red
    if (isRed == true) {
        gp->color = RED;
        pp->color = BLACK;
        return gp;
    }
    
    if (gp->leftChild == pp) {
        if (pp->leftChild == p) {
            // LLb condition
            pp->color = BLACK;
            gp->color = RED;
            return this->rightRotate(gp);
        }
        else {
            p->color = BLACK;
            gp->color = RED;
            this->leftRotate(pp);
            return this->rightRotate(gp);
        }
    }
    else {
        if (pp->leftChild == p) {
            p->color = BLACK;
            gp->color = RED;
            this->rightRotate(pp);
            return this->leftRotate(gp);
        }
        else {
            pp->color = BLACK;
            gp->color = RED;
            return this->leftRotate(gp);
        }
    }
}

template <typename K, typename T>
rbTreeNode<K, T>* RBTree<K, T>::leftRotate(rbTreeNode<K, T> *node) {
    if (node->rightChild == nullptr) return node; // check the validation of the node
    //if (node->rightChild->rightChild == nullptr) return node;
    
    rbTreeNode<K, T> *p, *pp, *gp;
    gp = node;
    pp = node->rightChild;
    p = node->rightChild->rightChild;
    
    if (gp->parent != nullptr) { // change from the parent node of our target node
        if (gp->parent->leftChild == gp) {
            gp->parent->leftChild = pp;
            pp->parent = gp->parent;
            gp->parent = nullptr;
        }
        else {
            gp->parent->rightChild = pp;
            pp->parent = gp->parent;
            gp->parent = nullptr;
        }
    }
    else {
        pp->parent = gp->parent;
    }
    
    // move the leftChild of pp to the rightChild of gp
    gp->rightChild = pp->leftChild;
    if (pp->leftChild != nullptr) pp->leftChild->parent = gp;
    pp->leftChild = gp;
    gp->parent = pp;
    
    if (this->root == gp) this->root = pp;
    
    return pp;
}

template <typename K, typename T>
rbTreeNode<K, T>* RBTree<K, T>::rightRotate(rbTreeNode<K, T> *node) {
    if (node->leftChild == nullptr) return node; // check the validation of the node
    //if (node->leftChild->leftChild == nullptr) return node;
    
    rbTreeNode<K, T> *p, *pp, *gp;
    gp = node;
    pp = node->leftChild;
    p = node->leftChild->leftChild;
    
    if (gp->parent != nullptr) { // change from the parent node of our target node
        if (gp->parent->leftChild == gp) {
            gp->parent->leftChild = pp;
            pp->parent = gp->parent;
            gp->parent = nullptr;
        }
        else {
            gp->parent->rightChild = pp;
            pp->parent =  gp->parent;
            gp->parent = nullptr;
        }
    }
    
    // move the rightChild of pp to the leftChild of gp
    gp->leftChild = pp->rightChild;
    if (pp->rightChild != nullptr) pp->rightChild->parent = gp;
    // move gp to the rightChild of pp
    pp->rightChild = gp;
    gp->parent = pp;
    
    if (this->root == gp) this->root = pp;
    
    return pp;
}

template <typename K, typename T>
void RBTree<K, T>::leftRotate(K key) {
    rbTreeNode<K, T> *node = this->nodeKey(key);
    if (node != nullptr) this->leftRotate(node);
}

template <typename K, typename T>
void RBTree<K, T>::rightRotate(K key) {
    rbTreeNode<K, T> *node = this->nodeKey(key);
    if (node != nullptr) this->rightRotate(node);
}

template <typename K, typename T>
bool RBTree<K, T>::verifyRBTree() {
    int a = 0;
    return this->verifyRBTree(this->root, a);
}

template <typename K, typename T>
bool RBTree<K, T>::verifyRBTree(rbTreeNode<K, T> *node, int &num) {
    if (node == nullptr) {
        num = 1;
        return true;
    }
    
    bool isSequence = false;
    if (node->parent != nullptr) isSequence = (node->parent->color == RED && node->color == RED);
        
    int leftNum = 0;
    int rightNum = 0;
    bool leftValid = this->verifyRBTree(node->leftChild, leftNum);
    bool rightValid = this->verifyRBTree(node->rightChild, rightNum);

    if (leftNum != rightNum) return false;
    if (node->color == BLACK) num = leftNum + 1;
    else num = leftNum;
    
    if (isSequence == true || !leftValid || !rightValid) return false;
    
    return true;
}

#endif




























