#pragma once

#include "command_parser.hpp"
#include "database_manager.hpp"
#include <string>

class CommandHandler {
public:
    explicit CommandHandler(DatabaseManager& db);
    std::string handle(const std::string& input);

private:
    DatabaseManager& db_;
    
    DatabaseManager::TableId parse_table_id(const std::string& table_str);
    std::string handle_insert(const std::vector<std::string>& args);
    std::string handle_truncate(const std::vector<std::string>& args);
    std::string handle_intersection();
    std::string handle_symmetric_difference();
};