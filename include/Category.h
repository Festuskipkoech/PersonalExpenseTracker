#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

class Category {
private:
    int id;
    std::string name;
    std::string description;

public:
    // Constructors
    Category();
    Category(int id, const std::string& name, const std::string& description = "");
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    
    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    
    // Other methods
    std::string toString() const;
};

#endif // CATEGORY_H