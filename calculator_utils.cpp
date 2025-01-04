#include "calculator_utils.h"
#include <thread>

bool CalculatorUtils::is_digit(const std::string& s){
    auto it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || *it == '.')) ++it;
    return !s.empty() && it == s.end();
}

bool CalculatorUtils::is_valid_operator_or_digit(const std::string& s) {
    return is_digit(s) || is_valid_operator(s);
}

bool CalculatorUtils::is_valid_operator_or_digit(const char& s) {
    return isdigit(s) || is_valid_operator(s) || s == '.';
}

inline bool CalculatorUtils::is_valid_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^";
}

inline bool CalculatorUtils::is_valid_operator(const char& s) {
    return s == '+' || s == '-' || s == '*' || s == '/' || s == '%' || s == '^';
}

bool CalculatorUtils::has_repeated_operators(const std::string& s) {
    const auto begin = s.begin();
    const auto end = s.end();

    if (s.length() < 2) return false;

    for (auto it = begin + 1; it != end; ++it) {
        if (isdigit(*it)) continue;
        if (*it == '(' || *it == ')') continue;

        if (is_valid_operator(*it) && is_valid_operator(*(it - 1))) {
            return true;
        }
    }

    return false;
}

bool CalculatorUtils::has_invalid_symbols(const std::string& s) {
    const auto begin = s.begin();
    const auto end = s.end();

    for (auto it = begin; it != end; ++it) {
        if (!is_valid_operator_or_digit(*it) && *it != '(' && *it != ')') return true;
    }

    return false;
}

float CalculatorUtils::perform_operation_on_strings(const std::string &a, const std::string &b, const char &_operator) {
    float afloat = std::atof(a.c_str());
    float bfloat = std::atof(b.c_str());

    switch (_operator) {
        case '^':
            return std::pow(afloat, bfloat);
        case '*':
            return afloat * bfloat;
        case '/':
            return afloat / bfloat;
        case '+':
            return afloat + bfloat;
        case '-':
            return afloat - bfloat;
        case '%':
            return fmod(std::stof(a), std::stof(b));
        default:
            return 0;
    }
}