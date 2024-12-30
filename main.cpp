#include <iostream>
#include "Calculator.h"
#include "CalculatorUtils.h"

void trim_string(std::string &str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

int main() {
    std::string operation;

    std::cout << "Enter desired math operation: " << std::endl;

    std::getline(std::cin, operation);
    trim_string(operation);

    Calculator calc(operation);

    if (CalculatorUtils::has_invalid_symbols(operation)) {
        std::cout << "Syntax error: invalid operators in operation" << std::endl;
        return 1;
    }

    if (CalculatorUtils::has_repeated_operators(operation)) {
        std::cout << "Syntax error: repeated consecutive operators, try using parenthesis to separate operators" << std::endl;
        return 1;
    }

    if (!calc.evaluate_parenthesis()) {
        std::cout << "Syntax error: unclosed parenthesis" << std::endl;
        return 1;
    }

    calc.calculate();
    std::cout << calc.get_result();

    return 0;
}
