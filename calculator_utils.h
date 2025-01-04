#pragma once
#include <iostream>

class CalculatorUtils {
public:
    CalculatorUtils()= default;
    ~CalculatorUtils()= default;

    static bool is_digit(const std::string&);

    static bool is_valid_operator_or_digit(const std::string&);
    static bool is_valid_operator_or_digit(const char& s);

    static inline bool is_valid_operator(const std::string&);
    static inline bool is_valid_operator(const char&);

    static bool has_repeated_operators(const std::string&);
    static bool has_invalid_symbols(const std::string&);

    static float perform_operation_on_strings(const std::string&, const std::string&, const char&);
};