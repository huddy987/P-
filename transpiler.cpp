// Name: Hudson Shykowski & Dale Richmond Naviza
// ID : 1520045 & 1534579
// CMPUT 275, Winter 2019
// Final Assignment: P- programming language



// Note for this file: The transpiler uses the queue contained in the lexer
// object for the majority of the functions contained here

#include "./transpiler.h"

using namespace std;

// Use debug to enable/disable deleting the temporary c++ file
bool debug = false;

bool supress_print = false;

// Function to write to a file
// to_write is the filename that you want to write to
void write_to_file(string to_write) {
    // Open the file, write to it, then close the file
    ofstream file;
    file.open("p++_temp.cpp", ios::app);
    file << to_write << endl;
    file.close();
}

// Transpiler constructor, requires a lexer object
Transpiler::Transpiler(lexer t_list) {
    token_list = t_list;
}

// Prints the start of the C++ code
void Transpiler::start() {
    // Create a new file object and open
    ofstream file;
    file.open("p++_temp.cpp");

    if (!supress_print) {
        system\
            ("echo You may see some files pop up in your current directory.");
        system\
            ("echo Please do not delete them. We will handle that for you!");
    }

    file << "// Header files: A lot of them so we never fail to compile.\n";
    file << "#include <iostream>\n#include <unordered_map>\n"
            "#include <vector>\n#include"
            " <unordered_set>\n#include <algorithm>\n"
            "#include <set>\n#include <string>\n#include \"digraph.h\"\n\n";
    file << "using namespace std;\n\nint main() {\n";

    file.close();
}

// Prints the end of the C++ code
void Transpiler::end() {
    // Create a new file object and open
    ofstream file;
    file.open("p++_temp.cpp", ios::app);
    file << "   return 0;\n}\n";
    file.close();
}

// Compiles the C++ code
void Transpiler::compile() {
    if (!supress_print) {
        system\
            ("echo P++ file sucessfully transpiled. Now compiling C++ code.");
    }
    // Compile the C++ code
    system("g++ p++_temp.cpp digraph.cpp -std=c++11 -o program");
    // Remove the C++ code
    if (!debug) {
        system("rm -rf p++_temp.cpp");
    } else if (!supress_print) {
        system("echo I##############################################I");
        system("echo In debug mode, p++_temp.cpp will not be removed.");
        system("echo I##############################################I");
    }

    if (!supress_print) {
        system("echo Done! Run ./program");
    }
}

// Transpiler add id
// We save ids to add context to the transpiler
void Transpiler::add_id(string id, string type) {
    defined_ids.insert({id, type});
}

// Transpiler id lookup
// Only returns true if the name and type are in the unordered map
bool Transpiler::find_id(string id, string type) {
    // Check if the id is in the unordered map
    if (defined_ids.find(id) != defined_ids.end()) {
        // If the id has an item with the same type, return true
        return (defined_ids.find(id)->second == type) ? true : false;
    } else {
        return false;
    }
}

// Continually removes newlines from the lexer queue
void Transpiler::read_until_newl() {
    while (token_list.next().first == "newl") {
        token_list.pop();
    }
}

// Removes the temporary C++ file and closes in case of incorrect
// usage as defined by the transpiler
void Transpiler::fail_close() {
    if (!debug) {
        system("rm -rf p++_temp.cpp");
    }
    exit(EXIT_FAILURE);
}

