
#include "shell/Shell.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

bool Shell::check_input(std::string input) {

    std::vector<std::string> ibuffer = Shell::parser.parse(input);

    if (ibuffer[0] == "exit") {
        std::cout << "Goodbye!" << "\n";
        return true;
    }

    else if (ibuffer[0] == "test") {
        
        int n = ibuffer.size();

        for (int i = 0; i < n; i++) {
            std::cout << ibuffer[i] << "\n";
        }
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