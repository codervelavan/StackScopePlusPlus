#include <iostream>
#include <string>
#include "evaluator.h"

using namespace std;

int main() {
    string infix;
    cout << "Enter a mathematical expression: ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    int result = evaluatePostfix(postfix);

    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;

    return 0;
}

