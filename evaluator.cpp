#include "evaluator.h"
#include <stack>
#include <cctype>
#include <sstream>
#include <iostream>

using std::stack;
using std::string;
using std::stringstream;
using std::isdigit;

//  HReturns precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Checks if character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Infix → Postfix
string infixToPostfix(const string& infix) {
    stack<char> operators;
    stringstream output;

    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];

        // 🔢 If digit, read full number
        if (isdigit(ch)) {
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                output << infix[i];
                i++;
            }
            output << ' ';
            i--; // adjust for outer loop
        }
        // 🅰️ If '(', push to stack
        else if (ch == '(') {
            operators.push(ch);
        }
        // 🔚 If ')', pop until '('
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output << operators.top() << ' ';
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // Pop '('
        }
        // ➕➖ Operators
        else if (isOperator(ch)) {
            while (!operators.empty() &&
                   precedence(operators.top()) >= precedence(ch)) {
                output << operators.top() << ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // 🧹 Pop any remaining operators
    while (!operators.empty()) {
        output << operators.top() << ' ';
        operators.pop();
    }

    return output.str();
}

// 📤 Evaluate Postfix
int evaluatePostfix(const string& postfix) {
    stack<int> stk;
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        // 🔢 If number, push to stack
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            stk.push(std::stoi(token));
        }
        // ➕➖ If operator, pop two and evaluate
        else if (isOperator(token[0])) {
            if (stk.size() < 2) {
                std::cerr << "Error: Invalid expression" << std::endl;
                return 0;
            }

            int right = stk.top(); stk.pop();
            int left = stk.top(); stk.pop();
            int result = 0;

            switch (token[0]) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/':
                    if (right == 0) {
                        std::cerr << "Error: Division by zero" << std::endl;
                        return 0;
                    }
                    result = left / right;
                    break;
            }
            stk.push(result);
        }
    }

    return stk.empty() ? 0 : stk.top();
}

