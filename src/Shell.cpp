
#include "shell/Shell.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <unistd.h>

int Shell::execute_external(std::vector<std::string> ibuffer) {

    pid_t pid = fork();

        if (pid < 0) {

            // ERROR
            perror("execvp");
            return -1;
        }

        else if (pid == 0) {
            
            std::vector<char*> argv;

            int n = ibuffer.size();

            for (int i = 0; i < n; i++) {
                argv.push_back(ibuffer[i].data());
            }

            argv.push_back(nullptr);


            //child process
            execvp(ibuffer[0].c_str(), argv.data());

            perror("execvp");
            _exit(127);
        }

        else { 
            
            //parent
            waitpid(pid, nullptr, 0);
            return 0;
        }
}

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

    else if (
        ibuffer[0] == "ls" ||
        ibuffer[0] == "pwd"
        ) {

        int res = Shell::execute_external(ibuffer);
        return res;
        
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