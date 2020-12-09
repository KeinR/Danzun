#include <iostream>

#include "extern/arashpartow/exprtk.hpp"


int main() {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    symbol_table_t symbol_table;
    expression_t expression;
    parser_t parser;

    const char *code = R"(
        x := 424
        return 22
    )";

    parser.compile(code, expression);

    expression.register_symbol_table(symbol_table);

    std::cout << expression.value() << '\n';
    std::cout << expression.get_symbol_table(0).get_variable("x") << '\n';

    return 0;
}
