#pragma once

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <optional>
#include <shared_mutex>

class Table {
private:
    std::map<int, std::string> data_;
    mutable std::shared_mutex mutex_;
    std::string name_;

public:
    explicit Table(std::string name);
    
    bool insert(int id, const std::string& name);
    void truncate();
    std::optional<std::string> get(int id) const;
    const std::map<int, std::string>& get_all() const;
    bool contains(int id) const;
    const std::string& get_name() const { return name_; }
};