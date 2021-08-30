/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
    DisjointSets s;

    s.addelements(50);
    s.setunion(2, 3);
    cout << "union(2,3), find(2), find(3): " << s.find(2) << s.find(3) << endl;
    s.setunion(3, 5);
    cout << "union(3,5), find(2), find(3), find(5): " << s.find(2) << s.find(3) << s.find(5) << endl;
    s.setunion(5, 7);
    s.setunion(7, 2);
    s.setunion(4, 6);

    cout << s.find(7) << endl;
    cout << s.find(5) << endl;
    cout << s.find(6) << endl;

    s.addelements(1);

    cout << s.find(50) << endl;

    s.setunion(50, 3);

    cout << s.find(50) << endl;
    cout << "Disjoint Sets test complete" << endl;

    return 0;
}
