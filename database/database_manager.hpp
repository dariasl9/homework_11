#pragma once

#include "database.hpp"
#include <memory>
#include <vector>

class DatabaseManager {
public:
    enum class TableId { A, B };
    
    DatabaseManager();
    
    bool insert(TableId table, int id, const std::string& name);
    void truncate(TableId table);
    
    std::vector<std::tuple<int, std::string, std::string>> intersection() const;
    std::vector<std::tuple<int, std::string, std::string>> symmetric_difference() const;

private:
    std::unique_ptr<Table> table_a_;
    std::unique_ptr<Table> table_b_;
    mutable std::shared_mutex mutex_;
    
    Table* get_table(TableId table);
    const Table* get_table(TableId table) const;
};