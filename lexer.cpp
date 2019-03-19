#include "lexer.h"

using namespace std;

// Allows inserting of a new token
void lexer::insert(string token) {
    string type = determine_type(token);
    if(type == "string") {
        // Change the first and last characters from ' to "
        token[0] = '"';
        token[token.size()-1] = '"';
    }
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

// Returns lexical "type"
string lexer::determine_type(string value) {
    // Check if it is an identifier
    if(func.find(value) != func.end()) {
        return "func";
    }
    // Check if it is an operator
    else if (op.find(value) != op.end()) {
        return "op";
    }
    // Check if it is a number
    else if (num.find(value) != num.end()) {
        return "int";
    }
    // Check if it is a new line token
    else if(newl.find(value) != newl.end()) {
      return "newl";
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
    else if(regex_match(value, regex("('.*.?')"))) {
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
       boost::split(result, line, boost::is_any_of(" "));
       for(string token : result) {
         // Ignore whitespace read in as a token
         if(token == "") {
           continue;
         }
         // Skip comments
         else if(token == "#") {
           break;
         }
         // For each token, insert it in the lexer object
         lex.insert(token);
			}
      // Insert a newline token at the end of each line
      lex.insert("\n");
   }

   // Close the file
   stream.close();

   return lex;
}
