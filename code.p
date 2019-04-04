g = graph

# Example of graph method usage

g addVertex 5 "This test is contained in vertex 5"
g addVertex 6 "No"
g addVertex 7 "Yes"
g addEdge 5 6
g addEdge 6 5
g addEdge 5 7

a = 5


# Example of printing

print : "Does the edge from 6 to 7 exist?" g isEdge 6 7
print : "5 is a vertex?:" g isVertex 5
print : "The contents of 5 are:" g getVertex 5
print : "The number of neighbours of vertex 5 are:" g numNeighbours 5
print : "Is there a walk from 6 to 5 to 6 to 5 to 7?" g isWalk 6 5 6 5 7
print : "Is there a path from 6 to 5 to 6 to 5 to 7?" g isPath 6 5 6 5 7
print : "The size of the graph is:" g size
g addVertex 8 "The contents of 8!"
print : "The new size of the graph is:" g size


# Examples of variable modification

test1 = 5
test2 = 6

print : ""
print : "test1 contains the number:" test1 "and test2 contains the number" test2
test3 = test1 + test1 * test1 - test2 + test2 / test1
print : "After performing test1 + test1 * test1 - test2 + test2 / test1, the result is:" test3


# Examples of string manipulation

x = "hello"
y = "world"
z = "hello world"

print : ""
print : "String expressions:"
print : "hello" "world"
print : "hello" y
print : x "world"
x = x y
print : x
