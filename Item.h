#pragma once

#include <string>

class Item {
public:
    Item() : name("Empty"), count(0) {}
    Item(const std::string& name, int count) : name(name), count(count) {}

    std::string getName() const { return name; }
    int getCount() const { return count; }

private:
    std::string name;
    int count;
};
