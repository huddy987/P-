#include "lexer.h"
#include <iostream>

using namespace std;

// Allows inserting of a new token
void lexer::insert(string token) {
    string type = determine_type(token);
    token_list.push(pair<string, string>(type, token));
}

// Allows retrieving the next item
pair<string, string> lexer::next() {
    // Return the front token
    return this->token_list.front();
}

// Pops the next item off of the queue
void lexer::pop() {
    this->token_list.pop();
}

// determines if the queue is empty or not
bool lexer::isempty() {
    return this->token_list.empty();
}

// Returns lexical "type"
string lexer::determine_type(string value) {
    // Check if it is an identifier
    if(func.find(value) != func.end()) {
        return "func";
    }
    // Check if it is a binary operator
    else if(bin_op.find(value) != bin_op.end()) {
        return "bin_op";
    }
    // Check if it is an operator
    else if (op.find(value) != op.end()) {
        return "op";
    }
    // Check if it is a graph method
    else if (graph.find(value) != graph.end()) {
        return "graph";
    }
    // Check if it is a number
    // https://stackoverflow.com/questions/7407099/regex-match-numbers-of-variable-length
    else if (regex_match(value, regex("(\\d+)"))) {
        return "int";
    }
    // Check if it is a new line token
    else if(newl.find(value) != newl.end()) {
      return "newl";
    }
    else if(keywords.find(value) != keywords.end()) {
        return "keyword";
    }
    // Check if it is a nonetype token
    else if(none.find(value) != none.end()) {
      return "none";
    }
    // Check if it is a boolean token
    else if(boolean.find(value) != boolean.end()) {
      return "bool";
    }
    // Check if it is a string token
    else if(regex_match(value, regex("(\".*.?\")"))) {
      return "string";
    }
    // If it reaches this, it is an identifier
    else {
        return "id";
    }
}

// Determines the lexical types of all tokens in a file, and stores it in a lexer object
lexer tokenize_file(string filename) {
    // Create a file stream object
   ifstream stream;
   // Open the file
   stream.open(filename);
   // Assert that the file exists
   assert(stream);
   // Create line object
   string line;
   // Create a tokens object which we will build upon
   lexer lex;
   // Continually read in lines to build the queue until we reach EOF
   while (true) {
       // Read in a line
       getline(stream, line);
       // Check for EOF
       if (stream.eof()) {
           break;
       }
       // Split into tokens
       // Used this https://www.geeksforgeeks.org/boostsplit-c-library/
       vector<string> result;

       // Flag that we are creating a string
       bool strflag = 0;

       // String we will match
       string out;

       boost::split(result, line, boost::is_any_of(" "));
       for(string token : result) {
         // Swap into a different mode if we are scanning a string
         if(token[0] == '\"' && token.back() != '\"') {
             strflag = 1;
             out = token;
             continue;
         }
         if(strflag == 1) {
            out += " " + token;
            if(token.back() == '\"') {
                // Exit "string" mode
                strflag = 0;
                lex.insert(out);
            }
            continue;
        }
         // Ignore whitespace read in as a token
         if(token == "") {
           continue;
         }
         // Skip comments
         else if(token == "#") {
           break;
         }
         else {
            out = token;
         }
         lex.insert(out);
     }
      // Insert a newline token at the end of each line
      lex.insert("\n");
   }

   // Close the file
   stream.close();

   return lex;
}