// Continually appends chains of math expressions together,
// and returns the resulting math expression
string Transpiler::math_expression() {
    // Final return value
    string final;

    // Check if the input is even a math expression to begin with
    if (token_list.next().first != "int" && !(token_list.next().first == "id"
        && this->find_id(token_list.next().second, "int"))) {
        cout << token_list.next().second << endl;
        cout << "Fail in math_expression: Value is not an integer" << endl;
        fail_close();
    }

    // Flag for if the previous value was an integer or not
    bool previous_int = 0;

    // Continually chain together the expressions if they are valid
    while (token_list.next().first == "int" || token_list.next().first == "op"
           || (token_list.next().first == "id"
           && this->find_id(token_list.next().second, "int"))) {
        // If this one is an int, set the flag for next time
        if (token_list.next().first == "int" ||
            token_list.next().first == "id") {
            if (previous_int == 1) {
                // Two ints in a row means we are done with this math expression
                // (Treat the next int as a new math expression)
                return final;
            } else {
                previous_int = 1;
            }
        } else if (previous_int == 1) {
            // If it isn't a number, it is an operator
            previous_int = 0;
        }
        // Add the string to the return value
        final += token_list.next().second;

        // Remove the string from the queue
        token_list.pop();
    }
    // Error cataching for undefined or invalid identifiers
    if (previous_int == 0 && !(token_list.next().first == "id" &&
        this->find_id(token_list.next().second, "int"))) {
        cout << "Fail in math_expression: Tried to use an undefined"
                " or invalid identifier in an expression" << endl;
        fail_close();
    }
    return final;
}

