#include <iostream>
#include <string>
#include "expression_evaluator.h"

int main() {
    std::string expression;
    std::cout << "请输入一个中缀表达式：";
    std::getline(std::cin, expression); // 使用getline以支持空格

    if (isLegalExpression(expression)) {
        try {
            double result = evaluateExpression(expression);
            std::cout << "计算结果：" << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "发生错误：" << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cout << "ILLEGAL" << std::endl;
    }

    return 0;
}