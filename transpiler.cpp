// Functions here define the grammer specified in the readme

#include "transpiler.h"

using namespace std;

bool debug = true;

// Function to write to a file
void write_to_file(string to_write) {
    // Open the file, write to it, then close the file
    ofstream file;
    file.open("p++_temp.cpp", ios::app);
    file << to_write << endl;
    file.close();
}

// Transpiler constructor
Transpiler::Transpiler(lexer t_list) {
    token_list = t_list;
}

// Prints the start of the c++ Code
void Transpiler::start() {
    // Create a new file object and open
    ofstream file;
    file.open("p++_temp.cpp");

    system("echo You may see some files pop up in your current directory...");
    system("echo Please do not delete them. We will handle that for you!");

    file << "// This file should have been deleted. Don't read it please (secret).\n\n";

    file << "// Header files: A lot of them so we never fail to compile.\n";
    file << "#include <iostream>\n#include <unordered_map>\n"
            "#include <vector>\n#include <unordered_set>\n#include <algorithm>\n"
            "#include <set>\n#include <string>\n#include \"digraph.h\"\n\n";
    file << "using namespace std;\n\nint main() {\n";

    file.close();
}

void Transpiler::end() {
    // Create a new file object and open
    ofstream file;
    file.open("p++_temp.cpp", ios::app);
    file << "   return 0;\n}\n";
    file.close();
}

// Compiles the C++ code
void Transpiler::compile() {
    system("echo P++ file sucessfully transpiled. Now compiling C++ code...");
    // Compile the C++ code
    system("g++ p++_temp.cpp digraph.cpp -std=c++11 -o program");
    // Remove the C++ code
    if(!debug) system("rm -rf p++_temp.cpp");

    system("echo Done! Run ./program");
}

// Transpiler add id
// We save ids to add context to the transpiler
void Transpiler::add_id(string id, string type) {
    defined_ids.insert({id, type});
}

// Transpiler id lookup
// Only returns true if the name and type are correct
bool Transpiler::find_id(string id, string type) {
    if (defined_ids.find(id) != defined_ids.end()) {
        // If the id has an item with the same type, return true
        return (defined_ids.find(id)->second == type) ? true : false;
    }
    else {
        return false;
    }
}

void Transpiler::read_until_newl() {
    while(token_list.next().first == "newl") {
        token_list.pop();
    }
}

// Continually appends chains of math expressions together
string Transpiler::math_expression() {
    string final;
    // Check if the input is even a math expression to begin with
    if(token_list.next().first != "int") {
        cout << token_list.next().second << endl;
        cout << "Fail in math_expression: Value is not an integer" << endl;
        exit(EXIT_FAILURE);
    }
    while(token_list.next().first == "int" or token_list.next().first == "op") {
        final += token_list.next().second;
        token_list.pop();
    }
    return final;
}

// Continually appends chains of strings together into a single string
string Transpiler::string_expression() {
    string final;
    // Check if the input is even a string to begin with
    if(token_list.next().first != "string") {
        cout << token_list.next().second << endl;
        cout << "Fail in string_expression: Value is not a string" << endl;
        exit(EXIT_FAILURE);
    }
    // Continually read in strings until we reach and endl
    while(token_list.next().first == "string") {
        // Create the next string to insert into the final string
        string next = token_list.next().second;

        // Format the string, remove the first and last " characters to make chaining easier
        next = next.substr(1, next.size() - 2);

        // Add the string chains up
        final += next + " ";

        // Pop out the next item
        token_list.pop();
    }

    // Remove the extra space at the end
    final.pop_back();

    // Readd the starting and ending " characters
    return '"' + final + '"';
}

// Writes an assignment to the file
void Transpiler::assignment() {
    read_until_newl(); // Pop out all prior newlines
    string final;
    if(token_list.next().first != "id") {
        cout << "Error in check_assign: Only identifiers can be assigned" << endl;
        exit(EXIT_FAILURE);
    }
    // Store the identifier
    string id = token_list.next().second;

    // Pop the identifier
    token_list.pop();

    // Check if we are properly using the assignement operator
    if(token_list.next().second != "=") {
        cout << "Error in check_assign: Must use = to assign a variable" << endl;
        exit(EXIT_FAILURE);
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
        final += math_expression();
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
        final += string_expression();
    }
    else {
        cout << token_list.next().second << endl;
        cout << "Error: Assigning to an invalid token (must be int or string)" << endl;
        exit(EXIT_FAILURE);
    }

    // Add the ; character at the end of the line
    final += ";";

    // Assuming that we got to the newline character, this pops the newline out
    token_list.pop();

    // Open the file, write to it, then close the file
    write_to_file(final);
}

void Transpiler::print() {
    read_until_newl(); // Pop out all prior newlines
    bool first = 0; // flag for first token to be read in

    // Begin building the output
    string final = "cout";
    // Make sure print is the first token
    if(token_list.next().second != "print") {
        cout << "Error in check_print: Function is not print, we got "
        << token_list.next().second << " instead." << endl;
        exit(EXIT_FAILURE);
    }
    // Pop out the print token
    token_list.pop();

    // Make sure the delimiter is the next token
    if(token_list.next().second != ":") {
        cout << "Error in print statement: Invalid syntax." << endl;
        exit(EXIT_FAILURE);
    }
    // Pop out the : token
    token_list.pop();

    // Continually append the strings together
    while(token_list.next().first != "newl") {
        if(token_list.next().second == "print") {
            cout << "Error: Nested print statements are illegal." << endl;
            exit(EXIT_FAILURE);
        }

        else if(token_list.next().first == "string") {
            // Add the string to the print statement
            final += " << " + string_expression();
            // We do all the popping inside of string_expression: no need to do it here
            if(first == 0) first = 1;
        }
        // If it is an id, and it is defined already, then add this to the print statement
        else if(token_list.next().first == "id" && this->find_id(token_list.next().second, "string")) {
            // Add the id to the final string
            // Only adds the extra space at the front if it's first
            if(first != 0){
                final += " << \" \"";
            }
            else {
                first = 1;
            }
            // C++ was yelling at me: I had to do it this way
            final += " << " + token_list.next().second;
            // Pop the token out of the queue
            token_list.pop();
            if(token_list.next().first != "newl") {
                final += " << \" \"";
            }
        }
        else {
            cout << "Error in print statement: Cannot print non-strings" << endl;
            exit(EXIT_FAILURE);
        }
    }
    // Pop out the newl character
    token_list.pop();

    final += " << endl;";

    // Open the file, write to it, then close the file
    write_to_file(final);
}

/*
Garbage but dont delete in case we need it as a back up

string Transpiler::check_all() {
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
}*/


int main() {
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test.p");

    Transpiler t = Transpiler(token_test);

    t.start();
    
    t.assignment();
    t.assignment();
    t.print();
    t.print();
    t.print();

    t.end();
    t.compile();
}
