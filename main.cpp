#include "transpiler.h"
#include "lexer.h"
#include <iostream>
#include <queue>

int main() {
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test.p");

    Transpiler t = Transpiler(token_test);

    // TODO Something with grammer here

    t.start();

    queue<string> grammar_queue;
    // TODO: Get a proper queue from the grammar thing

    while(!grammar_queue.empty()) {
        if(grammar_queue.front() == "p") {
            t.print();
        }
        else if(grammar_queue.front() == "a") {
            t.assignment();
        }
        else if(grammar_queue.front() == "g") {
            t.graph();
        }
        grammar_queue.pop();
    }

    t.end();
    t.compile();
    return 0;
}
