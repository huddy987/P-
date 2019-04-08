// Name: Hudson Shykowski & Dale Richmond Naviza
// ID : 1520045 & 1534579
// CMPUT 275, Winter 2019
// Final Assignment: P- programming language

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <cassert>
#include <utility>
#include <fstream>
#include "lexer.h"
#include "transpiler.h"
#include <queue>

using namespace std;


/*
 * Input  -
 *        -
 * Output -
 */


typedef vector<string> VS;
typedef unordered_set<string> USS;
typedef unordered_map<string, USS> UMSUSS;

// this splices a string by whitespace
// returns a vector where each element is a "word" in the string
/*
 * Input - line: a string object
 * Output - split: a vector string of line separated by whitespace
 *
 */
VS splicer(string line) {
  string buf;                 // Have a buffer string
  stringstream ss(line);       // Insert the string into a stream

  VS split;  // Create vector to hold our words

  while (ss >> buf)
        split.push_back(buf);

  return split;
}

// separates the vector by "|"
// ignores the first two elements
// this assumes that the proper format is followed
/*
 * Input  - line: the entire line of definition for the nonterminal
 *
 * Output - vector string of each production rule
 */
VS productionSplit(VS line) {
    int bro = 0;
    VS production;
    string holder = "";

    // this is for when the nonterminal --> one terminal
    if (line.size() == 3) {
        // the algorithm below excludes if the nonterminal
        // produces just one nonterminal
        production.push_back(line[2]);
        return production;
    }

    // iteratre over line
    for (int i=2; i < line.size(); i++) {
        if (line[i] == "|") continue;
        // this handles the last element
        if (i == line.size() - 1) {
            if (line[i-1] == "|") {
            // if the previous element is "|" then add
                production.push_back(line[i]);
            } else {
                // else add the last element then pushback
                holder = line[i-1] + " " + line[i];
                production.push_back(holder);
            }
            break;
        }
        // if first element just the char
        // holder already holds something, add the space
        if (holder == "") holder = line[i];
        else holder = holder + " " + line[i];

        if (line[i+1] == "|") {
            // if next element is |
            // then put in the array and restart the loop
            production.push_back(holder);
            holder = "";
        }
    }
    return production;
}

/*
 * Input  - letter char
 *        -
 * Output - true if the argument is a capital letter
          - false otherwise
 */
bool isCapital(char letter) {
    if ('A' <= letter && letter <= 'Z') return true;
    return false;
}

// this function checks if the given production rule for
// any non terminal follows the CNF form
bool CNFvalid(string production) {
    // split the production rule
    VS split = splicer(production);
    // only size of 2 or 1 is valid
    if (split.size() == 2) {
        // if size 2, both have to be non terminals
        if (isCapital(split[0][0]) && isCapital(split[0][0])) return true;
    } else if (split.size() == 1) {
        // if size 1, it has to be a terminal
        if (!isCapital(split[0][0])) return true;
    }
    return false;
}

/*
 * Input  - vector string
 *        -
 * Output - none prints a vector separated by whitespace
 */
void printVec(VS stuff) {
    for (int i=0; i<stuff.size(); i++) {
        cout << stuff[i] << i <<  endl;
    } cout << endl;
}



// this checks if the string is a number or not
// it works
/*
 * Input  - line, a string
 *        -
 * Output - true or false
 */
bool isThisNum(string line) {
    try {
        // literally just try this
        int num = stoi(line);
        num++;
    } catch (std::invalid_argument) {
        // if it fails, then not a number
        return false;
    }
    return true;
}

// takes in input from terminal
// the key: "nonterminals" is a set of the non-terminals
/*
 * Input  - none
 *        -
 * Output - map of the grammar-
                key: string of the nonterminal
                value: set of production rules for that nonterminal
        "nonterminals" : set of the non-terminals
        "terminals" : set of the terminals
 */
