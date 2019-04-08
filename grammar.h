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

// this splices a string by whitespace
// returns a vector where each element is a "word" in the string
/*
 * Input - line: a string object
 * Output - split: a vector string of line separated by whitespace
 *
 */
vector<string> splicer(string line);

// separates the vector by "|"
// ignores the first two elements
// this assumes that the proper format is followed
// only works well for two string elements
vector<string> productionSplit(vector<string> line);


// prints a vector separated by whitespace
// doesn't print an endline though
void printVec(vector<string> stuff);

// order matters
vector<string> getCartesianProduct(string one, string two);

// this checks if the string is a number or not
// it works
bool isThisNum(string line);

// takes in input from terminal
// the key: "nonterminals" is a set of the non-terminals
// this takes in inputs from the terminal.
unordered_map<string, unordered_set<string>> makeGrammar();

// returns true if string in the set
bool thisStringInThisSet(string part, unordered_set<string> & readySet);

bool CYK(string analyze, unordered_map<string,const unordered_set<string>> & grammar)

#endif
