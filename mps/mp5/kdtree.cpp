/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim> &first, const Point<Dim> &second) const {
    double dist = 0.0;
    
    for (int i=0; i<Dim; i++){
        dist += (first[i] - second[i]) * (first[i] - second[i]);
    }
    return dist;
}

template <int Dim>
double KDTree<Dim>::dist_plane(const Point<Dim> &first, const Point<Dim> &second, int level) const {
    int dim = level % Dim;
    return (first[dim]-second[dim]) * (first[dim]-second[dim]); 
}

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim)
        return false;

    else if (first[curDim] < second[curDim]){
        return true;
    }
    else if (first[curDim] > second[curDim]){
        return false;
    }
    else{
        return first < second? true : false;
    }

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double dist_curr = distance(currentBest, target);
    double dist_potl = distance(potential, target);

    if (dist_potl > dist_curr)
        return false;
    else if (dist_potl < dist_curr)
        return true;
    else
        return potential < currentBest? true : false;
}


// helper function for partition, with the right-most 
// element as the pivot. All elements smaller than the 
// pivot will be on the lhs of the pivot. All elements
// larger than the pivot will be on the rhs of the pivot.
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & Points, int dim, int left, int right){

    Point<Dim> pivot = Points[right];
    int i = left;

    for (int j=left; j<=(right-1); j++){
        if (smallerDimVal(Points[j], pivot, dim)){
            std::swap(Points[i], Points[j]);
            i++;
        }
    }

    std::swap(Points[i], Points[right]);
    return i;
}


// helper function for rearrange the vector, find the kth smallest
// element, and return. Eg. all elements smaller
// than the k-th smallest element are on its lhs,
// same as those larger. Note: kth--> 1st, 2nd, 3rd ...
template <int Dim>
Point<Dim> KDTree<Dim>::kthSmallest(vector<Point<Dim>> & Points, int dim, int left, int right, int k){

    if (k>0 && k<= right-left +1){

        int index = partition(Points, dim, left, right);

        if (index-left == k-1)
            return Points[index];

        if (index-left > k-1)
            return kthSmallest(Points, dim, left, index-1, k);

        return kthSmallest(Points, dim, index+1, right, k-index+left-1);

    }
    
    cout << "error: k is too small or too large." << endl;
    double array[Dim];
    std::fill_n(array, Dim, -5);
    Point<Dim> tmp(array);
    return tmp;
}


//helper function to build up a tree, recursively returning a node
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::vectorToBST(vector<Point<Dim>>& Points, int level, int left, int right){

    if (left > right)
        return NULL;
   
    int dim = level % Dim;
    // Note: call kth-smallest, k is 1st, 2nd, 3rd ... 
    int mid = floor((left + right)/2.0) + 1; 

    Point<Dim> mid_point = kthSmallest(Points, dim, left, right, mid - left);
 
    struct KDTreeNode * root = new KDTreeNode(mid_point);

    root->left = vectorToBST(Points, level+1, left, mid-2);
    root->right = vectorToBST(Points, level+1, mid, right);

    return root;
} 


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
   vector<Point<Dim>> Points_copy = newPoints; 
   size = Points_copy.size();
   root = vectorToBST(Points_copy, 0, 0, size-1);
  
}

template <int Dim>
void KDTree<Dim>::destroy(typename KDTree<Dim>::KDTreeNode * subRoot){
    if (subRoot == NULL)
        return;
    destroy(subRoot->left);
    destroy(subRoot->right);
    delete subRoot;
    subRoot = NULL;
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(const typename KDTree<Dim>::KDTreeNode * subRoot){
    if (subRoot == NULL)
        return NULL;

    struct KDTreeNode * new_subRoot = new KDTreeNode(subRoot->point);
    new_subRoot->left = copy(subRoot->left);
    new_subRoot->right = copy(subRoot->right); 
 
    return subRoot;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
    root = copy(other->root);
    size = other.size;
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
    if (this != &rhs){
        destroy(root);
        root = copy(rhs->root);
        size = rhs.size;
    }

    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    destroy(root);
    size = 0;
}


// helper function to do top-down search. Not an efficient implementation.
// Will do unnecessary searches. Could not pass all test cases
template <int Dim>
Point<Dim> KDTree<Dim>::search_subtree_topdown(const typename KDTree<Dim>::KDTreeNode * subRoot, Point<Dim> query, Point<Dim> curr_best, double dist_min, int level) const {
    if (subRoot == NULL)
        return curr_best;

    bool check = shouldReplace(query, curr_best, subRoot->point);
    double d = distance(subRoot->point, query);

    if (check == true){
        dist_min = d;
        curr_best = subRoot->point; 
    }

    double dist = dist_plane(subRoot->point, query, level);
    int dim = level % Dim;

    if (dist >= dist_min){
        if (query[dim] <= subRoot->point[dim]){
            curr_best = search_subtree_topdown(subRoot->left, query, curr_best, dist_min, level+1);
        }
        else{
            curr_best = search_subtree_topdown(subRoot->right, query, curr_best, dist_min, level+1);
        }
    }
    else{
        Point<Dim> curr_best1 = search_subtree_topdown(subRoot->left, query, curr_best, dist_min, level+1);
        Point<Dim> curr_best2 = search_subtree_topdown(subRoot->right, query, curr_best, dist_min, level+1);

        double d1 = distance(curr_best1, query);
        double d2 = distance(curr_best2, query);
        curr_best = d1 <= d2? curr_best1 : curr_best2;
    }

    return curr_best;
}

//helper function search for parents. reference to dongxin2
template <int Dim>
Point<Dim> KDTree<Dim>::search_subtree_parent(const KDTreeNode* subRoot, const Point<Dim> query, int level, Point<Dim>& curr_best) const{

    bool go_left = false;
    if (subRoot->left == NULL && subRoot->right == NULL) 
        return subRoot->point;

    if (smallerDimVal(query, subRoot->point, level%Dim)){
        if (subRoot->left != NULL){
            go_left = true;
            curr_best = search_subtree_parent(subRoot->left, query, level+1, curr_best);
        }
        else
            curr_best = search_subtree_parent(subRoot->right, query, level+1, curr_best); 
    }
    else{
        if (subRoot->right != NULL)
            curr_best = search_subtree_parent(subRoot->right, query, level+1, curr_best);
        else{
            go_left = true;
            curr_best = search_subtree_parent(subRoot->left, query, level+1, curr_best); 
        }
    }

    //parent
    Point<Dim> curr_best2 = curr_best;
    if (shouldReplace(query, curr_best, subRoot->point)){
        curr_best = subRoot->point;
    }

    if (dist_plane(query, subRoot->point, level%Dim) <= distance(query, curr_best)){
        if(go_left){
            if (subRoot->right != nullptr)
               curr_best2 = search_subtree_parent(subRoot->right, query, level+1, curr_best2);
        }
        else{
            if (subRoot->left != nullptr)
            curr_best2 = search_subtree_parent(subRoot->left, query, level+1, curr_best2);
      }
    }
    
    //which is better
    if (shouldReplace(query, curr_best, curr_best2))
        curr_best = curr_best2;
    return curr_best;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    Point<Dim> tmp = root->point;
    //Point<Dim> nearest = search_subtree_topdown(root, query, tmp, 1000.0, 0);
    Point<Dim> nearest = search_subtree_parent(root, query, 0, tmp);

    return nearest;
}

