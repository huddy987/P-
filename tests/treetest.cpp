#include "../tree.h"
#include <iostream>


using namespace std;


int main() {
    Tree testtree;

    testtree.add_root("first");

    testtree.add_left(0, "second");

    testtree.add_right(0, "third");

    pair<int, string> test1 = testtree.get_left(0);

    testtree.add_right(test1.first, "fourth");

    pair<int, string> test2 = testtree.get_right(0);

    testtree.add_left(test2.first, "fifth");

    pair<int, string> test3 = testtree.get_right(test1.first);

    pair<int, string> test4 = testtree.get_left(test2.first);

    // Inherits all
    cout << testtree.isVertex(0) << endl;

    cout << testtree.isVertex(20) << endl;

    cout << "The left child of the root has a value of: " << test1.first << " and it's contents are: " << test1.second << endl;

    cout << "The right child of the root has a value of: " << test2.first << " and it's contents are: " << test2.second << endl;

    cout << "The right child of the left node has a value of: " << test3.first << " and it's contents are: " << test3.second << endl;

    cout << "The left node of the right child has a value of: " << test4.first << " and it's contents are: " << test4.second << endl;

    return 0;
}
