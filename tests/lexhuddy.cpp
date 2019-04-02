#include "../lexer.h"
#include <iostream>

using namespace std;
int main(){
    // Example usage of the class
    lexer token_test;

    token_test = tokenize_file("test.p");

    while(true) {
      cout << token_test.next().first << " " << token_test.next().second << endl;
      token_test.pop();
    }

    // Comparing tokens
    return 0;
}
