// Name: Hudson Shykowski & Dale Richmond Naviza
// ID : 1520045 & 1534579
// CMPUT 275, Winter 2019
// Final Assignment: P- programming language

#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

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
#include <queue>

using namespace std;


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
VS splicer(string line);

// separates the vector by "|"
// ignores the first two elements
// this assumes that the proper format is followed
/*
 * Input  - line: the entire line of definition for the nonterminal
 *
 * Output - vector string of each production rule
 */
VS productionSplit(VS line);

/*
 * Input  - letter char
 *        -
 * Output - true if the argument is a capital letter
          - false otherwise
 */
bool isCapital(char letter);

// this function checks if the given production rule for
// any non terminal follows the CNF form
bool CNFvalid(string production);

/*
 * Input  - vector string
 *        -
 * Output - none prints a vector separated by whitespace
 */
void printVec(VS stuff);



// this checks if the string is a number or not
// it works
/*
 * Input  - line, a string
 *        -
 * Output - true or false
 */
bool isThisNum(string line);

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
unordered_map<string, USS> makeGrammar(string filename);

/*
 * Input  - line, a string
 *        -
 * Output - true or false, very descriptive function name
 */
bool thisStringInThisSet(string part, USS readySet);

// just prints the structure of the grammar to terminal
// returns how many nonterminals there are
/*
 * Input  - grammar, what describes the grammar
 *        -
 * Output - none - just prints to screen
 */
void printGrammar(unordered_map<string, USS> grammar);

/*
 * Input  - two unordered sets of strings
 *        -
 * Output - example output:
            "AB" x "CD" = "A C", "A D", "B C", "B D"
 */
VS cartesianProduct(USS first, USS second);

/*
 * Input  - stringSet: an unordered set of strings
 * Output - none: just prints an unordered set of string
 */
void printUSS(USS stringSet);

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
bool CYK(string line, unordered_map<string, USS> & grammar, string start = "Start");

// this takes in the tests from grammarRules.txt
/*
 * Input  - grammar for the syntax
 *        -
 * Output - none : prints if the input given is valid or not
 */
void testFunc(unordered_map<string, USS> & grammar);

// creates the string so CYK can understand it

/*
 * Input  - lexer object
 * Output - creates the line that CYK will analyze - its a string
 */
string createLine(lexer & token_test);

/*
 * Input  - line to be analyzed
 *        - grammar map
 * Output - a letter that describes what the line is
 * This is how we add "context" to the context free grammar
 */
string determineContext(string line, UMSUSS & grammar);

/*
 * Input  - grammar map
 *        - lexer object token_test
 * Output - queue of letters describing what that line was
 */
queue<string> populateGrammar(UMSUSS & grammar, lexer token_test);


#endif