unordered_map<string, USS> makeGrammar(string filename) {

    unordered_map<string, USS> grammar;
    string holder;
    VS stringVec, stringy;

    ifstream stream;
   // Open the file
   stream.open(filename);
   // Assert that the file exists
   assert(stream);

    while (holder != "Q") {
        // read the input then splice it by spaces
        getline(stream, holder);
        stringVec = splicer(holder);
        // printVec(stringVec);
        // "//" is how we comment the conn
        if(stringVec.empty()) continue;
        if (stringVec[0] != "N") continue;
        // "//" is how we comment the grammar definitions
        // if just an empty line, skip the line
        for (int i=0; i < stringVec.size(); i++) {
            // if the element of the line is not capital, add it to the terminals
            if (!(isCapital(stringVec[i][0])) && stringVec[i] != "|") {
                grammar["terminals"].insert(stringVec[i]);
            }
        }
        // split by "|" and ignore the first two elements of the vector
        stringy = productionSplit(stringVec);
        // only these three letters are allowed to start the requests
        // this is just for error checking
        assert(stringVec[0] == "N" | stringVec[0] == "//" | stringVec[0] == "Q");

        for (int i=0; i < stringy.size(); i++) {

            // put them in the set described by
            if (CNFvalid(stringy[i])) {
                grammar[stringVec[1]].insert(stringy[i]);
            } else {
                cout << "error: " << stringy[i] << " " << stringy[i+1] << endl;
                // crash the program if it's not in Chomsky Normal Form
                assert(CNFvalid(stringy[i]));
            }
        }
        // add the nonterminal to that key in the grammar
        if (holder != "Q") grammar["nonterminals"].insert(stringVec[1]);
    }
    stream.close();
    return grammar;
}

/*
 * Input  - line, a string
 *        -
 * Output - true or false, very descriptive function name
 */
bool thisStringInThisSet(string part, USS readySet) {
    if (readySet.find(part) != readySet.end()) return true;
    return false;
}

// just prints the structure of the grammar to terminal
// returns how many nonterminals there are
/*
 * Input  - grammar, what describes the grammar
 *        -
 * Output - none - just prints to screen
 */
void printGrammar(unordered_map<string, USS> grammar) {
    ////////////////////////// PRINT THE GRAMMAR //////////////////////////////////
    int bro = 0;
    cout << endl;
    // go through the keys of the map
    for (auto x: grammar) {
        // skip the nonterminals and the terminals
        if (x.first == "nonterminals" || x.first == "terminals") continue;
        bro++;
        cout << x.first << " --> ";
        // print the production rules of the given nonterminal
        for (auto y: grammar[x.first]) {
            cout << y << " | ";
        } cout << endl;
    } cout << endl;
    // print the terminals and the non terminals
    cout << "nonterminals: ";
    for (auto y: grammar["nonterminals"]) {
        // print the nonterminals
            cout << y << " ";
    } cout << endl << "terminals: ";
    for (auto y: grammar["terminals"]) {
        // print the terminals
            cout << y << " ";
    } cout << endl;
    cout << "Number of Non-Terminals: " << bro << endl<< endl;
    ////////////////////////// PRINT THE GRAMMAR //////////////////////////////////
}

/*
 * Input  - two unordered sets of strings
 *        -
 * Output - example output:
            "AB" x "CD" = "A C", "A D", "B C", "B D"
 */
VS cartesianProduct(USS first, USS second) {
    VS product;
    string holder;
    // if empty, cartesian product is an empty set
    if (first.empty() || second.empty()) return product;
    for (auto x: first) {
        for (auto y: second) {
            // concatenate them
            holder = x + " " + y;
            // then put into the vector
            product.push_back(holder);
            // I do this just in case but not nescessary
            holder = "";
        }
    }
    return product;
}

/*
 * Input  - stringSet: an unordered set of strings
 * Output - none: just prints an unordered set of string
 */
void printUSS(USS stringSet) {
    for (auto x: stringSet) {
        cout << x <<  " ";
    }
}

/*
 * Input  - line: the line to be examined
 *        -  grammar: description of grammar for this language
 * Output - true or false; if line is valid under the syntax described by grammar
 * Acknowledgement: I watched the youtube video linked below to learn the algorithm
                    However, I did not follow any pseduocode and tried to code it
                    based on how I understand it. xarg.org has a nice and quick
                    animation of the algorithm
 */
