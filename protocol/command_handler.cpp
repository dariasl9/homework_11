#include "command_handler.hpp"
#include <stdexcept>

CommandHandler::CommandHandler(DatabaseManager& db) : db_(db) {}

std::string CommandHandler::handle(const std::string& input) {
    auto cmd = CommandParser::parse(input);
    
    try {
        switch (cmd.type) {
            case Command::Type::INSERT:
                return handle_insert(cmd.args);
            case Command::Type::TRUNCATE:
                return handle_truncate(cmd.args);
            case Command::Type::INTERSECTION:
                return handle_intersection();
            case Command::Type::SYMMETRIC_DIFFERENCE:
                return handle_symmetric_difference();
            case Command::Type::UNKNOWN:
            default:
                return "ERR Unknown command\n";
        }
    } catch (const std::exception& e) {
        return "ERR " + std::string(e.what()) + "\n";
    }
}

DatabaseManager::TableId CommandHandler::parse_table_id(const std::string& table_str) {
    if (table_str == "A") return DatabaseManager::TableId::A;
    if (table_str == "B") return DatabaseManager::TableId::B;
    throw std::invalid_argument("Unknown table");
}

std::string CommandHandler::handle_insert(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        return "ERR Invalid number of arguments for INSERT\n";
    }
    
    auto table = parse_table_id(args[0]);
    int id;
    try {
        id = std::stoi(args[1]);
    } catch (...) {
        return "ERR Invalid id format\n";
    }
    
    const auto& name = args[2];
    
    if (db_.insert(table, id, name)) {
        return "OK\n";
    } else {
        return "ERR duplicate " + std::to_string(id) + "\n";
    }
}

std::string CommandHandler::handle_truncate(const std::vector<std::string>& args) {
    if (args.size() != 1) {
        return "ERR Invalid number of arguments for TRUNCATE\n";
    }
    
    auto table = parse_table_id(args[0]);
    db_.truncate(table);
    return "OK\n";
}

std::string CommandHandler::handle_intersection() {
    auto result = db_.intersection();
    std::string response;
    for (const auto& [id, a, b] : result) {
        response += std::to_string(id) + "," + a + "," + b + "\n";
    }
    response += "OK\n";
    return response;
}

std::string CommandHandler::handle_symmetric_difference() {
    auto result = db_.symmetric_difference();
    std::string response;
    for (const auto& [id, a, b] : result) {
        response += std::to_string(id) + "," + a + "," + b + "\n";
    }
    response += "OK\n";
    return response;
}