// Continually appends chains of strings together into a single string
string Transpiler::string_expression() {
    //  Final return value
    string final;

    //  Check if the input is even a string to begin with
    if (token_list.next().first != "string" &&
        !(token_list.next().first == "id" &&
        this->find_id(token_list.next().second, "string"))) {
        cout << token_list.next().second << endl;
        cout << "Fail in string_expression: Value is not a string" << endl;
        fail_close();
    }

    //  We handle identifiers first and only once or else we may run into
    //  problems in certain situations
    if (token_list.next().first == "id" &&
       this->find_id(token_list.next().second, "string")) {
        //  Create the next string to insert into the final string
        string next = token_list.next().second;

        //  Pop out the next item
        token_list.pop();

        return next;
    }

    //  Continually read in strings until we reach and endl
    while (token_list.next().first == "string") {
        //  Create the next string to insert into the final string
        string next = token_list.next().second;

        //  Format the string, remove the first and last
        //  " characters to make chaining easier
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
    read_until_newl();  // Pop out all prior newlines
    string final;   // Final return value

    // Check that we are assigning to an identifier
    if (token_list.next().first != "id") {
        cout << token_list.next().first << endl;
        cout << "Error in check_assign:"
                " Only identifiers can be assigned" << endl;
        fail_close();
    }

    // Store the identifier
    string id = token_list.next().second;

    // Pop the identifier
    token_list.pop();

    // Check if we are properly using the assignement operator
    if (token_list.next().second != "=") {
        cout << "Error in check_assign: "
                "Must use = to assign a variable" << endl;
        fail_close();
    }

    // Pop the assignement operator
    token_list.pop();

    // Try to match with digraph object
    if (token_list.next().second == "graph") {
        // If it is defined, simply restate the graph object
        // This will result in a useless expression, but the resulting
        // C++ code will still be valid.
        if (this->find_id(id, "graph")) {
            final = id;
        } else if (this->find_id(id, "int") || this->find_id(id, "string")) {
            // Prevents graph from being reassigned to an int or a string
            cout << "Error: Attempted to reassign a "
                    "graph object to an integer or a string" << endl;
            fail_close();
        } else {
            // Create the digraph object
            final = "Digraph " + id;

            // Add the id to the defined identifiers set
            this->add_id(id, "graph");
        }
    } else if (token_list.next().first == "int" ||
            (token_list.next().first == "id" &&
            this->find_id(token_list.next().second, "int"))) {
            // Try to match with integer/math expression

        // If it's already defined, do not put int in front
        if (this->find_id(id, "int")) {
            final = id + " = ";
        } else if (this->find_id(id, "string") || this->find_id(id, "graph")) {
            // Prevents integer from being reassigned to a graph or a string
            cout << "Error: Attempted to reassign an integer "
                    "object to a graph or a string" << endl;
            fail_close();
        } else {
            // Add the type and the name to the final expression
            final = "int " + id + " = ";

            // Add the id to the defined identifiers set.
            this->add_id(id, "int");
        }
        // Add the math expression to the final return value
        final += math_expression();
    } else if (token_list.next().first == "string" ||
            (token_list.next().first == "id" &&
            this->find_id(token_list.next().second, "string"))) {
            // Try to match with string expression
        // If it's already defined, do not put string in front
        if (this->find_id(id, "string")) {
            final = id + " = ";
        } else if (this->find_id(id, "int") || this->find_id(id, "graph")) {
            // Prevents string from being reassigned to a graph or an integer
            cout << "Error: Attempted to reassign a string "
                    "object to a graph or an integer" << endl;
            fail_close();
        } else {
            // Add the type and the name to the final string
            final = "string " + id + " = ";

            // Add the id to the defined identifiers set.
            this->add_id(id, "string");
        }
        // While loop for adding a string
        while ((token_list.next().first == "id" &&
              this->find_id(token_list.next().second, "string")) ||
              token_list.next().first == "string") {
            // Flag for if the previous value was a string literal
            bool was_string = 0;

            if (token_list.next().first == "string") {
                was_string = 1;
            }

            // Add the string to the assignment
            final += string_expression();

            // Handles formatting for string literal
            // and string identifier combinations
            if ((token_list.next().first == "id" &&
                this->find_id(token_list.next().second, "string")) ||
                token_list.next().first == "string") {
                if (was_string && token_list.next().first == "string") {
                    final += " ";
                } else if (was_string && token_list.next().first == "id") {
                    final += " \" \" + ";
                } else {
                    final += " + \" \" + ";
                }
            }
        }
    } else {
        cout << "Error: Assigning to an invalid token (must be int, "
                "string, or the graph keyword)" << endl;
        fail_close();
    }

    // Add the ; character at the end of the line
    final += ";";

    // Assuming that we got to the newline character, this pops the newline out
    token_list.pop();

    // Open the file, write to it, then close the file
    write_to_file(final);
}

// Handles print statement logic
void Transpiler::print() {
    read_until_newl();  // Pop out all prior newlines

    // Begin building the output
    string final = "cout";
    // Make sure print is the first token
    if (token_list.next().second != "print") {
        cout << "Error in check_print: Function is not print, we got "
        << token_list.next().second << " instead." << endl;
        fail_close();
    }
    // Pop out the print token
    token_list.pop();

    // Make sure the delimiter is the next token
    if (token_list.next().second != ":") {
        cout << "Error in print statement: Invalid syntax." << endl;
        fail_close();
    }
    // Pop out the : token
    token_list.pop();

    // Continually append the strings together
    while (token_list.next().first != "newl") {
        if (token_list.next().second == "print") {
            cout << "Error: Nested print statements are illegal." << endl;
            fail_close();
        } else if (token_list.next().first == "string") {
            // Add the string to the print statement
            final += " << " + string_expression();

            // Add the next print section
            if (token_list.next().first != "newl") {
                final += " << \" \"";
            }
        } else if (token_list.next().first == "id" &&
                  (this->find_id(token_list.next().second, "graph"))) {
            // Check if we are printing a graph method

            // Add graph argument to the print statement
            final += " << " + graph();
            // Add the next print section
            if (token_list.next().first != "newl") {
                final += " << \" \"";
            }
        } else if (token_list.next().first == "int" ||
                  (token_list.next().first == "id" &&
                  (this->find_id(token_list.next().second, "int")))) {
            // Check if we are printing an integer

            // Add integer to the print statements
            final += " << " + math_expression();
            // Add the next print section
            if (token_list.next().first != "newl") {
                final += " << \" \"";
            }
        } else if (token_list.next().first == "id" &&
                 (this->find_id(token_list.next().second, "string"))) {
            // Check if we are printing a string identifier

            // Add the identifier to the print statement
            final += " << " + token_list.next().second;

            // Pop the token out of the queue
            token_list.pop();

            // Add the next print section
            if (token_list.next().first != "newl") {
                final += " << \" \"";
            }
        } else {
            cout << "Error in print statement: Cannot print "
                    "non-string" << token_list.next().second << endl;
            fail_close();
        }
    }
    // Pop out the newl character
    token_list.pop();

    final += " << endl;";

    // Open the file, write to it, then close the file
    write_to_file(final);
}

// Handles graph and graph methods
string Transpiler::graph() {
    read_until_newl();  // Pop out all prior newlines

    string id, final;

    if (token_list.next().first == "id" &&
        this->find_id(token_list.next().second, "graph")) {
        // Get the identifier
        id = token_list.next().second;
        token_list.pop();
    } else {
        cout << "Identifier is undefined or not of type graph: " <<
                token_list.next().second << endl;
        fail_close();
    }
    // Get the method
    string method = token_list.next().second;
    token_list.pop();


    // Messy, but it's because C++ doesn't allow switch statements of string
    // All the stuff below is basic formatting for the return statement
    if (method == "addVertex") {
        string first = token_list.next().second;
        token_list.pop();
        string second = token_list.next().second;
        token_list.pop();

        // Open the file, write to it, then close the file
        final = id + "." + "addVertex" + "(" + first + "," + second + ")";
    } else if (method == "addEdge") {
        string first = token_list.next().second;
        token_list.pop();
        string second = token_list.next().second;
        token_list.pop();

        final = id + "." + "addEdge" + "(" + first + "," + second + ")";
    } else if (method == "getVertex") {
        string first = token_list.next().second;
        token_list.pop();

        return id + "." + "getVertex" + "(" + first + ")";
    } else if (method == "isVertex") {
        string first = token_list.next().second;
        token_list.pop();

        return id + "." + "isVertex" + "(" + first + ")";
    } else if (method == "isEdge") {
        string first = token_list.next().second;
        token_list.pop();
        string second = token_list.next().second;
        token_list.pop();

        return id + "." + "isEdge" + "(" + first + "," + second + ")";
    } else if (method == "numNeighbours") {
        string first = token_list.next().second;
        token_list.pop();

        return id + "." + "numNeighbours" + "(" + first + ")";
    } else if (method == "isWalk") {
        final += id + "." + "isWalk" + "(vector<int>{";
        // Flag for the first iteration of the while loop
        // Makes it so we don't print an extra "," at the start
        bool startflag = 1;
        while (token_list.next().first == "int" ||
              (token_list.next().first == "id" &&
              this->find_id(token_list.next().second, "int"))) {
            // While we have a list of integers, add them to the final value

            string next = token_list.next().second;
            token_list.pop();

            if (startflag == 1) {
                final += next;
                startflag = 0;
            } else {
                final += "," + next;
            }
        }
        final += "})";
        return final;
    } else if (method == "isPath") {
        final += id + "." + "isPath" + "(vector<int>{";
        // Flag for the first iteration of the while loop
        // Makes it so we don't print an extra "," at the start
        bool startflag = 1;
        while (token_list.next().first == "int" ||
              (token_list.next().first == "id" &&
              this->find_id(token_list.next().second, "int"))) {
            // While we have a list of integers, add them to the final value

            string next = token_list.next().second;
            token_list.pop();
            if (startflag == 1) {
                final += next;
                startflag = 0;
            } else {
                final += "," + next;
            }
        }
        final += "})";
        return final;
    } else if (method == "size") {
        return id + "." + "size()";
    } else {
        cout << "Undefined method for graph: " + method << endl;
        fail_close();
    }
    write_to_file(final + ";");

    // If this gets written into our file, it means we
    // made a mistake somewhere with the usage of this function
    return "Error in Digraph Object Method";
}
