
#pragma once

#include "parser/parser.hpp"
#include <string_view>
#include <string>

class Shell {
public:
    void run();
    bool check_input(std::string input);
    int execute_external(std::vector<std::string> ibuffer);

private:
    std::string_view m_prompt{"shell++ | "};
    Parser parser{};
};