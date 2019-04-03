#include "../lexer.h"
#include <iostream>
#include "../grammar.cpp"
#include <string>
#include <unordered_set>

using namespace std;


// creates the string so CYK can understand it
string createLine(lexer & token_test) {
  string holder, analyze;

  // if the think is a graph method pass in the mothod
  // maybe make the different grammars for print, graph, and  math


      // while we havent hit the end of line
      while (token_test.next().first != "newl") {
        // take in the first token
        string holder = token_test.next().first;
        if (holder == "op") {
          // if it's an operation, use the operator
          holder = token_test.next().second;
        } else if (holder == "func") {
          // if it's a func, use the function
          holder = token_test.next().second;
        } else if (holder == "graph") {
          // if it's a func, use the function
          holder = token_test.next().second;
        }
        // concatenate the strings
        analyze = analyze + " " + holder;
        // move on to the next token
        token_test.pop();
      } token_test.pop();
  return analyze;
}

int main(){

    unordered_map<string, USS> grammar = makeGrammar("grammarTest.txt");
    // printGrammar(grammar);
    string analyze;

    // Example usage of the class
    lexer token_test, copy;
    token_test = tokenize_file("test.p");
    copy = token_test;

    while(!token_test.isempty()) {
      // make the string to be analyzed by CYK
      analyze = createLine(token_test);

      // skip empty lines
      if (analyze.empty()) continue;

      // check if the syntax is valid
      if (CYK(analyze, grammar, "Print")) {
        cout << "PRINT: ";
      } else if (CYK(analyze, grammar, "MathArgument")) {
        cout << "MATH: ";
      } else if (CYK(analyze, grammar, "Assignment")) {
        cout << "ASSIGN: " ;
      } else if (CYK(analyze, grammar, "GraphFunc")) {
        cout << "GRAPH: " ;
      } else if (CYK(analyze, grammar, "Start")) {
        cout << "valid: " ;
      } else {
        cout << "invalid: ";
      }


      // print the result then the string analyzed
      cout << analyze << endl;

    }

    // Comparing tokens
    return 0;
}



// make clean && make lexer && ./lexer
