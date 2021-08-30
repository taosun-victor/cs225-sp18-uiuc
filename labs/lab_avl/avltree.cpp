/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * x = t->right;
    t->right = x->left;
    x->left = t;
    
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    x->height = 1 + max(heightOrNeg1(x->left), heightOrNeg1(x->right));

    t = x;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * x = t->left;

    t->left = x->right;
    x->right = t;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    x->height = 1 + max(heightOrNeg1(x->left), heightOrNeg1(x->right));

    t = x;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::getBalance(Node *& subtree) const {
    if (subtree == NULL)
        return 0;
    else
        return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL)
        return;
     
    subtree->height = 1 + max(heightOrNeg1(subtree->left), 
                              heightOrNeg1(subtree->right));

    int self_balance = getBalance(subtree);
    int left_balance = getBalance(subtree->left);
    int right_balance = getBalance(subtree->right);

    if (self_balance == -2  && left_balance == -1)
        rotateRight(subtree);

    if (self_balance == -2 && left_balance == 1)
        rotateLeftRight(subtree);
    
    if (self_balance == 2 && right_balance == 1)
        rotateLeft(subtree);
    
    if (self_balance == 2 && right_balance == -1)
        rotateRightLeft(subtree);
    
    return; 
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL){
        subtree = new Node(key, value);
    }    
    else if (key < subtree->key){
        insert(subtree->left, key, value);
        int balance = getBalance(subtree); 
        int leftBalance = getBalance(subtree->left); 
        if (balance == -2){
            if (leftBalance == -1)
                rotateRight(subtree);
            else
                rotateLeftRight(subtree);
        }
    }
    else if (key > subtree->key){
        insert(subtree->right, key, value);
        int balance = getBalance(subtree); 
        int rightBalance = getBalance(subtree->right); 
        if (balance == 2){
            if (rightBalance == -1)
                rotateRightLeft(subtree);
            else
                rotateLeft(subtree);
        }
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left), 
                              heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } 
    else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } 
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } 
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * tmp = subtree->left;
            while ( tmp->right != NULL )
               tmp = tmp->right;
            swap(subtree, tmp);
            remove(subtree->left, key);
        } 
        else {
            /* one-child remove */
            // your code here
            Node * tmp = subtree->left? subtree->left : subtree->right;
            *subtree = *tmp;
            delete tmp;
            tmp = NULL;
        }
    }

    // your code here
    rebalance(subtree);

}
