// This file should have been deleted. Don't read it please (secret).

// Header files: A lot of them so we never fail to compile.
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <string>
#include "digraph.h"

using namespace std;

int main() {
Digraph g;
g.addVertex(5,"Hello");
g.addVertex(6,"No");
g.addVertex(7,"Yes");
g.addEdge(5,6);
g.addEdge(5,7);
cout << "Does the edge from 6 to 7 exist?" << " " << g.isEdge(6,7) << endl;
cout << "5 is a vertex?:" << " " << g.isVertex(5) << endl;
cout << "The contents of 5 are:" << " " << g.getVertex(5) << endl;
cout << "The number of neighbours of vertex 5 are:" << " " << g.numNeighbours(5) << endl;
g.addVertex(3,"asd");
cout << Error in Digraph Object Method << endl;
int test1 = 5;
int test2 = 6;
cout << "test1 contains the number:" << " " << test1 << " " << "and test2 contains the number" << " " << test2 << endl;
int test3 = test1+test1*test1-test2+test2/test1;
cout << "After performing test1 + test1 * test1 - test2 + test2 / test1, the result is:" << " " << test3 << endl;
   return 0;
}
