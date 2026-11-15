
#pragma once

#include <string_view>

class Shell {
public:
    void run();
    bool check_input(std::string_view input);

private:
    std::string_view m_prompt{"shell++ | "};
};