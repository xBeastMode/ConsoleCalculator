#include "parenthesis_handler.h"
#include "calculator_utils.h"
#include "operation_handler.h"

void ParenthesisHandler::handle_open_parenthesis(const size_t i) {
    if (!current_operation.empty()) {
        if(!CalculatorUtils::is_valid_operator(current_operation.back())) {
            current_operation += PARENTHESIS_MULTIPLICATION_TOKEN;
        }

        if (parentheses_stack.empty()) {
            output_operation_stack.push_back(current_operation);
            current_operation = "";
        }else {
            nested_operation_stack.push_back(current_operation);
            current_operation = "";
        }
    }

    if (i > 0 && input[i - 1] == ')') {
        nested_operation_stack.push_back(PARENTHESIS_MULTIPLICATION_TOKEN);
    }

    parentheses_stack.emplace_back("(");
    nested_operation_stack.emplace_back("(");
}

void ParenthesisHandler::handle_closed_parenthesis(const size_t i) {
    std::string _operation, _operator;

    while (true) {
        if (nested_operation_stack.empty()) break;

        const std::string nested_operation = nested_operation_stack.back();

        if (nested_operation.empty()) continue;

        if (nested_operation == "(") {
            parentheses_stack.pop_back();
            nested_operation_stack.pop_back();

            if (!nested_operation_stack.empty() && CalculatorUtils::is_valid_operator(nested_operation_stack.back())) {
                _operator = nested_operation_stack.back();
                nested_operation_stack.pop_back();
            }
            break;
        }

        _operation = nested_operation;
        nested_operation_stack.pop_back();
    }

    if (!current_operation.empty()) {
        if (!_operator.empty() && !working_operation.empty()) {
            working_operation = OperationHandler::simplify_operators(current_operation) + _operator + working_operation;
            working_operation = OperationHandler::simplify_operators(working_operation);
        }else {
            working_operation += current_operation;
        }
        current_operation = "";
    }

    if (!_operation.empty()) {
        working_operation = _operation + working_operation;
    }

    working_operation = OperationHandler::simplify_operators(working_operation);

    if (parentheses_stack.empty()) {
        nested_operation_stack.clear();
        output_operation_stack.push_back(working_operation);

        working_operation = "";

        if (i < input.length() - 1 && !CalculatorUtils::is_valid_operator(input[i + 1])) {
            output_operation_stack.push_back(PARENTHESIS_MULTIPLICATION_TOKEN);
        }
    }
}

ParenthesisHandler::StringVector ParenthesisHandler::process() {
    for(int i = 0; i < input.length(); i++) {
        std::string curr_char(1, input[i]);
        if (CalculatorUtils::is_valid_operator_or_digit(curr_char)) {
            current_operation += curr_char;
            continue;
        }

        if (curr_char == "(") {
            handle_open_parenthesis(i);
        }else if(curr_char == ")") {
            handle_closed_parenthesis(i);
        }
    }

    if (!parentheses_stack.empty()) {
        throw std::runtime_error("Syntax error: unclosed parenthesis");
    }

    if (!current_operation.empty()) {
        output_operation_stack.push_back(current_operation);
        current_operation = "";
    }

    output_operation_stack = OperationHandler::simplify_operators(output_operation_stack);

    return output_operation_stack;
}