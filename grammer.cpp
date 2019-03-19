// Functions here define the grammer specified in the readme
#include <utility>
#include <iostream>
#include "lexer.h"
#include <stdlib.h>

string check_math(lexer &token_list) {
    // TODO: RICHMOND
    
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

    while(token_list.next().first != "newl") {
        if(token_list.next().first == "int") {
            // TODO: evaulate integer expression
            final += "bruh";
        }
        else if(token_list.next().first == "string") {
            // Add the string to the assignment
            final += "string " + id + " = " + token_list.next().second;
            // Pop the string off of the queue
            token_list.pop();
        }
        else {
            cout << token_list.next().first << endl;
            cout << "Error: Assigning to an invalid token (must be int or string)" << endl;
            exit(EXIT_FAILURE);
        }
    }
    // Pop out the newline character
    token_list.pop();
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
