#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <cassert>
#include <utility>

using namespace std;


typedef vector<string> VS;
typedef unordered_set<string> USS;

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
// this assums that the proper format is followed
VS productionSplit(VS line) {
    int bro = 0;
    VS production;
    string holder = "";

    if (line.size() == 3) {
        // the algorithm below excludes if the nonterminal
        // produces just one nonterminal
        production.push_back(line[2]);
        return production;
    }

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

// returns true if the argument is a capital letter
// false otherwise
bool isCapital(char letter) {
    if ('A' <= letter && letter <= 'Z') return true;
    return false;
}

// this function checks if the given production rule for
// any non terminal follows the CNF form
bool CNFvalid(string production) {
    VS split = splicer(production);
    if (split.size() == 2) {
        if (isCapital(split[0][0]) && isCapital(split[0][0])) return true;
    } else if (split.size() == 1) {
        if (!isCapital(split[0][0])) return true;
    }
    return false;
}

// prints a vector separated by whitespace
// doesn't print an endline though
void printVec(VS stuff) {
    for (int i=0; i<stuff.size(); i++) {
        cout << stuff[i] << i <<  endl;
    } cout << endl;
}



// this checks if the string is a number or not
// it works
bool isThisNum(string line) {
    try {
        int num = stoi(line);
        num++;
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}

// takes in input from terminal
// the key: "nonterminals" is a set of the non-terminals
unordered_map<string, USS> makeGrammar() {

    unordered_map<string, USS> grammar;
    string holder;
    VS stringVec, stringy;

    while (holder != "Q") {
        // cout << "Input: ";
        getline(cin, holder);
        stringVec = splicer(holder);
        // printVec(stringVec);
        // "//" is how we comment the conn
        if (stringVec.empty()) continue;
        if (stringVec[0] == "//") continue;
        for (int i=0; i < stringVec.size(); i++) {
            if (!(isCapital(stringVec[i][0])) && stringVec[i] != "|") {
                grammar["terminals"].insert(stringVec[i]);
            }
        }
        stringy = productionSplit(stringVec);
        // only these three letters are allowed to start the requests
        // this is just for error checking
        assert(stringVec[0] == "N" | stringVec[0] == "//" | stringVec[0] == "Q");

        for (int i=0; i < stringy.size(); i++) {
            // put them in the set described by
            assert(CNFvalid(stringy[i]));
            grammar[stringVec[1]].insert(stringy[i]);
        }

        if (holder != "Q") grammar["nonterminals"].insert(stringVec[1]);
    }
    return grammar;
}

bool thisStringInThisSet(string part, USS readySet) {
    if (readySet.find(part) != readySet.end()) return true;
    return false;
}

// just prints the structure of the grammar to terminal
// returns how many nonterminals there are
int printGrammar(unordered_map<string, USS> grammar) {
    ////////////////////////// PRINT THE GRAMMAR //////////////////////////////////
    int bro = 0;
    cout << endl;
    for (auto x: grammar) {
        if (x.first == "nonterminals" || x.first == "terminals") continue;
        bro++;
        cout << x.first << " --> ";
        for (auto y: grammar[x.first]) {
            cout << y << " | ";
        } cout << endl;
    } cout << endl;
    // print the terminals and the non terminals
    cout << "nonterminals: ";
    for (auto y: grammar["nonterminals"]) {
            cout << y << " ";
    } cout << endl << "terminals: ";
    for (auto y: grammar["terminals"]) {
            cout << y << " ";
    } cout << endl;
    cout << "Number of Non-Terminals: " << bro << endl;
    ////////////////////////// PRINT THE GRAMMAR //////////////////////////////////
}

// order is important
// AB x CD = AC, AD, BC, BD
VS cartesianProduct(USS first, USS second) {
    VS product;
    string holder;
    if (first.empty() || second.empty()) return product;
    for (auto x: first) {
        for (auto y: second) {
            // concatenate them
            holder = x + " " + y;
            // then put into the vector
            product.push_back(holder);
            // I do this just in case
            holder = "";
        }
    }
    return product;
}

void printUSS(USS stringSet) {
    for (auto x: stringSet) {
        cout << x <<  " ";
    }
}

// http://pages.cs.wisc.edu/~agorenst/cyk.pdf
// https://www.cs.bgu.ac.il/~michaluz/seminar/CKY1.pdf
bool CYK(string line, unordered_map<string, USS> & grammar) {
    VS split = splicer(line);
    if (split.empty()) {
        return false;
    }
    int n = split.size();
    // row first; column second
    USS CYK[n][n];

    // this populates the principal row
    for (int i=0; i<n ; i++) {
        for (auto x: grammar) {
            if (thisStringInThisSet(split[i], grammar[x.first])) {
                // cout << split[i] << " " << x.first << endl;
                CYK[0][i].insert(x.first);
            }
        }
    }
/*
    cout << endl;
    for (int i=0; i<n;i++) {
        cout << split[i] << ": ";
        printUSS(CYK[0][i]);cout << endl;
    } cout << endl;
*/
    pair<int,int> right, left;
    // triple for loops FTW
    for (int r=1; r<n; r++) {
        // cout << "out-" << r << ":\n";
        for (int j=0; j < n-r; j++){
            // cout << "j: "<< j << endl;
            // first is row, second is column
            left.first = 0; left.second = j;
            right.first = r-1; right.second = j+1;
            // cout << "start values: "; cout << left.first  << left.second << " " << right.first<< right.second << endl;
            for (int t=0; t<r; t++) {
                // do what needs to be done up here
                // before the pairs values are changed
                // cout << left.first  << left.second << " " << right.first<< right.second << endl;
                USS L = CYK[left.first][left.second];
                USS R = CYK[right.first][right.second];
                VS product = cartesianProduct(L,R);

                for (auto couple: product) {
                    for (auto nonterm: grammar) {
                        if(thisStringInThisSet(couple, grammar[nonterm.first])) {
                            CYK[r][j].insert(nonterm.first);
                        }
                    }
                }
                left.first += 1; right.first -= 1; right.second+= 1;
            }
        }
    }



/*
    for (int l=1; l<n; l++) {
        cout << "Main For Loop Start: " <<  l << endl;
        // this is the main one
        for (int r=0; r<l;r++) {
            // first is row, second is column
            left.first = l; left.second = r;
            right.first = l-1; right.second = r+1;

            for (int t=0; t<l; t++) {
                left.first++; right.first--; right.second++;
                cout << "left: " << left.first << " " << left.second;
                cout << " right: " << right.first << " " << right.second << endl;

                // cout << "l- " << l << " r- " << r << " t- " << t << endl;

                printUSS(L); cout << " |||| "; printUSS(R); cout << endl;
                // create the cartesian product of 
                VS pairs = cartesianProduct(L,R);


                for (auto couple: pairs) {
                    for (auto nonterm: grammar) {
                        if(thisStringInThisSet(couple, grammar[nonterm.first])) {
                            CYK[r][r+l].insert(nonterm.first);
                        }
                    }
                }

            }
        }
        cout << endl;
    }
*/
    // cout << "Final Set: "; printUSS(CYK[n-1][0]);
    if (thisStringInThisSet("S0",CYK[n-1][0])){
        return true;
    }
    return false;
}

// this takes in the tests from grammarRules.txt
void testFunc(unordered_map<string, USS> & grammar) {
    string bruh; bool hold; VS split;
    while (true) {
        getline(cin, bruh);
        if (bruh == "Stop") return;
        split = splicer(bruh);
        if (split.empty()) continue;
        if (split[0] == "//") continue;

        cout << bruh << ": ";
        if (CYK(bruh,grammar)) {
            cout << "valid" << endl;
        } else {
            cout << "invalid" << endl;
        }
    }
}



int main() {  
    cout << endl;
    // makeGrammar creates a map
    // the key is the non terminal
    // the value is an unordered set of strings
    //      of the allowed productions
    // The grammar inputted is assumed to be in Chomsky Normal Form
    unordered_map<string, USS> grammar = makeGrammar();
    testFunc(grammar);
    // int F = printGrammar(grammar);

    cout << "The End" << endl << endl;
    return 0;
}