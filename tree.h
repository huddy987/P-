#ifndef _TREE_H_
#define _TREE_H_

#include <utility> // For pair
#include "digraph.h"

using namespace std;

class Tree : public Digraph {
    public:
        // Add the root node of the tree
        void add_root(string contents);

        // Add a new left node
        void add_left(int parent, string contents);

        // Add a new right node
        void add_right(int parent, string contents);

        // Return the id and contents of the left node
        pair<int, string> get_left(int parent) const;

        // Return the id and contents of the right node
        pair<int, string> get_right(int parent) const;
};

#endif
