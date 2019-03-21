// Functions here define the grammer specified in the readme

#include "parser.h"

using namespace std;

// Parser constructor
Parser::Parser(lexer t_list) {
    token_list = t_list;
}

// Parser add id
void Parser::add_id(string id, string type) {
    defined_ids.insert({id, type});
}

// Parser id lookup
// Only returns true if the name and type are correct
bool Parser::find_id(string id, string type) {
    if (defined_ids.find(id) != defined_ids.end()) {
        // If the id has an item with the same type, return true
        return (defined_ids.find(id)->second == type) ? true : false;
    }
    else {
        return false;
    }
}

void Parser::read_until_newl() {
    while(token_list.next().first != "newl") {
        token_list.pop();
    }
    // Pop out the newline character
    token_list.pop();
}

string Parser::check_math() {
    // TODO: RICHMOND
    return ""; // just for now so stuff compiles
}

// Continually appends chains of strings together into a single string
string Parser::check_string() {
    string final;
    // Check if the input is even a string to begin with
    if(token_list.next().first != "string") {
        return "";
    }
    // Continually read in strings until we reach and endl
    while(token_list.next().first != "newl") {
        if(token_list.next().first != "string") {
            cout << token_list.next().second << endl;
            cout << "Error in check_string: Only type 'string' can be chained together" << endl;
            exit(EXIT_FAILURE);
        }
        // Create the next string to insert into the final string
        string next = token_list.next().second;

        // Format the string, remove the first and last " characters to make chaining easier
        next = next.substr(1, next.size() - 2);

        // Add the string chains up
        final += next + " ";

        // Pop out the next item
        token_list.pop();
    }
    // Pop out the newl character
    token_list.pop();

    // Remove the extra space at the end
    final.pop_back();

    // Readd the starting and ending " characters
    return '"' + final + '"';
}

string Parser::check_assign() {
    string final;
    if(token_list.next().first != "id") {
        //cout << "Error in check_assign: Only identifiers can be assigned" << endl;
        return "";  // Return empty string, we were unable to match.
    }
    // Store the identifier
    string id = token_list.next().second;

    // Pop the identifier
    token_list.pop();

    // Check if we are properly using the assignement operator
    if(token_list.next().second != "=") {
        cout << "Error in check_assign: Must use = to assign a variable" << endl;
        return "";  // Return empty string, we were unable to match.
    }

    // Pop the assignement operator
    token_list.pop();

    if(token_list.next().first == "int") {
        // If it's already defined, do not put int in front
        if(this->find_id(id, "int")) {
            final = id + " = ";
        }
        else {
            // Add the type and the name to the final expression
            final = "int " + id + " = ";

            // Add the id to the defined identifiers set.
            this->add_id(id, "int");
        }
        // TODO: evaulate integer expression
        final += check_math();
    }
    else if(token_list.next().first == "string") {
        if(this->find_id(id, "string")) {
            final = id + " = ";
        }
        else {
            // Add the type and the name to the final string
            final = "string " + id + " = ";

            // Add the id to the defined identifiers set.
            this->add_id(id, "string");
        }
        // Add the string to the assignment
        final += check_string();
    }
    else {
        cout << token_list.next().first << endl;
        cout << "Error: Assigning to an invalid token (must be int or string)" << endl;
        exit(EXIT_FAILURE);
    }
    return final;
}

string Parser::check_print() {
    string final = "cout";
    if(token_list.next().second != "print") {
        //cout << "Error in check_print: Function is not print." << endl;
        return "";  // Return empty string, we were unable to match.
    }
    // Pop out the print token
    token_list.pop();
    if(token_list.next().second != ":") {
        cout << "Error in print statement: Invalid syntax." << endl;
        exit(EXIT_FAILURE);
    }
    // Pop out the : token
    token_list.pop();

    if(token_list.next().second == "print") {
        cout << "Error: Nested print statements are illegal." << endl;
        exit(EXIT_FAILURE);
    }

    else if(token_list.next().first == "string") {
        // Add the string to the print statement
        final += " << " + check_string();
    }
    else if(token_list.next().first == "int") {
        // Add the integer to the print statement
    }
    //else if(token_list.next().first == "id" && this

    final += " << endl;";
    return final;
}

string Parser::check_all() {
    line_count += 1;   // We will be reading in a line each time
    string final;

    // Check if it's a math expression
    final = check_math();
    // Return the expression
    if(final != "") return final;

    // Check if it's a string expression
    final = check_string();
    // Return the expression
    if(final != "") return final;

    // Check if it's an assignment expression
    final = check_assign();
    // Return the expression
    if(final != "") return final;

    // Check if it's a print expression
    final = check_print();
    // Return the expression
    if(final != "") return final;

    else {
        // Read until we reach a new line
        read_until_newl();

        return "Error on line: " + to_string(line_count);
    }
}


int main() {
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test.p");

    Parser p = Parser(token_test);

    while(true) {
        cout << p.check_all() << endl;
        usleep(1000000);
    }
}
