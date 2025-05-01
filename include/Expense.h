#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include "Category.h"

class Expense {
private:
    int id;
    double amount;
    std::string description;
    std::string date; // Format: YYYY-MM-DD
    int categoryId;
    std::string categoryName; // Store the category name for easier display

public:
    // Constructors
    Expense();
    Expense(int id, double amount, const std::string& description, 
            const std::string& date, int categoryId, const std::string& categoryName);
    
    // Getters
    int getId() const;
    double getAmount() const;
    std::string getDescription() const;
    std::string getDate() const;
    int getCategoryId() const;
    std::string getCategoryName() const;
    
    // Setters
    void setId(int id);
    void setAmount(double amount);
    void setDescription(const std::string& description);
    void setDate(const std::string& date);
    void setCategoryId(int categoryId);
    void setCategoryName(const std::string& categoryName);
    
    // Other methods
    std::string toString() const;
    std::string toCSV() const;
    static Expense fromCSV(const std::string& csvLine);
};

#endif // EXPENSE_H