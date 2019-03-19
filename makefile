all: lexer digraphtest treetest

lexer:
	g++ lexer.cpp tests/lextest.cpp -std=c++11 -o lexer

digraphtest:
	g++ digraph.cpp tests/digraphtest.cpp -std=c++11 -o digraphtest

treetest:
	g++ tests/treetest.cpp tree.cpp digraph.cpp -std=c++11 -o treetest

clean:
	rm -rf lexer
	rm -rf digraphtest
	rm -rf treetest
