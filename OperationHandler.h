#pragma once
#include <iostream>

class OperationHandler {
public:
    OperationHandler()= default;
    ~OperationHandler()= default;

    using StringVector = std::vector<std::string>;

    static std::string join_operation_stack(const StringVector&);

    static uint count_of_numbers_operated(const std::string&);
    static bool contains_operator(const std::string&, const char&);
    static bool contains_operators_in_string(const std::string&, const std::vector<char>&);
    static bool contains_operator_in_stack(const StringVector &, const char &);
    static char get_first_in_precedence(const std::string&, const std::vector<char>&);
    static StringVector evaluate_parenthesis(const std::string &);
    static StringVector simplify_by_operator(StringVector&, const char&);
    static StringVector tokenize_operation(const std::string&);
    static std::string simplify_by_operator(const std::string&, const char&);
    static std::string simplify_operators(std::string);
    static StringVector simplify_operators(StringVector);
};