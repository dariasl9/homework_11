#include "database.hpp"
#include <mutex>

Table::Table(std::string name) : name_(std::move(name)) {}

bool Table::insert(int id, const std::string& name) {
    std::unique_lock lock(mutex_);
    auto [it, inserted] = data_.emplace(id, name);
    return inserted;
}

void Table::truncate() {
    std::unique_lock lock(mutex_);
    data_.clear();
}

std::optional<std::string> Table::get(int id) const {
    std::shared_lock lock(mutex_);
    auto it = data_.find(id);
    if (it != data_.end()) return it->second;
    return std::nullopt;
}

const std::map<int, std::string>& Table::get_all() const {
    std::shared_lock lock(mutex_);
    return data_;
}

bool Table::contains(int id) const {
    std::shared_lock lock(mutex_);
    return data_.find(id) != data_.end();
}