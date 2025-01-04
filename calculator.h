#pragma once

#include <iostream>
#include <vector>

class Calculator {
public:
    static constexpr uint8_t STATUS_UNKNOWN = 0;
    static constexpr uint8_t STATUS_SUCCESS = 1;
    static constexpr uint8_t STATUS_ERROR = 2;

    std::vector<std::string> operation_stack = {};
    std::string operation_input;
    std::string result = "Error";
    uint8_t status = STATUS_UNKNOWN;

    explicit Calculator(std::string operation): operation_input(std::move(operation)) {};
    ~Calculator()= default;

    bool evaluate_parenthesis();
    void calculate();
    [[nodiscard]] uint8_t get_status() const;
    [[nodiscard]] std::string get_result() const;
    [[nodiscard]] double get_numeric_result() const;
    [[nodiscard]] std::string get_result_in_scientific_notation() const;
private:
    void simplify_by_operator(const char &);
};