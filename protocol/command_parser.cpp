#include "command_parser.hpp"
#include <sstream>

Command CommandParser::parse(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(std::move(token));
    }
    
    if (tokens.empty()) {
        return {Command::Type::UNKNOWN, {}};
    }
    
    std::string cmd = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());
    
    if (cmd == "INSERT") return {Command::Type::INSERT, args};
    if (cmd == "TRUNCATE") return {Command::Type::TRUNCATE, args};
    if (cmd == "INTERSECTION") return {Command::Type::INTERSECTION, args};
    if (cmd == "SYMMETRIC_DIFFERENCE") return {Command::Type::SYMMETRIC_DIFFERENCE, args};
    
    return {Command::Type::UNKNOWN, {}};
}