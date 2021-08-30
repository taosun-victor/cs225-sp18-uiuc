/* Your code here! */
#ifndef DSETS_H
#define DSETS_H 

#include <vector>
#include <iostream>

using namespace std;

class DisjointSets{
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        int getNumSets() const;

      
        void printParent();
        void printSize();
        void printElemSize();

    private:
        vector<int> size_;
        vector<int> parent_; 
        size_t num_elems = 0;
        int num_sets = 0;

};
#endif
