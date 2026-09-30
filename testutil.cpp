#include <iostream>
#include <set>
#include "util.h"

using namespace std;

int main()
{
    set<string> words;

    words = parseStringToWords("Hello, World!");

    cout << "Men's Fitted Shirt:" << endl;

    for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl;

    words = parseStringToWords("J.");

    cout << "J.:" << endl;

    for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl;

    words = parseStringToWords("I'll");

    cout << "I'll:" << endl;

    for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}