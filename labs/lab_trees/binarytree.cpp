/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <cmath>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot){
    if (subRoot == NULL)
        return;

    Node * tmp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = tmp;
    mirror(subRoot->left);
    mirror(subRoot->right);

}
/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here

    InorderTraversal<int> iot(root);
    T record = (iot.pop())->elem;

    for (TreeTraversal<int>::Iterator it=iot.begin(); it != iot.end(); ++it){
        if((*it)->elem < record )
            return false;
        else
            record = (*it)->elem;
        }

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedR(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedR(typename BinaryTree<T>::Node * subRoot) const {
    if (subRoot->left == NULL && subRoot->right == NULL)
        return true;
    else if (subRoot->left == NULL && subRoot->right != NULL)
        return (isOrderedR(subRoot->right) && (subRoot->elem < minTree(subRoot->right)));
    else if (subRoot->left != NULL && subRoot->right == NULL)
        return (isOrderedR(subRoot->left) && (subRoot->elem > maxTree(subRoot->left)));
    else// (subRoot->left != NULL && subRoot->right != NULL)
        return (isOrderedR(subRoot->left) && isOrderedR(subRoot->left) && (subRoot->elem > maxTree(subRoot->left)) && (subRoot->elem < minTree(subRoot->right)) );

}


template <typename T>
T BinaryTree<T>::minTree(typename BinaryTree<T>::Node * subRoot) const {
/*
    if (subRoot == NULL)
        return 0;

    T m = subRoot->elem;
    m = min(m, minTree(subRoot->left));
    return min(m, minTree(subRoot->right));
*/

    if (subRoot->left == NULL && subRoot->right == NULL)
        return subRoot->elem;
    else if (subRoot->left == NULL && subRoot->right != NULL)
        return min(subRoot->elem, minTree(subRoot->right));
    else if (subRoot->left != NULL && subRoot->right == NULL)
        return min(subRoot->elem, minTree(subRoot->left));
    else //(subRoot->left != NULL && subRoot->right != NULL)
        return min(subRoot->elem, min(minTree(subRoot->left), minTree(subRoot->right)) );

}

template <typename T>
T BinaryTree<T>::maxTree(typename BinaryTree<T>::Node * subRoot) const {
/* 
    if (subRoot == NULL)
        return 0;

    T m = subRoot->elem;
    m = max(m, maxTree(subRoot->left));
    return max(m, maxTree(subRoot->right));  
*/

    if (subRoot->left == NULL && subRoot->right == NULL)
        return subRoot->elem;
    else if (subRoot->left == NULL && subRoot->right != NULL)
        return max(subRoot->elem, maxTree(subRoot->right));
    else if (subRoot->left != NULL && subRoot->right == NULL)
        return max(subRoot->elem, maxTree(subRoot->left));
    else //(subRoot->left != NULL && subRoot->right != NULL)
        return max(subRoot->elem, max(maxTree(subRoot->left), maxTree(subRoot->right)) );

}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    T path[3000];
    printPathsRecur(root, paths, path, 0);
}

template <typename T>
void BinaryTree<T>::printPathsRecur(typename BinaryTree<T>::Node * subRoot, vector<vector<T>> &paths, T path[], int pathLen) const {

    if (subRoot == NULL)
        return;

    path[pathLen] = subRoot->elem;
    pathLen += 1;
    
    if (subRoot->left == NULL && subRoot->right == NULL){
        storePath(paths, path, pathLen);
    }
    else{
        printPathsRecur(subRoot->left, paths, path, pathLen);
        printPathsRecur(subRoot->right, paths, path, pathLen);
    }
}

template <typename T>
void BinaryTree<T>::storePath(vector<vector<T>> &paths, T path[], int pathLen) const {
    vector<T> tmp;

    for (int i=0; i<pathLen; i++)
        tmp.push_back(path[i]);

    paths.push_back(tmp);
}



/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistances(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistances(typename BinaryTree<T>::Node * subRoot, int pathLen) const {
    
    if (subRoot == NULL)
        return 0;

    //pathLen += 1;
    return(pathLen + sumDistances(subRoot->left, pathLen+1) + sumDistances(subRoot->right, pathLen+1)); 
}



