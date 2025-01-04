#pragma once

#include <iostream>

class ParenthesisHandler {
    const std::string PARENTHESIS_MULTIPLICATION_TOKEN = "*";

    using StringVector = std::vector<std::string>;

    StringVector parentheses_stack = {};
    StringVector output_operation_stack = {};
    StringVector nested_operation_stack = {};

    std::string current_operation, working_operation;
    const std::string &input;
public:
    explicit ParenthesisHandler(const std::string& input) : input(input){}
    ~ParenthesisHandler()= default;

    void handle_open_parenthesis(size_t);
    void handle_closed_parenthesis(size_t);

    StringVector process();
};