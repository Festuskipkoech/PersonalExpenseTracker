#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "ExpenseManager.h"

class UserInterface {
private:
    ExpenseManager expenseManager;
    
    // Private helper methods
    void displayMainMenu() const;
    void displayExpenseMenu() const;
    void displayCategoryMenu() const;
    void displayReportMenu() const;
    
    void handleAddExpense();
    void handleViewExpenses();
    void handleDeleteExpense();
    
    void handleAddCategory();
    void handleViewCategories();
    void handleUpdateCategory();
    void handleDeleteCategory();
    
    void handleViewTotalExpenses();
    void handleViewExpensesByCategory();
    void handleViewExpensesByDateRange();
    void handleViewCategoryDistribution();
    void handleViewMonthlySummary();
    
    std::string getValidDate() const;
    bool isValidDate(const std::string& date) const;
    bool isValidDouble(const std::string& str) const;
    bool isValidInt(const std::string& str) const;
    
public:
    // Constructor
    UserInterface(const std::string& dataDir = "../data");
    
    // Main method to run the application
    void run();
};

#endif // USER_INTERFACE_H