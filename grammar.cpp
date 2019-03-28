// Name: Hudson Shykowski & Dale Richmond Naviza
// ID : 1520045 & 1534579
// CMPUT 275, Winter 2019

#include "grammar.h"

using namespace std;

// this splices a string by whitespace
// returns a vector where each element is a "word" in the string
/*
 * Input - line: a string object
 * Output - split: a vector string of line separated by whitespace
 *
 */
vector<string> splicer(string line) {
  string buf;                 // Have a buffer string
  stringstream ss(line);       // Insert the string into a stream

  vector<string> split;  // Create vector to hold our words

  while (ss >> buf)
        split.push_back(buf);

  return split;
}

// separates the vector by "|"
// ignores the first two elements
// this assums that the proper format is followed
vector<string> productionSplit(vector<string> line) {
    int bro = 0;
    vector<string> production;
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


// prints a vector separated by whitespace
// doesn't print an endline though
void printVec(vector<string> stuff) {
    for (int i=0; i<stuff.size(); i++) {
        cout << stuff[i] << i <<  " ";
    } cout << endl;
}

// order matters
vector<string> getCartesianProduct(string one, string two) {
    vector<string> product;
    string first, second;
    first = second = "";
    for (auto x: one) {
        first = x;
        for (auto y: two) {
            second = y ;
            product.push_back(first + second);
        }
    }
    return product;
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

// key is the nonterminal capital letter
// value is the set of allowed syntax
unordered_map<string, unordered_set<string>> grammar;
// this is the set of non terminals
unordered_set<string> nonTerminals;
unordered_set<string> terminals;

// takes in input from terminal
// the key: "nonterminals" is a set of the non-terminals
unordered_map<string, unordered_set<string>> makeGrammar() {

    unordered_map<string, unordered_set<string>> grammar;
    string holder;
    vector<string> stringVec, stringy;

    while (holder != "Q") {
        // cout << "Input: ";
        getline(cin, holder);
        stringVec = splicer(holder);
        // printVec(stringVec);
        // "//" is how we comment the conn
        if (stringVec[0] == "//") continue;
        for (int i=0; i < stringVec.size(); i++) {
            if ('a' <= (stringVec[i])[0] && (stringVec[i])[0] <= 'z') {
                grammar["terminals"].insert(stringVec[i]);
            }
        }
        stringy = productionSplit(stringVec);
        // only these three letters are allowed to start the requests
        // this is just for error checking
        assert(stringVec[0] == "N" | stringVec[0] == "//" | stringVec[0] == "Q");

        for (int i=0; i < stringy.size(); i++) {
            // put them in the set described by 
            grammar[stringVec[1]].insert(stringy[i]);
        }

        if (holder != "Q") grammar["nonterminals"].insert(stringVec[1]);
    }
    return grammar;
}

bool thisStringInThisSet(string part, unordered_set<string> & readySet) {
    if (readySet.find(part) != readySet.end()) return true;
    return false;
}



int main() {  
    
    // makeGrammar creates a map
    // the key is the non terminal
    // the value is an unordered set of strings
    //      of the allowed productions
    // The grammar inputted is assumed to be in Chomsky Normal Form
    unordered_map<string, unordered_set<string>> grammar = makeGrammar();
    
    int bro = 0;
    cout << endl;
    for (auto x: grammar) {
        bro++;
        if (x.first == "nonterminals" || x.first == "terminals") continue;
        cout << x.first << " --> ";
        for (auto y: grammar[x.first]) {
            cout << y << " | ";
        } cout << endl;
    }
    cout << endl << "Number of Non-Terminals: " << bro - 2 << endl;

    return 0;
}