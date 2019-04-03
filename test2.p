g = graph

# Example of graph method usage
g addVertex 5 "Hello"
g addVertex 6 "No"
g addVertex 7 "Yes"
g addEdge 5 6
g addEdge 5 7

# Example of printing
print : "Does the edge from 6 to 7 exist?" g isEdge 6 7
print : "5 is a vertex?:" g isVertex 5
print : "The contents of 5 are:" g getVertex 5
print : "The number of neighbours of vertex 5 are:" g numNeighbours 5

# Examples of variable modification
test1 = 5
test2 = 6
print : "test1 contains the number:" test1 "and test2 contains the number" test2
test3 = test1 + test1 * test1 - test2 + test2 / test1
print : "After performing test1 + test1 * test1 - test2 + test2 / test1, the result is:" test3
