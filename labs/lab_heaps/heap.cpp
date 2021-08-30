#include <math.h>
#include <iostream>
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    size_t left_index = leftChild(currentIdx);
    //size_t right_index = rightChild(currentIdx);
    if (left_index > (_elems.size()-1))
        return false;
    else
        return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left_child = leftChild(currentIdx);
    size_t right_child = rightChild(currentIdx);
    if (right_child <= (_elems.size()-1)){
        if (higherPriority(_elems[left_child], _elems[right_child]))
            return left_child;
        else
            return right_child;
    }
    else if (left_child <= (_elems.size()-1))
        return left_child;
    else
        return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx) == false) 
        return;
    size_t priorityChild_index = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[priorityChild_index], _elems[currentIdx])){
        std::swap(_elems[priorityChild_index], _elems[currentIdx]);
        heapifyDown(priorityChild_index);
    } 
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for (size_t i=0; i<elems.size(); i++)
        _elems.push_back(elems[i]);

    for (size_t i=parent(_elems.size()); i>0; i--)
        heapifyDown(i);


}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T highestPriority = _elems[1];
    _elems[1] = _elems[_elems.size()-1];
    _elems.pop_back();
    heapifyDown(1);

    return highestPriority;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);

}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return !(_elems.size()>1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
