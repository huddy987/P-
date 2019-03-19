#include "tree.h"
#include "digraph.h"

using namespace std;

// Add the root node of the tree
void Tree::add_root(string contents) {
    Digraph::addVertex(0, contents); // Value is 0 since it is the root
}

// Add a new left node
void Tree::add_left(int parent, string contents) {
    // Left child of index i = 2i+1
    int child_val = (parent * 2) + 1;
    Digraph::addVertex(child_val, contents);
}

// Add a new right node
void Tree::add_right(int parent, string contents) {
    // Right child of index i = 2i+2
    int child_val = (parent * 2) + 2;
    Digraph::addVertex(child_val, contents);
}

// Return the id and contents of the left node
pair<int, string> Tree::get_left(int parent) const {
    int child_val = (parent * 2) + 1;
    string contents = getVertex(child_val);
    return pair<int, string>(child_val, contents);
}

// Return the id and contents of the right node
pair<int, string> Tree::get_right(int parent) const {
    int child_val = (parent * 2) + 2;
    string contents = getVertex(child_val);
    return pair<int, string>(child_val, contents);
}
