#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>

// Converts an infix expression (e.g., "3 + 4 * 2") to postfix (e.g., "3 4 2 * +")
std::string infixToPostfix(const std::string& infix);

// Evaluates a postfix expression (e.g., "3 4 2 * +") and returns the result
int evaluatePostfix(const std::string& postfix);

#endif // EVALUATOR_H
