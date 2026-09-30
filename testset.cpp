#include <iostream>
#include <set>
#include "util.h"

using namespace std;

int main()
{
    set<int> s1;
    set<int> s2;

    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);

    s2.insert(3);
    s2.insert(4);
    s2.insert(5);
    s2.insert(6);

    set<int> intersection = setIntersection(s1, s2);
    set<int> uni = setUnion(s1, s2);

    cout << "Intersection:" << endl;

    for (set<int>::iterator it = intersection.begin();
         it != intersection.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;

    cout << "Union:" << endl;

    for (set<int>::iterator it = uni.begin();
         it != uni.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;

    return 0;
}