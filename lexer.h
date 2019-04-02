#ifndef _LEXER_H_
#define _LEXER_H_

#include <unordered_set>
#include <queue>
#include <fstream>
#include <utility> // For pair
#include <assert.h> // assert ensures file exists
#include <regex> // to check for strings

//boost headers
#include <boost/algorithm/string.hpp>


// http://www.cplusplus.com/reference/queue/queue/
// http://www.cplusplus.com/reference/unordered_set/unordered_set/
// http://www.cplusplus.com/reference/utility/pair/pair/

using namespace std;

// Lexer object used for determining the lexical type off a token
class lexer {
    public:
        // Allows inserting of a new token
        void insert(string token);

        // Allows retrieving the next item
        pair<string, string> next();

        // Pops the next item off of the queue
        void pop();

    private:
        unordered_set<string> func {"print", "add", "subtract", "func"};
        unordered_set<string> op {":", "=", "+", "-", "*", "/"};
        unordered_set<string> bin_op {"!=", "=="};
        unordered_set<string> key_words{"Graph"};
        unordered_set<string> newl {"\n"};
        unordered_set<string> boolean {"TRUE", "FALSE"};
        unordered_set<string> none {"NULL"};

        // First element is the type, second element is the token
        queue<pair<string, string>> token_list;

        // Returns lexical "type"
        string determine_type(string value);
};

// Determines the lexical types of all tokens in a file, and stores it in a lexer object
lexer tokenize_file(string filename);


#endif
