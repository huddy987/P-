#include "../digraph.h"
#include <iostream>

using namespace std;

int main() {
    Digraph d;
    d.addVertex(0, "hi");
    d.addVertex(1, "bye");
    d.addVertex(2, "Hello");
    d.addEdge(0, 1);
    d.addEdge(0, 2);
    cout << d.isWalk(vector<int>{0, 1, 2}) << endl;
    cout << d.getVertex(0) << endl;
    cout << d.getVertex(1) << endl;
    cout << d.getVertex(2) << endl;
    return 0;
}
