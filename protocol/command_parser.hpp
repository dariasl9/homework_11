#pragma once

#include <string>
#include <vector>

struct Command {
    enum class Type {
        INSERT,
        TRUNCATE,
        INTERSECTION,
        SYMMETRIC_DIFFERENCE,
        UNKNOWN
    };
    
    Type type;
    std::vector<std::string> args;
};

class CommandParser {
public:
    static Command parse(const std::string& input);
};