/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
using namespace std;

template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1i
  if (!this->empty()){
    clear();
  }
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode * thru = head_;
  while(head_ != NULL){
    head_ = head_->next;
    delete thru;
    thru = head_;
  }
  tail_ = NULL;
  length_ = 0.0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  //length_ = length_ + 1;

  if (empty()){
    ListNode * curr = new ListNode(ndata);
    head_ = curr;
    tail_ = curr;
  }
  else{
    ListNode * curr = new ListNode(ndata);
    curr->next = head_;
    head_->prev = curr;
    head_ = curr;
  }

  length_ = length_ + 1;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

  if (this->empty()){
    ListNode * curr = new ListNode(ndata);
    head_ = curr;
    tail_ = curr;
  }
  else{
    ListNode * curr = new ListNode(ndata);
    curr->prev = tail_;
    tail_->next = curr;
    tail_ = curr;
  }

  length_ = length_ + 1;
}


// self-written function, debug purpose
/*
template <typename T>
void List<T>::printList(){
  cout << "head_ to tail_: " << endl;
  ListNode * thru = head_;
  while(thru != NULL){
    cout << thru->data << " "; 
    thru = thru->next;
  }
  cout << endl;

  
  cout << "tail_ to head_: " << endl;
  thru = tail_;
  while (thru != NULL){
    cout << thru->data << " ";
    thru = thru->prev;
  }
  cout << endl;
  
} */


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

// self written function, debug purpose
/*
template <typename T>
void List<T>::reverse(int a, int b){
  ListNode * start = head_;
  while(a>0){
    start = start->next;
    a--;
  }
  ListNode * end = head_;
  while(b>0){
    end = end->next;
    b--;
  }

  reverse(start, end);
}*/
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if ((startPoint != NULL) && (endPoint !=NULL ) && (startPoint != endPoint) ){

    ListNode * tmp01 = startPoint->prev;
    ListNode * tmp02 = endPoint->next;
    ListNode * thru = startPoint->next;
    ListNode * tmp = NULL;

    startPoint->prev = startPoint->next;
    startPoint->next = tmp02;
    endPoint->next = endPoint->prev;
    endPoint->prev = tmp01;

    if (tmp01 != NULL)
      tmp01->next = endPoint;
    if (tmp02 != NULL)
      tmp02->prev = startPoint;

    while (thru != endPoint){
      tmp = thru->next;
      thru->next = thru->prev;
      thru->prev = tmp;
      thru = thru->prev;
    }

    
    if ( (startPoint == head_) && (endPoint != tail_) )
      head_ = endPoint;

    if ( (endPoint == tail_) && (startPoint != head_) )
      tail_ = startPoint;

    
    tmp = startPoint;
    startPoint = endPoint;
    endPoint = tmp;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (n >= length_){
    reverse(head_, tail_);}
  else{
    int block = n;
    ListNode * start = head_;
    ListNode * end = head_;


    while(block <= length_){
            
      int i=0;
      while(i<(n-1)){
        end = end->next;
        i = i+1;
      }
      reverse(start, end);
      start = end->next;
      end = end->next;
      block = block + n;
    }

    if (end != NULL){
        end = tail_;
        reverse(start, end);
    }

  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
    ListNode * curr = head_;
    int mark = 0;

    while ( curr->next != NULL){
        if (mark % 2 == 1){
            ListNode * tmp01 = curr->prev;
            ListNode * tmp02 = curr->next;

            tmp01->next = tmp02;
            tmp02->prev = tmp01;
            curr->next = tail_->next;
            curr->prev = tail_;
            tail_->next = curr;
            tail_ = curr;
            curr = tmp02;
        }
        else{
            curr = curr->next;
        } 
        mark += 1;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
    int mark = 0;
    ListNode * curr = start;

    while(mark < splitPoint){
        curr = curr->next;
        mark += 1;
    }

    curr->prev->next = NULL;
    curr->prev = NULL;
    
    return curr;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
    ListNode * f = first;
    ListNode * s = second;

    if (first->data < second->data){
        f = f->next;
    }
    else{
        first = second;
        s = s->next;
    }

    ListNode * thru = first;
    while(f != NULL && s != NULL){
        if (f->data < s->data){
            thru->next = f;
            f->prev = thru;
            thru = f;
            f = f->next;
        }
        else{
            thru->next = s;
            s->prev = thru;
            thru = s;
            s = s->next;
        }
    }

    if (s == NULL){
        thru->next = f;
        f->prev = thru;
    }
    else{
        thru->next = s;
        s->prev = thru;
    }

    second = NULL;

    return first;

}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
    if (chainLength == 1)
        return start;

    int half_length = chainLength/2;

    ListNode * mid = split(start, half_length); 

    ListNode * m1 = mergesort(start, half_length);
    ListNode * m2 = mergesort(mid, chainLength - half_length);

    return merge(m1, m2);
}

