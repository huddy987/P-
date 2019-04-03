#include "transpiler.h"
#include "lexer.h"
#include "./tests/lextest.cpp"
#include <iostream>
#include <queue>

int main() {
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test.p");

    UMSUSS grammar = makeGrammar("grammarTest.txt");

    Transpiler t = Transpiler(token_test);



    // TODO Something with grammar here
    t.start();

    // return what kind of line each thing is
    queue<string> grammar_queue = populateGrammar(grammar, token_test);
    // TODO: Get a proper queue from the grammar thing
    int counter = 0;



    while(!grammar_queue.empty()) {
        // cout << counter++ << endl;
        if(grammar_queue.front() == "p") {
            t.print();
        }
        else if(grammar_queue.front() == "a") {
            t.assignment();
        }
        else if(grammar_queue.front() == "g") {
            t.graph();
        } else {
            cout << "Invalid Syntax: " << endl;
        }
        grammar_queue.pop();
    }

    t.end();
    t.compile();
    return 0;
}
