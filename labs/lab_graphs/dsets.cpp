/* Your code here! */
#include <vector>
#include <iostream>
#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num){
    for (int i=0; i<num; i++){
        parent_.push_back(num_ + i);
        size_.push_back(1);
    }
    num_ = num_ + num;
}

int DisjointSets::find(int elem){
    if (parent_[elem] == elem) return elem;
    else {
        parent_[elem] = find(parent_[elem]);
        return parent_[elem];
    }

}

void DisjointSets::setunion(int a, int b){
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b) return;

    if (size_[root_a] < size_[root_b]){
        parent_[root_a] = root_b;
        size_[root_b] = size_[root_a] + size_[root_b];
    }
    else{
        parent_[root_b] = root_a;
        size_[root_a] = size_[root_a] + size_[root_b];
    }   

}

int DisjointSets::size(int elem){
    int root_elem = find(elem);
    return size_[root_elem];
}


void DisjointSets::printParent(){
    for (unsigned i=0; i<parent_.size(); i++)
        cout << parent_[i] << "->";
    cout << endl;
}



void DisjointSets::printSize(){
    for (unsigned i=0; i<size_.size(); i++)
        cout << size_[i] << "->";
    cout << endl;
}



void DisjointSets::printElemSize(){
    for (unsigned i=0; i<parent_.size(); i++)
        cout << size(i) << "->";
    cout << endl;
}

