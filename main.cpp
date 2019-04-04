#include "transpiler.h"
#include "lexer.h"
#include "grammar.cpp"
#include <iostream>
#include <queue>

int main() {
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test2.p");

    UMSUSS grammar = makeGrammar("grammarTest.txt");

    Transpiler t = Transpiler(token_test);

    cout << "Checking context free grammar." << endl;
    // return what kind of line each thing is
    queue<string> grammar_queue = populateGrammar(grammar, token_test);

    cout << "Context free grammar is good." <<  endl;

    // If it passes the grammar test with no fails, then compile
    t.start();

    while(!grammar_queue.empty()) {
        if(grammar_queue.front() == "p") {
            t.print();
        }
        else if(grammar_queue.front() == "a") {
            t.assignment();
        }
        else if(grammar_queue.front() == "g") {
            t.graph();
        } else {
            cout << "Invalid Syntax detected." << endl;
            t.end();
            exit(EXIT_FAILURE);
        }
        grammar_queue.pop();
    }

    t.end();
    t.compile();
    return 0;
}
