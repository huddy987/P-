#ifndef _GRAMMER_H_
#define _GRAMMER_H_

#include <iostream> // So we can print
#include <unordered_map>
#include <utility> // For pair
#include "lexer.h" // For the lexer class
#include <stdlib.h> // So we can exit if theres an error
#include <string>   // For string manipulation
#include <unistd.h> // For usleep()
#include <fstream> // For writing to files


using namespace std;

class Transpiler {
    public:
        // Constructor
        Transpiler(lexer t_list);

        // Prints the starting code that is always required.
        void start();

        // Prints the ending code that is always required
        void end();

        // Compiles the code created by this file
        void compile();

        // Keeps reading newlines in continually
        void read_until_newl();

        // Evaluates a math expression
        string math_expression();

        // Evaluates a sequence of strings
        string string_expression();

        // Evaluates assignment operation
        void assignment();

        // Evaluates print function
        void print();

        // Evaluates all of the aboves in attempt to match, returns a blank string otherwise
        //string check_all();

        // Adds a defined id
        void add_id(string id, string type);

        // Checks if the id is defined
        bool find_id(string id, string type);

        // Handles graph objects
        string graph();

    private:
        lexer token_list;
        // Key is the identifier name, item is the identifier type
        // This is a bit unintuitive but it is because we only allow uniqie identifier names
        unordered_map<string, string> defined_ids;
        int line_count = 0;
};

#endif
