#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <exception>

class DivisionByZeroException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Division by zero error";
    }
};

class IllegalExpressionException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Illegal expression";
    }
};

bool isLegalExpression(const std::string& expr);
double evaluateExpression(const std::string& expr);

#endif // EXPRESSION_EVALUATOR_H