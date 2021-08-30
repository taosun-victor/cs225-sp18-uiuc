/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
using namespace std;

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{ // Your code here
  if (s.empty()){
    return 0;
  }
  else{
    T tmp = s.top();
    s.pop();
    T total = tmp + sum(s);
    s.push(tmp);
    return total;  
  }
                // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets. 
 * A string will consist of 
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * You are allowed only the use of one stack in this function, and no other local variables.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    //
    //

    stack<char> check;
    while (!input.empty()){
        char tmp = input.front();
        if (tmp == '['){
            check.push(tmp);
        }
        else if (tmp == ']'){
            if (check.empty()){
                return false;
                break; }
            else {
                if (check.top() != '['){
                    return false;
                    break;}
                else
                    check.pop();
            } 
        }
        input.pop();
    }
   
    if (check.empty())
        return true;
    else
        return false;

}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> t;
    int block_size = 1;
    T tmp;

    while(block_size < int(q.size())  ){
        if (block_size % 2 == 1){
            for (int i=0; i<block_size; i++){
                tmp = q.front();
                q.pop();
                t.push(tmp);
            }
        }
        else{
            for (int i=0; i<block_size; i++){
                tmp = q.front();
                q.pop();
                s.push(tmp);
            }
            while(!s.empty()){
                tmp = s.top();
                s.pop();
                t.push(tmp);
            }
        }
        block_size += 1;
    }

    while(!q.empty()){
        if (block_size % 2 == 1){
            tmp = q.front();
            q.pop();
            s.push(tmp);
        }
        else{
            tmp = q.front();
            q.pop();
            s.push(tmp);
        }
    }

    while(!s.empty()){
        tmp = s.top();
        s.pop();
        t.push(tmp);
    }

    q = t; 

    // optional: queue<T> q2;

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */

template <typename T>
bool verifySame(stack<T> & s, queue<T> & q)
{
    bool retval = true; 
    T tmp;

    if(s.empty()){
        return true;}
    else{
        tmp = s.top();
        s.pop();

        retval = (verifySame(s, q) && (tmp == q.front()));

        // recover
        q.push(q.front());
        q.pop();
        s.push(tmp);
    }

    return retval;
}


}


