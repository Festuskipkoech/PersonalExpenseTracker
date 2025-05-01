#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <vector>
#include <map>
#include <string>
#include "Expense.h"
#include "Category.h"

class ExpenseManager {
private:
    std::vector<Expense> expenses;
    std::vector<Category> categories;
    std::string dataDirectory;
    int nextExpenseId;
    int nextCategoryId;
    
    // File paths
    std::string expensesFilePath;
    std::string categoriesFilePath;

    // Private helper methods
    void loadExpenses();
    void loadCategories();
    void saveExpenses();
    void saveCategories();
    std::string getCurrentDate() const;

public:
    // Constructor
    ExpenseManager(const std::string& dataDir = "../data");
    
    // Expense management
    void addExpense(double amount, const std::string& description, 
                    const std::string& date, int categoryId);
    void deleteExpense(int id);
    Expense getExpense(int id) const;
    std::vector<Expense> getAllExpenses() const;
    std::vector<Expense> getExpensesByCategory(int categoryId) const;
    std::vector<Expense> getExpensesByDateRange(const std::string& startDate, 
                                               const std::string& endDate) const;
    
    // Category management
    void addCategory(const std::string& name, const std::string& description = "");
    void deleteCategory(int id);
    void updateCategory(int id, const std::string& name, const std::string& description);
    Category getCategory(int id) const;
    std::vector<Category> getAllCategories() const;
    
    // Reporting
    double getTotalExpenses() const;
    double getTotalExpensesByCategory(int categoryId) const;
    double getTotalExpensesByDateRange(const std::string& startDate, 
                                      const std::string& endDate) const;
    std::map<std::string, double> getExpenseDistributionByCategory() const;
    std::map<std::string, double> getMonthlyExpenseSummary(int year) const;
};

#endif // EXPENSE_MANAGER_H