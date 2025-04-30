#include "Category.h"
#include <sstream>

// Default constructor
Category::Category() : id(0), name(""), description("") {}

// parameterized constructor
Category::Category(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}

// Getters
int Category::getId() const {
    return id;
}

std::string Category::getName() const {
    return name;
}

std::string Category:: getDescription() const {
    return description;
}

// setters
void Category::setId(int id) {
    this->id =id;
}

void Category::setName(const std::string& name) {
    this -> name = name;
}
void Category::setDescription(const std::string & description) {
    this-> description = description;
}

// other methods
std::string Category::toString() const {
    std::stringstream ss;
    ss << "ID: " << id << ", Name: " << name;
    if(!description.empty()) {
        ss << ", Description: " << description;
    }
    return ss.str();
}

