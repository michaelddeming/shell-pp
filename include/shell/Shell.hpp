
#pragma once

#include "parser/parser.hpp"
#include <string_view>
#include <string>
class Shell {
public:
    void run();
    bool check_input(std::string input);

private:
    std::string_view m_prompt{"shell++ | "};
    Parser parser{};
};