// https://www.xarg.org/tools/cyk-algorithm/
// https://www.youtube.com/watch?v=VTH1k-xiswM
bool CYK(string line, unordered_map<string, USS> & grammar, string start = "Start") {
    VS split = splicer(line);
    if (split.empty()) {
        return false;
    }
    int n = split.size();
    // row first; column second
    USS CYK[n][n];

    // this populates the principal row with the nonterminals
    // that can map to that specific token
    for (int i=0; i<n ; i++) {
        for (auto x: grammar) {
            // for every none terminal
            // check if it can produce the token
            if (thisStringInThisSet(split[i], grammar[x.first])) {
                // cout << split[i] << " " << x.first << endl;
                CYK[0][i].insert(x.first);
            }
        }
    }
/*  // this printed the first row of the CYK array
    cout << endl;
    for (int i=0; i<n;i++) {
        cout << split[i] << ": ";
        printUSS(CYK[0][i]);cout << endl;
    } cout << endl;
*/
    // these pairs will hold the coordinates
    // of the element in the array being examined/ populated
    pair<int,int> right, left;
    // triple for loops FTW
    for (int r=1; r<n; r++) {
        // the outermost for loop describes the row
        // cout << "out-" << r << ":\n";
        for (int j=0; j < n-r; j++){
            // second for loop describes the column
            // cout << "j: "<< j << endl;
            // first is row, second is column
            left.first = 0; left.second = j;
            right.first = r-1; right.second = j+1;
            // initialize the coordinates first
            for (int t=0; t<r; t++) {
                // do what needs to be done up here
                // before the pairs values are changed
                // L - left block; R - right block
                USS L = CYK[left.first][left.second];
                USS R = CYK[right.first][right.second];
                // look at their cartesian product
                VS product = cartesianProduct(L,R);

                for (auto couple: product) {
                    // iterate over the products
                    for (auto nonterm: grammar) {
                        // iterate over the non terminals
                        if(thisStringInThisSet(couple, grammar[nonterm.first])) {
                            // if the nonterminal maps to the product
                            // add it to the set inside that block
                            CYK[r][j].insert(nonterm.first);
                        }
                    }
                }
                // change the coordinates now
                left.first += 1; right.first -= 1; right.second+= 1;
            }
        }
    }
    // cout << "Final Set: "; printUSS(CYK[n-1][0]);
    if (thisStringInThisSet(start,CYK[n-1][0])){
        // the start is in the [n-1][0] block,
        // then the string is valid
        return true;
    }
    return false;
}

// this takes in the tests from grammarRules.txt
/*
 * Input  - grammar for the syntax
 *        -
 * Output - none : prints if the input given is valid or not
 */
void testFunc(unordered_map<string, USS> & grammar) {
    string bruh; bool hold; VS split;
    while (true) {
        getline(cin, bruh);
        // this is the stop message
        if (bruh == "Stop") return;
        // take it apart
        split = splicer(bruh);
        // if it's empty or a comment, skip it
        if (split.empty()) continue;
        if (split[0] == "//") continue;

        // check if valid then print result + input
        if (CYK(bruh,grammar, "Start")) {
            cout << "  valid: ";
        } else {
            cout << "invalid: ";
        } cout << bruh << endl;
    }
}

// creates the string so CYK can understand it

/*
 * Input  - lexer object
 * Output - creates the line that CYK will analyze - its a string
 */
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

/*
 * Input  - line to be analyzed
 *        - grammar map
 * Output - a letter that describes what the line is
 * This is how we add "context" to the context free grammar
 */
string determineContext(string line, UMSUSS & grammar) {
  // math expression, print statement, assignment, graph method, a generic start
  VS Context {"MathArgument", "Print", "Assignment","GraphFunc","Start"};
  VS ContextReturn {"m", "p","a","g","s"};

  /// check one the line matches to and output the result
  for (int i=0; i<Context.size(); i++) {
    if (CYK(line, grammar, Context[i])) return ContextReturn[i];
  }
  // If invalid, just crash everything and print the error
  cout << "Terminating. Invalid structure: " << endl;
  cout << line << endl;
  exit(EXIT_FAILURE);
  return "";
}


/*
 * Input  - grammar map
 *        - lexer object token_test
 * Output - queue of letters describing what that line was
 */
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
      // cout << determineContext(analyze, grammar) << ": " << analyze << endl;
      grammar_queue.push(determineContext(analyze, grammar));
    }

    // Comparing tokens
    return grammar_queue;
}





/*
 * Input  -
 *        -
 * Output -

int main() {
    cout << endl;
    // makeGrammar creates a map
    // the key is the non terminal
    // the value is an unordered set of strings
    //      of the allowed productions
    // The grammar inputted is assumed to be in Chomsky Normal Form

    unordered_map<string, USS> grammar = makeGrammar();
    printGrammar(grammar);
    testFunc(grammar);

    cout << "The End" << endl << endl;
    return 0;
} */
