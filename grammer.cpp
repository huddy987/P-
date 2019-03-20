// Functions here define the grammer specified in the readme
#include <utility>
#include <iostream>
#include "lexer.h"
#include <stdlib.h>
#include <string>

string check_math(lexer &token_list) {
    // TODO: RICHMOND
    return "0"; // just for now so stuff compiles
}

// Continually appends chains of strings together into a single string
string check_string(lexer &token_list) {
    string final;
    // Continually read in strings until we reach and endl
    while(token_list.next().first != "newl") {
        if(token_list.next().first != "string") {
            cout << "Error in check_string: Only strings can be used here" << endl;
            cout << "Maybe you tried to chain some strings together halfway through a line?" << endl;
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

string check_assign(lexer &token_list) {
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
        // Add the type and the name to the final string
        final = "int " + id + " = ";
        // TODO: evaulate integer expression
        final += check_math(token_list);
    }
    else if(token_list.next().first == "string") {
        // Add the type and the name to the final string
        final = "string " + id + " = ";
        // Add the string to the assignment
        final += check_string(token_list);
    }
    else {
        cout << token_list.next().first << endl;
        cout << "Error: Assigning to an invalid token (must be int or string)" << endl;
        exit(EXIT_FAILURE);
    }
    return final;
}
string check_print(lexer &token_list) {
    string final = "cout";
    if(token_list.next().second != "print") {
        cout << "Error in check_print: Function is not print." << endl;
        exit(EXIT_FAILURE);
    }
    // Pop out the print token
    token_list.pop();
    if(token_list.next().second != ":") {
        cout << "Error in print statement: Invalid syntax." << endl;
        exit(EXIT_FAILURE);
    }
    // Pop out the : token
    token_list.pop();

    while(token_list.next().first != "newl") {
        if(token_list.next().second == "print") {
            cout << "Error: Nested print statements are illegal." << endl;
            exit(EXIT_FAILURE);
        }
        else if(token_list.next().first != "string") {
            // TODO: Allow numbers to be printed as well?
            cout << token_list.next().first << endl;
            cout << "Error: Must print a string." << endl;
            exit(EXIT_FAILURE);
        }
        final += " << " + token_list.next().second;
        // Pop the string out of the queue
        token_list.pop();
    }
    final += " << endl;";
    // Pop the newline character out of the queue
    return final;
}


int main() {
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test.p");
    while(true) {
        cout << check_assign(token_test) << endl;
    }
}
