#include "../lexer.h"
#include <iostream>
#include "../grammar.cpp"
#include <string>
#include <unordered_set>
#include <queue>

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

string determineContext(string line, UMSUSS & grammar) {

  VS Context {"MathArgument", "Print", "Assignment","GraphFunc","Start"};
  VS ContextReturn {"m", "p","a","g","s"};

  for (int i=0; i<Context.size(); i++) {
    if (CYK(line, grammar, Context[i])) return ContextReturn[i];
  }
  // If invalid, just crash everything:
  cout << "Terminating. Invalid structure: " << endl;
  cout << line << endl;
  exit(EXIT_FAILURE);
  return "";
}


queue<string> populateGrammar(UMSUSS & grammar, lexer token_test){

    // printGrammar(grammar);
    string analyze;
    queue<string> grammar_queue;

    // Example usage of the class
    while(!token_test.isempty()) {
      // make the string to be analyzed by CYK
      analyze = createLine(token_test);

      // skip empty lines
      if (analyze.empty()) continue;
      //cout << determineContext(analyze, grammar) << ": " << analyze << endl;

      // determine what the context is: print this and the line
      cout << determineContext(analyze, grammar) << ": " << analyze << endl;
      grammar_queue.push(determineContext(analyze, grammar));
    }

    // Comparing tokens
    return grammar_queue;
}



// make clean && make lexer && ./lexer
