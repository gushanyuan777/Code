#include "expression_evaluator.h"
#include <cctype>
#include <cmath>
#include <stack>
#include <iostream>
#include <sstream>

// Utility function to check if the character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Utility function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Utility function to perform the operation based on the operator
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw DivisionByZeroException();
            return a / b;
    }
    return 0;
}

// Function to evaluate the expression inside the parentheses
double evaluate(const std::string &expr, size_t &index) {
    std::stack<double> values;
    std::stack<char> ops;
    int balance = 0;

    while (index < expr.length()) {
        char c = expr[index];

        if (std::isspace(c)) {
            ++index;
            continue;
        }

        if (isdigit(c) || c == '.') {
            std::string num;
            while (index < expr.length() && (isdigit(expr[index]) || expr[index] == '.')) {
                num += expr[index++];
            }
            if (num.empty()) throw IllegalExpressionException();
            values.push(std::stod(num));
        } else if (isOperator(c)) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(c);
            ++index;
        } else if (c == '(') {
            ops.push(c);
            balance++;
            ++index;
        } else if (c == ')') {
            if (balance == 0) throw IllegalExpressionException();
            balance--;
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            if (!ops.empty() && ops.top() != '(') throw IllegalExpressionException();
            if (!ops.empty()) ops.pop(); // Remove the '(' from the stack
            ++index;
        } else {
            throw IllegalExpressionException();
        }
    }

    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    if (balance != 0) throw IllegalExpressionException(); // Check for unmatched parentheses

    return values.empty() ? 0 : values.top();
}

bool isLegalExpression(const std::string& expr) {
    std::stack<char> s;
    int balance = 0;
    bool lastWasOperator = false;

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (std::isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            if (lastWasOperator && i == 0) return false; // Expression starts with an operator
            lastWasOperator = false;
        } else if (isOperator(c)) {
            if (lastWasOperator) return false; // Consecutive operators
            lastWasOperator = true;
        } else if (c == '(') {
            if (lastWasOperator) {
                s.push(c);
                balance++;
            } else {
                return false; // '(' not after a number/operator
            }
        } else if (c == ')') {
            if (balance == 0) return false; // Unmatched ')'
            if (lastWasOperator) return false; // ')' after an operator
            balance--;
            s.pop();
            lastWasOperator = false;
        } else {
            return false; // Invalid character
        }
    }
    return balance == 0 && !lastWasOperator; // Check for unmatched parentheses and operator at the end
}

double evaluateExpression(const std::string& expr) {
    if (!isLegalExpression(expr)) throw IllegalExpressionException();
    size_t index = 0;
    return evaluate(expr, index);
}