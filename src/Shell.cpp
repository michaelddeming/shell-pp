
#include "shell/Shell.hpp"
#include <iostream>
#include <string>
#include <string_view>

bool Shell::check_input(std::string_view input) {

    if (input == "exit") {
        std::cout << "Goodbye!" << "\n";
        return true;
    }
    else {
        std::cout << "Invalid command!" << "\n";
        return false;
    }
}

void Shell::run() {

    std::string input{};

    while (std::cout << m_prompt, std::getline(std::cin, input)) {        

        if (check_input(input)) break;
    }
}