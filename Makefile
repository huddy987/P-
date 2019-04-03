all: lexer digraphtest treetest grammar transpiler main 

main:
	g++ main.cpp lexer.cpp transpiler.cpp -std=c++11 -o main

transpiler:
	g++ transpiler.cpp lexer.cpp -std=c++11 -o transpiler

lexer:
	g++ lexer.cpp tests/lextest.cpp -std=c++11 -o lexer

lexer2:
	g++ lexer.cpp tests/lexhuddy.cpp -std=c++11 -o lexer

digraphtest:
	g++ digraph.cpp tests/digraphtest.cpp -std=c++11 -o digraphtest

treetest:
	g++ tests/treetest.cpp tree.cpp digraph.cpp -std=c++11 -o treetest

grammar:
	g++ grammar.cpp -std=c++11 -o grammar

grammartest: grammar
	./grammar < grammarTest.txt

rich: clean lexer
	./lexer

clean:
	rm -rf lexer
	rm -rf digraphtest
	rm -rf treetest
	rm -rf grammar
	rm -rf transpiler
	rm -rf main
