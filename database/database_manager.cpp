#include "database_manager.hpp"
#include <algorithm>
#include <mutex>

DatabaseManager::DatabaseManager() 
    : table_a_(std::make_unique<Table>("A"))
    , table_b_(std::make_unique<Table>("B")) {}

bool DatabaseManager::insert(TableId table, int id, const std::string& name) {
    std::unique_lock lock(mutex_);
    Table* t = get_table(table);
    return t->insert(id, name);
}

void DatabaseManager::truncate(TableId table) {
    std::unique_lock lock(mutex_);
    Table* t = get_table(table);
    t->truncate();
}

std::vector<std::tuple<int, std::string, std::string>> 
DatabaseManager::intersection() const {
    std::shared_lock lock(mutex_);
    std::vector<std::tuple<int, std::string, std::string>> result;
    
    const auto& data_a = table_a_->get_all();
    const auto& data_b = table_b_->get_all();
    
    auto it_a = data_a.begin();
    auto it_b = data_b.begin();
    
    while (it_a != data_a.end() && it_b != data_b.end()) {
        if (it_a->first == it_b->first) {
            result.emplace_back(it_a->first, it_a->second, it_b->second);
            ++it_a;
            ++it_b;
        } else if (it_a->first < it_b->first) {
            ++it_a;
        } else {
            ++it_b;
        }
    }
    
    return result;
}

std::vector<std::tuple<int, std::string, std::string>> 
DatabaseManager::symmetric_difference() const {
    std::shared_lock lock(mutex_);
    std::vector<std::tuple<int, std::string, std::string>> result;
    
    const auto& data_a = table_a_->get_all();
    const auto& data_b = table_b_->get_all();
    
    auto it_a = data_a.begin();
    auto it_b = data_b.begin();
    
    while (it_a != data_a.end() && it_b != data_b.end()) {
        if (it_a->first == it_b->first) {
            ++it_a;
            ++it_b;
        } else if (it_a->first < it_b->first) {
            result.emplace_back(it_a->first, it_a->second, "");
            ++it_a;
        } else {
            result.emplace_back(it_b->first, "", it_b->second);
            ++it_b;
        }
    }
    
    while (it_a != data_a.end()) {
        result.emplace_back(it_a->first, it_a->second, "");
        ++it_a;
    }
    
    while (it_b != data_b.end()) {
        result.emplace_back(it_b->first, "", it_b->second);
        ++it_b;
    }
    
    return result;
}

Table* DatabaseManager::get_table(TableId table) {
    return (table == TableId::A) ? table_a_.get() : table_b_.get();
}

const Table* DatabaseManager::get_table(TableId table) const {
    return (table == TableId::A) ? table_a_.get() : table_b_.get();
}