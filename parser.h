#ifndef _GRAMMER_H_
#define _GRAMMER_H_

#include <iostream> // So we can print
#include <unordered_map>
#include <utility> // For pair
#include "lexer.h" // For the lexer class
#include <stdlib.h> // So we can exit if theres an error
#include <string>   // For string manipulation
#include <unistd.h> // For usleep()


using namespace std;

class Parser {
    public:
        // Constructor
        Parser(lexer t_list);

        // Keeps reading newlines in continually
        void read_until_newl();

        // Evaluates a math expression
        string check_math();

        // Evaluates a sequence of strings
        string check_string();

        // Evaluates assignment operation
        string check_assign();

        // Evaluates print function
        string check_print();

        // Evaluates all of the aboves in attempt to match, returns a blank string otherwise
        string check_all();

        // Adds a defined id
        void add_id(string id, string type);

        // Checks if the id is defined
        bool find_id(string id, string type);

    private:
        lexer token_list;
        // Key is the identifier name, item is the identifier type
        // This is a bit unintuitive but it is because we only allow uniqie identifier names
        unordered_map<string, string> defined_ids;
        int line_count = 0;
};

#endif
