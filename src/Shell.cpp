
#include "shell/Shell.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>

int Shell::execute_external(std::vector<std::string> ibuffer)
{
    if (ibuffer.empty())
        return -1;

    pid_t pid = fork();

    if (pid < 0)
    {

        // ERROR
        perror("fork");
        return -1;
    }

    else if (pid == 0)
    {

        std::vector<char *> argv;

        int n = ibuffer.size();

        for (int i = 0; i < n; i++)
        {
            argv.push_back(ibuffer[i].data());
        }

        argv.push_back(nullptr);

        // child process
        execvp(ibuffer[0].c_str(), argv.data());

        perror(ibuffer[0].c_str());
        _exit(127);
    }

    else
    {

        // parent
        int status{};
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return -1;
        }
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }

        if (WIFSIGNALED(status))
        {
            return 128 + WTERMSIG(status);
        }

        return -1;
    }
}

bool Shell::check_input(std::string input)
{

    std::vector<std::string> ibuffer = Shell::parser.parse(input);

    if (ibuffer.empty())
        return false;

    if (ibuffer[0] == "exit")
    {
        std::cout << "Goodbye!" << "\n";
        return true;
    }

    else if (ibuffer[0] == "test")
    {

        int n = ibuffer.size();
        std::cout << "Test... printing buffer: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << ibuffer[i] << "\n";
        }
        return false;
    }

    else
    {
        int res = Shell::execute_external(ibuffer);

        if (res == -1)
        {
            return false;
        }

        if (res == 127)
        {
            std::cout << "Command could not be executed.\n";
        }
        else if (res != 0)
        {
            std::cout << "Command exited with status: " << res << "\n";
        }

        return false;
    }
}

void Shell::run()
{

    std::string input{};

    while (std::cout << m_prompt, std::getline(std::cin, input))
    {

        if (check_input(input))
            break;
    }
}