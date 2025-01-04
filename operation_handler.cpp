#include <numeric>
#include "operation_handler.h"

#include <thread>

#include "calculator_utils.h"
#include "parenthesis_handler.h"

std::string OperationHandler::join_operation_stack(const StringVector &operation_stack) {
    return std::accumulate(operation_stack.begin(), operation_stack.end(), std::string{});
}

uint OperationHandler::count_of_numbers_operated(const std::string &operation) {
    const auto count = std::ranges::count_if(operation, [](const char o) {
        return CalculatorUtils::is_valid_operator(o);
    });
    return std::isdigit(operation.front()) && std::isdigit(operation.back()) && count > 0 ? count + 1 : count;
}

bool OperationHandler::contains_operator(const std::string &operation, const char &_operator) {
    return std::ranges::find(operation, _operator) != operation.end();
}

bool OperationHandler::contains_operators_in_string(const std::string &operation, const std::vector<char>& operators) {
    return std::ranges::any_of(operators, [&](const char _operator) {
        return contains_operator(operation, _operator);
    });
}

bool OperationHandler::contains_operator_in_stack(const StringVector &operation_stack, const char &_operator) {
    return std::ranges::any_of(operation_stack, [&](const std::string operation) {
        return contains_operator(operation, _operator);
    });
}

char OperationHandler::get_first_in_precedence(const std::string &operation, const std::vector<char> &operators) {
    char first = NULL;
    int last_precedence = std::numeric_limits<int>::max();

    for (const char _operator : operators) {
        for (int i = 0; i < operation.length(); i++) {
            const char curr_char = operation[i];
            if (CalculatorUtils::is_valid_operator(curr_char) && i == 0) {
                continue;
            }
            if (_operator == curr_char && i < last_precedence) {
                first = curr_char;
                last_precedence = i;
                break;
            }
        }
    }

    return first;
}

OperationHandler::StringVector OperationHandler::evaluate_parenthesis(const std::string &input) {
    return ParenthesisHandler(input).process();
}

OperationHandler::StringVector OperationHandler::simplify_by_operator(StringVector &operation_stack, const char &_operator) {
    for (auto & operation : operation_stack) {
        if (count_of_numbers_operated(operation) <= 1) continue;

        while (contains_operator(operation, _operator)) {
            operation = simplify_by_operator(operation, _operator);
        }
    }

    return operation_stack;
}

OperationHandler::StringVector OperationHandler::tokenize_operation(const std::string &operation) {
    StringVector tokens;
    std::string tokenization;

    int i = 0;
    for (const auto &curr_char : operation) {
        if (const std::string curr_char_str(1, curr_char); CalculatorUtils::is_digit(curr_char_str)) {
            tokenization += curr_char_str;
        }else if (CalculatorUtils::is_valid_operator(curr_char_str)) {
            if (i == 0) {
                tokenization += curr_char_str;
            }else {
                tokens.push_back(tokenization);
                tokens.push_back(curr_char_str);
                tokenization = "";
            }
        }
        i++;
    }

    if (!tokenization.empty()) {
        tokens.push_back(tokenization);
    }

    return tokens;
}

std::string OperationHandler::simplify_by_operator(const std::string &operation, const char &_operator) {
    if (count_of_numbers_operated(operation) <= 1) {
        return operation;
    }

    const StringVector separated_operation_stack = tokenize_operation(operation);
    const size_t stack_size = separated_operation_stack.size();

    std::string operation_result;

    for (size_t i = 0; i < stack_size;) {
        const std::string& token1 = separated_operation_stack[i];
        const std::string& token2 = i + 1 < stack_size ? separated_operation_stack[i + 1] : "";
        const std::string& token3 = i + 2 < stack_size ? separated_operation_stack[i + 2] : "";

        if (!token2.empty() && token2[0] == _operator) {
            const float result = CalculatorUtils::perform_operation_on_strings(token1, token3, token2[0]);
            operation_result += std::to_string(result);
            i += 3;
        } else {
            operation_result += token1;
            if (i + 1 >= stack_size) break;
            operation_result += token2;
            i += 2;
        }
    }

    if (operation_result.empty()) {
        return operation;
    }
    return operation_result;
}

std::string OperationHandler::simplify_operators(std::string operation) {
    if (count_of_numbers_operated(operation) > 1) {
        while (count_of_numbers_operated(operation) > 1 && contains_operator(operation, '^')) {
            operation = simplify_by_operator(operation, '^');
        }

        auto operators = {'*', '/', '%'};
        while (count_of_numbers_operated(operation) > 1 && contains_operators_in_string(operation, operators)) {
            if (const char first = get_first_in_precedence(operation, operators); first != NULL) {
                operation = simplify_by_operator(operation, first);
            }
        }

        operators = {'+', '-'};
        while (count_of_numbers_operated(operation) > 1 && contains_operators_in_string(operation, operators)) {
            if (const char first = get_first_in_precedence(operation, operators); first != NULL) {
                operation = simplify_by_operator(operation, first);
            }
        }
    }

    return operation;
}

OperationHandler::StringVector OperationHandler::simplify_operators(StringVector operation_stack) {
    if (const std::string operation = simplify_operators(join_operation_stack(operation_stack)); !operation.empty()) {
        return tokenize_operation(operation);
    }
    return operation_stack;
}
