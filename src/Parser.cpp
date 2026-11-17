

#include "parser/parser.hpp"
#include <iostream>
#include <sstream>
#include <string_view>
#include <string>
#include <vector>


std::vector<std::string> Parser::parse(std::string input) {
    
    std::istringstream stream{input};

    std::vector<std::string> buffer{};

    std::string token{};
    while ( stream >> token ) {

        buffer.push_back(token);
    }

    return buffer;

}