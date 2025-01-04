#include "calculator.h"

#include <sstream>
#include "operation_handler.h"

bool Calculator::evaluate_parenthesis() {
    try {
        operation_stack = OperationHandler::evaluate_parenthesis(operation_input);
        return true;
    }catch(std::exception&) {
        return false;
    }
}

void Calculator::simplify_by_operator(const char &_operator) {
    operation_stack = OperationHandler::simplify_by_operator(operation_stack, _operator);
}

void Calculator::calculate() {
    operation_stack = OperationHandler::simplify_operators(operation_stack);
    if (!operation_stack.empty()) {
        result = OperationHandler::join_operation_stack(operation_stack);
        status = STATUS_SUCCESS;
    }else {
        status = STATUS_ERROR;
    }
}

uint8_t Calculator::get_status() const {
    return status;
}

std::string Calculator::get_result() const {
    switch (status) {
        case STATUS_SUCCESS:
            return "\033[34m" + result + "\033[0m";
        case STATUS_ERROR:
            return "\033[31mError in operation\033[0m";
        default:
            return "\033[31mAn unknown error occurred\033[0m";;
    }
}

double Calculator::get_numeric_result() const {
    if (get_status() == STATUS_SUCCESS) {
        return std::stod(result);
    }
    return 0;
}

std::string Calculator::get_result_in_scientific_notation() const {
    if (get_status() == STATUS_SUCCESS) {
        std::ostringstream oss;
        oss << std::scientific << std::stod(result);
        return oss.str();
    }

    return get_result();
}
